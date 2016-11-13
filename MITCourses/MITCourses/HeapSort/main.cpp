#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <chrono>

using std::vector;

// It's O(lgn)
void maxHeapify(vector<int>& v, int i, int heapSize)
{
    int left = (i + 1) * 2 - 1;
    int right = left + 1;

    if (left >= heapSize)
    {
        return;
    }

    int largest = i;

    if (left < heapSize && v[left] > v[largest])
    {
        largest = left;
    }

    if (right < heapSize && v[right] > v[largest])
    {
        largest = right;
    }

    if (largest == i)
    {
        // Current i is a root node of max heap subtree.
        return;
    }

    int temp = v[i];
    v[i] = v[largest];
    v[largest] = temp;

    maxHeapify(v, largest, heapSize);
}

// It's O(n)
void buildMaxHeap(vector<int>& v)
{
    // Start from v.size() / 2 + 1, they are all leaves and
    // are max heaps in nature.
    // We only do max-heapify on 0 - v.size / 2.
    for (int i = v.size() / 2 - 1; i >= 0; --i)
    {
        maxHeapify(v, i, v.size());
    }
}

void heapSort(vector<int>& v)
{
    // Build a max heap first.
    buildMaxHeap(v);

    int heapSize = v.size();
    while (heapSize >= 2)
    {
        // Swap the first element and last element in the heap.
        // So the the last element is the largest element at this time. 
        int temp = v[0];
        v[0] = v[heapSize - 1];
        v[heapSize - 1] = temp;

        --heapSize;

        // As current array may not meet the max-heap requirement,
        // we need a O(lgn) max-heapify.
        maxHeapify(v, 0, heapSize);
    }
}

int main()
{
    int arraySize = 500;

    vector<int> arr;
    arr.reserve(arraySize);
    for (int i = 0; i < arraySize; ++i)
    {
        arr.push_back(rand() % arraySize);
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    heapSort(arr);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Executed = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " micro seconds." << std::endl;

    return 0;
}