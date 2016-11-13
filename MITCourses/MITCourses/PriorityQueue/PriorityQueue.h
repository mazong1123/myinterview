#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include <vector>

class PriorityQueue
{
public:
    PriorityQueue();
    ~PriorityQueue();

    bool empty();
    int max();
    int extractMax();
    void insert(int i);
    void increaseKey(int i, int k);
private:
    void maxHeapify(int i);

    std::vector<int> m_vec;
};

#endif // PRIORITY_QUEUE_H_

