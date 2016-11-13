#include <stdexcept>

#include "PriorityQueue.h"

PriorityQueue::PriorityQueue()
{
}

PriorityQueue::~PriorityQueue()
{
}

bool PriorityQueue::empty()
{
    return m_vec.empty();
}

int PriorityQueue::max()
{
    if (m_vec.empty())
    {
        throw std::invalid_argument("Queue is empty.");
    }

    return m_vec[0];
}

int PriorityQueue::extractMax()
{
    if (m_vec.empty())
    {
        throw std::invalid_argument("Queue is empty.");
    }

    // Get the root node value as the max value.
    // Swap the root node and last leaf.
    int max = m_vec[0];
    m_vec[0] = m_vec.back();
    m_vec[m_vec.size() - 1] = max;

    // Now we should decrease the heap size.
    m_vec.resize(m_vec.size() - 1);

    // Do max-heapify to keep the max heap property.
    maxHeapify(0);

    return max;
}

void PriorityQueue::insert(int k)
{
    m_vec.push_back(INT_MIN);

    this->increaseKey(m_vec.size() - 1, k);
}

void PriorityQueue::increaseKey(int i, int k)
{
    if (i >= m_vec.size())
    {
        throw std::invalid_argument("The index is over the range of the heap.");
    }

    if (m_vec[i] > k)
    {
        throw std::invalid_argument("The new key is smaller than the current key.");
    }

    m_vec[i] = k;

    int parentIndex = (i + 1) / 2 - 1;
    while (parentIndex >= 0 && m_vec[parentIndex] < m_vec[i])
    {
        int temp = m_vec[parentIndex];
        m_vec[parentIndex] = m_vec[i];
        m_vec[i] = temp;

        i = parentIndex;
        parentIndex = (i + 1) / 2 - 1;
    }
}

void PriorityQueue::maxHeapify(int i)
{
    int left = (i + 1) * 2 - 1;
    int right = left + 1;

    if (left >= m_vec.size())
    {
        return;
    }

    int largestIndex = i;

    if (m_vec[left] > m_vec[largestIndex])
    {
        largestIndex = left;
    }

    if (right < m_vec.size() && m_vec[right] > m_vec[largestIndex])
    {
        largestIndex = right;
    }

    if (largestIndex == i)
    {
        return;
    }

    int temp = m_vec[i];
    m_vec[i] = m_vec[largestIndex];
    m_vec[largestIndex] = temp;

    maxHeapify(largestIndex);
}

