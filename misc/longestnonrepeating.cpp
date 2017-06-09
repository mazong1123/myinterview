    int lengthOfLongestSubstring(string s) {
    	if (s.empty())
    	{
    		return 0;
    	}        
    
    	int res = -1;
    	int start = 0;
    	int end = 0;
    	unordered_map<char, int> ht;
    
    	while (end < s.length())
    	{
    		if (ht.find(s[end]) != ht.end())
    		{
    			res = max(res, end - start);
    			start = max(start, ht[s[end]] + 1);
    		}
    		
    		ht[s[end]] = end;
    		++end;
    	}
	
    	res = max(res, end - start);
    
    	return res;
    }
