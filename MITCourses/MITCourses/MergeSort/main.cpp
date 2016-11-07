#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <chrono>

using std::vector;

void merge(int left, int middle, int right, vector<int>& arr)
{
    int leftArraySize = middle - left + 1;
    vector<int> leftArray;
    leftArray.reserve(leftArraySize);

    for (int i = left; i <= middle; ++i)
    {
        leftArray.push_back(arr[i]);
    }

    // Sentinel number. 
    leftArray.push_back(INT_MAX);

    int rightArraySize = right - (middle + 1) + 1;
    vector<int> rightArray;
    rightArray.reserve(rightArraySize);

    for (int i = middle + 1; i <= right; ++i)
    {
        rightArray.push_back(arr[i]);
    }

    // Sentinel number.
    rightArray.push_back(INT_MAX);

    int i = 0;
    int j = 0;

    for (int k = left; k <= right; ++k)
    {
        if (leftArray[i] < rightArray[j])
        {
            arr[k] = leftArray[i];
            ++i;
        }
        else
        {
            arr[k] = rightArray[j];
            ++j;
        }
    }
}

void mergeSort(vector<int>& arr, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int middle = left + (right - left) / 2;

    // Divde
    mergeSort(arr, left, middle);
    mergeSort(arr, middle + 1, right);

    // Conquer
    merge(left, middle, right, arr);
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

    mergeSort(arr, 0, arr.size() - 1);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Executed = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " micro seconds." << std::endl;

    return 0;
}