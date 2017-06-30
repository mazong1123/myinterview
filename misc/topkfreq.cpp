vector<string> topKFrequent(vector<string>& nums, int k)
{
    vector<string> res;
    res.reserve(k);

    unordered_map<string, int> ht;
    for (size_t i = 0; i < nums.size(); ++i)
    {
        ht[nums[i]]++;
    }

    multimap<int, string> mp;
    for (auto it = ht.begin(); it != ht.end(); ++it)
    {
        mp.insert(pair<int, string>(it->second, it->first));
    }

    for (auto it = mp.rbegin(); it != mp.rend(); ++it)
    {
        res.push_back(it->second);
        if (res.size() == k)
        {
            break;
        }
    }

    return res;
}
