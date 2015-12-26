package com.ime.interview.multithreadcounter;

import java.util.concurrent.LinkedBlockingQueue;

/**
 * 多线程计数器。通过指定计数上下限，每个计数器的容量以及计数器的执行顺序构造出不同的计数逻辑。 使用方法: 例如，你初始化了3个计数器: Counter
 * counterA = new Counter("A", 3); Counter counterB = new Counter("B", 2);
 * Counter counterC = new Counter("C", 1);
 * 
 * Counter.setMaxNumber(50);
 * 
 * 如果你想按照 A->B->A->C的顺序执行，请将B, A, C加到列表中，然后让起始计数器启动
 * Counter.getCounterList().add(counterB);
 * Counter.getCounterList().add(counterA);
 * Counter.getCounterList().add(counterC);
 * 
 * counterA.start();
 * 
 * @author Jingyu Ma
 *
 */
public class Counter extends Thread {
	/**
	 * 存储可用的Counter。 从性能考虑，用ArrayBlockingQueue更优。但为了扩展性，支持不定数量的Counter,
	 * 选用LinkedBlockingQueue
	 */
	private static volatile LinkedBlockingQueue<Counter> counterList = new LinkedBlockingQueue<Counter>();

	/**
	 * 当前计数器的值。初始时为0, 可以通过setCurrentNumber()改变初始值。该值是全局配置，一旦设定对所有计数器有效。
	 */
	private static volatile int currentNumber = 0;

	/**
	 * 全局配置，计数器统计的数字上限。可以通过setMaxNumber()修改。
	 */
	private static int maxNumber = 50;

	/**
	 * 计数器线程的名称
	 */
	private String threadName = "";

	/**
	 * 指定计数器是否挂起。
	 */
	private boolean suspended = true;

	/**
	 * 指定当前计数器计数任务是否完成。
	 */
	private boolean finished = false;

	/**
	 * 计数器容量，即计数器每次执行输出的数字个数。
	 */
	private int capacity = 1;

	/**
	 * 实例化一个Counter类型。通过指定计数上下限，每个计数器的容量以及计数器的执行顺序构造出不同的计数逻辑。
	 * 
	 * @param threadName
	 *            计数器所在线程名称
	 * @param capacity
	 *            计数器容量，即计数器每次执行输出的数字个数。
	 */
	public Counter(String threadName, int capacity) {
		this.threadName = threadName;
		this.capacity = capacity;
	}

	/**
	 * 获取可用的计数器列表。请在启动计数器之前，务必调用此方法并添加计数器。
	 * 
	 * @return 可用的计数器列表。
	 */
	public static LinkedBlockingQueue<Counter> getCounterList() {
		return Counter.counterList;
	}

	/**
	 * 获取计数器统计的数字上限
	 * 
	 * @return 计数器统计的数字上限
	 */
	public static int getMaxNumber() {
		return Counter.maxNumber;
	}

	/**
	 * 设置计数器统计的数字上限
	 * 
	 * @return 设置计数器统计的数字上限
	 */
	public static void setMaxNumber(int maxNumber) {
		Counter.maxNumber = maxNumber;
	}

	/**
	 * 获取当前计数值
	 * 
	 * @return 当前计数值
	 */
	public static int getCurrentNumber() {
		return Counter.currentNumber;
	}

	/**
	 * 设置当前计数器的值。请在启动任何计数器之前调用，用于设置计数器初始值。
	 * 
	 * @param currentNumber
	 *            当前计数器的值。
	 */
	public static void setCurrentNumber(int currentNumber) {
		Counter.currentNumber = currentNumber;
	}

	/**
	 * 启动计数器。注意，该方法只能被外部调用一次，请调用第一个计数器的该方法，后续的计数器会按照counterList的数序陆续执行。
	 */
	public void run() {
		while (!this.finished) {
			if (Counter.currentNumber > Counter.maxNumber) {
				// 已经达到了计数上限，首先将完成标志设置了。
				this.finished = true;

				// 其次，通知所有计数器可以继续走下去了，计数任务完成了，其他计数器也会陆续结束工作。
				this.finalizeAllCounters();

				break;
			}

			// 这里为了避免输出超过maxNumber的数值而做的处理。
			int length = Math.min(Counter.maxNumber - Counter.currentNumber + 1, this.capacity);

			for (int i = 0; i < length; i++) {
				System.out.printf("线程 %s: %d\n", this.threadName, Counter.currentNumber);

				Counter.currentNumber++;
			}

			System.out.printf("\n");

			// 这次计数任务完成，让下一个计数器开始工作。
			this.nextCounter();
		}
	}

	/**
	 * 挂起线程。
	 */
	private void suspendCounter() {
		this.suspended = true;
	}

	/**
	 * 恢复线程，通知 线程继续运行。
	 */
	private synchronized void resumeCounter() {
		this.suspended = false;
		this.notify();
	}

	/**
	 * 让所有计数器全部恢复，通常是在计数达到上限值后调用。
	 */
	private void finalizeAllCounters() {
		Counter counter = counterList.poll();
		while (counter != null) {
			counter.resumeCounter();
			counter = counterList.poll();
		}
	}

	/**
	 * 将当前计数器加入队列尾部，获取下一个计数器并执行，挂起当前计数器。
	 */
	private void nextCounter() {
		// 首先将当期计数器加入计数器队列尾部，以便后续循环执行。
		counterList.add(this);

		// 取出队首的计数器，并执行。
		Counter counter = counterList.poll();
		if (!counter.isAlive()) {
			// 如果计数器还没有被启动过，启动。
			counter.start();
		} else {
			// 计数器已经启动过了，那么恢复计数器线程。
			counter.resumeCounter();
		}

		// 将当前计数器挂起。这里只是设置了 计数器挂起标志。
		this.suspendCounter();

		try {
			synchronized (this) {
				while (this.suspended) {
					// 如果挂起标志是true, 就一直等待 ，直到this.notify()被call才继续执行。
					this.wait();
				}
			}

			Thread.sleep(100);
		} catch (InterruptedException e) {
			System.out.println(e.getMessage());
			e.printStackTrace();
		}
	}
}
