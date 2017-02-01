#include<unordered_map>

unsigned int fibr(unsigned int n)
{
	static std::unordered_map<unsigned int, unsigned int> cache;
	auto iter = cache.find(n);
	if (iter != cache.end())
	{
		return	iter->second;
	}

	if (n == 0 || n == 1)
	{
		cache[n] = n;
		return n;
	}

	int value = fibr(n - 1) + fibr(n - 2);
	cache[n] = value;

	return value;
}

unsigned int fib(unsigned int n)
{
	if (n == 0 || n == 1)
	{
		return n;
	}

	std::unordered_map<unsigned int, unsigned int> cache;
	cache[0] = 0;
	cache[1] = 1;

	for (unsigned int i = 2; i <= n; ++i)
	{
		cache[i] = cache[i - 1] + cache[i - 2];
	}

	return cache[n];
}

int main()
{
	unsigned int r = fibr(1);
	r = fibr(0);
	r = fibr(5);
	r = fibr(10);

	r = fib(0);
	r = fib(1);
	r = fib(10);

	return 0;
}
