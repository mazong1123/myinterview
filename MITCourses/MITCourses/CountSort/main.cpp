#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <chrono>

using std::vector;

const int MAX_NUM = 10000;

vector<int>* countSort(const vector<int>& arr)
{
    int interArrSize = MAX_NUM + 1;
    vector<int> interArr;
    interArr.resize(interArrSize, 0);

    for (int i = 0; i < arr.size(); ++i)
    {
        interArr[arr[i]] += 1;
    }

    for (int i = 1; i < interArrSize; ++i)
    {
        // interArr[i] stores the count of numbers <= i.
        interArr[i] += interArr[i - 1];
    }

    vector<int>* resultArr = new vector<int>();
    resultArr->resize(arr.size(), 0);

    for (int i = 0; i < arr.size(); ++i)
    {
        // interArr[arr[i]]: The count of numbers <= arr[i].
        // So interArr[arr[i]] - 1 is the right index arr[i] should store.
        (*resultArr)[interArr[arr[i]] - 1] = arr[i];
        --interArr[arr[i]];
    }

    return resultArr;
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

    auto result = countSort(arr);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Executed = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " micro seconds." << std::endl;

    delete result;
    result = nullptr;

    return 0;
}