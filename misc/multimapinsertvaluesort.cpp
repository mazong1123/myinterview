#include <iostream>
#include <string>
#include <map>

using std::cout;
using std::endl;
using std::multimap;
using std::map;

// Insert and sort values. Inspired by https://stackoverflow.com/questions/21215214/how-to-sort-both-key-and-value-in-a-multimap/33406365#33406365
// The time complexity is O(mlgn). m is the duplicated keys in the multimap. n is the size of multimap.
void insertValueSorted(multimap<int, int>& mmap, int key, int value)
{
    auto keyValues = mmap.equal_range(key);
    for (auto it = keyValues.first; it != keyValues.second; ++it)
    {
        // Change the condition according to your requirement.
        if (it->second > value)
        { 
            mmap.emplace_hint(it, key, value);

            return;
        }
    }

    // The input key does not exist in mmap,
    // or the key does exit in mmap, but the input value is greater than all values of the existing key.
    mmap.emplace(key, value);
}

int main()
{
    map<int, multimap<int, int>> m;

    multimap<int, int> mm;
    insertValueSorted(mm, 1, 20);
    insertValueSorted(mm, 1, 20);
    insertValueSorted(mm, 1, 3);
    insertValueSorted(mm, 1, 6);
    insertValueSorted(mm, -11, 3);
    insertValueSorted(mm, 5, 31);
    insertValueSorted(mm, 5, 3);

    multimap<int, int> mm2;
    insertValueSorted(mm2, 6, 3);
    insertValueSorted(mm2, 5, 21);
    insertValueSorted(mm2, 5, 13);

    m[1] = mm;
    m[2] = mm2;

    for (auto it = m.begin(); it != m.end(); ++it)
    {
        cout << "map contains: " << endl;
        
        for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
        {
            cout << iter->first << "," << iter->second << endl;
        }

        cout << endl;
    }
}