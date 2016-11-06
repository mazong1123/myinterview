#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>

using std::vector;

vector<int> insertionSort(vector<int> arr)
{
    if (arr.empty() || arr.size() == 1)
    {
        return arr;
    }

    for (int i = 1; i < arr.size(); ++i)
    {
        int j = i - 1;
        while (j >= 0 && arr[j] > arr[j + 1])
        {
            // swap
            int temp = arr[j + 1];
            arr[j + 1] = arr[j];
            arr[j] = temp;

            --j;
        }
    }

    return arr;
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

    vector<int> sortedArr = insertionSort(arr);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Executed = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " micro seconds." << std::endl;

    return 0;
}