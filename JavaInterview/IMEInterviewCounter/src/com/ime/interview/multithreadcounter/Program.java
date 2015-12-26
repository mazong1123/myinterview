package com.ime.interview.multithreadcounter;

public class Program {
	public static void main(String args[]) {
		runWithStandardData();
		
		// 也可以试试其他几个方法，可以支持比较灵活的数据和输出顺序。
	}

	/**
	 * 这是标准数据的输入，即面试要求的数据和顺序
	 */
	private static void runWithStandardData() {
		Counter counterA = new Counter("A", 3);
		Counter counterB = new Counter("B", 2);
		Counter counterC = new Counter("C", 1);

		Counter.setMaxNumber(50);
		Counter.getCounterList().add(counterB);
		Counter.getCounterList().add(counterA);
		Counter.getCounterList().add(counterC);

		counterA.start();
	}

	/**
	 * 负数开始计数也是支持的
	 */
	private static void runWithNegativeData() {
		Counter counterA = new Counter("A", 3);
		Counter counterB = new Counter("B", 2);
		Counter counterC = new Counter("C", 1);

		Counter.setCurrentNumber(-20);
		Counter.setMaxNumber(50);
		Counter.getCounterList().add(counterB);
		Counter.getCounterList().add(counterA);
		Counter.getCounterList().add(counterC);

		counterA.start();
	}

	/**
	 * 每个计数器的容量可变，计数器的顺序也是可调的，具体可以见Counter类的使用说明。
	 */
	private static void runWithAnotherOrderAndData() {
		Counter counterA = new Counter("A", 3);
		Counter counterB = new Counter("B", 2);
		Counter counterC = new Counter("C", 1);
		Counter counterD = new Counter("D", 2);
		
		Counter.setCurrentNumber(-20);
		Counter.setMaxNumber(60);
		Counter.getCounterList().add(counterA);
		Counter.getCounterList().add(counterC);
		Counter.getCounterList().add(counterB);
		Counter.getCounterList().add(counterD);

		counterB.start();
	}
}
