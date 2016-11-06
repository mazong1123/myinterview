#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <chrono>

using std::vector;

void merge(int leftStart, int rightStart, vector<int>& sorted)
{
    int count = rightStart - leftStart;

    if (count <= 0)
    {
        return;
    }

    if (count == 1)
    {
        sorted.push_back(std::min(sorted[leftStart], sorted[rightStart]));

        return;
    }

    merge(leftStart, count / 2,sorted);
    merge(count / 2 + 1, count - count / 2, source, sorted);
}

vector<int> mergeSort(vector<int> arr)
{
    if (arr.empty() || arr.size() == 1)
    {
        return arr;
    }

    vector<int> sortedArray;

    merge(0, arr.size() / 2 - 1, arr.size() / 2, arr, sortedArray);
    merge(arr.size() / 2, arr.size() - arr.size() / 2, arr.size() - arr.size() / 2, arr, sortedArray);

    return sortedArray;
}

int main()
{
    int arraySize = 10;

    vector<int> arr;
    arr.reserve(arraySize);
    for (int i = 0; i < arraySize; ++i)
    {
        arr.push_back(rand() % arraySize);
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    vector<int> sortedArr = mergeSort(arr);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Executed = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " micro seconds." << std::endl;

    return 0;
}