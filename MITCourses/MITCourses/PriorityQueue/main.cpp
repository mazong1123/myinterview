#include <iostream>
#include <algorithm>
#include <cstdlib>

#include "PriorityQueue.h"

int main()
{
    int arraySize = 10;

    PriorityQueue pq;

    for (int i = 0; i < arraySize; ++i)
    {
        pq.insert(rand() % arraySize);
    }

    // Get max
    std::cout << "max():" << std::endl;
    std::cout << pq.max() << std::endl;

    // Increase key
    std::cout << "increaseKey():" << std::endl;
    pq.increaseKey(2, INT_MAX);

    // Extract max
    std::cout << "extractMax():" << std::endl;
    while (!pq.empty())
    {
        std::cout << pq.extractMax() << " ";
    }

    std::cout << std::endl;

    return 0;
}