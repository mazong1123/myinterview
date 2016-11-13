#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <chrono>

using std::vector;

int partition(vector<int>& v, int l, int r)
{
    int i = l - 1;
    int pe = v[r];

    for (int j = l; j <= r - 1; ++j)
    {
        if (v[j] <= pe)
        {
            // We found a value smaller than pivot element.
            // The "smaller value" boundary should be increased.
            ++i;

            // Now move the smaller value to the new boundary index.
            // The original value at this boundary index should be moved to
            // current j index (As it's bigger than the pe - proved by one of the previous steps,
            // it should not be stored at the "smaller value" boundary index).
            int temp = v[j];
            v[j] = v[i];
            v[i] = temp;
        }
    }

    int temp = v[r];
    v[r] = v[i + 1];
    v[i + 1] = temp;

    // i + 1 is now the pe element.
    // index < i + 1 is smaller than pe; index > i + 1 is greater than pe.
    return i + 1;
}

void quickSort(vector<int>& v, int l, int r)
{
    if (l > r)
    {
        return;
    }

    int m = partition(v, l, r);
    quickSort(v, l, m - 1);
    quickSort(v, m + 1, r);
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

    quickSort(arr, 0, arr.size() - 1);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Executed = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " micro seconds." << std::endl;

    return 0;
}