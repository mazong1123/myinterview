#include<vector>
#include<iostream>

int cutRod(const std::vector<int>& p, size_t l)
{
	if (l == 0)
	{
		return 0;
	}

	int r = -99999;
	for (size_t i = 1; i <= l; ++i)
	{
		int tempRevenue = p[i - 1] + cutRod(p, l - i);
		if (r < tempRevenue)
		{
			r = tempRevenue;
		}
	}

	return r;
}

int bottomUpCutRod(const std::vector<int>& p, size_t l)
{
	if (l <= 0)
	{
		return 0;
	}

	std::vector<int> revenues;
	revenues.resize(l + 1, -99999);
	revenues[0] = 0;

	for (size_t i = 1; i <= l; ++i)
	{
		int r = -99999;
		for (size_t j = 1; j <= i; ++j)
		{
			int tempR = p[j - 1] + revenues[i - j];
			if (r < tempR)
			{
				r = tempR;
			}
		}

		revenues[i] = r;
	}

	return revenues[l];
}

int main()
{
	std::vector<int> priceTable = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
	size_t rodLength = 10;

	if (rodLength > priceTable.size())
	{
		return -1;
	}

	std::cout << "Calculating revenue..." << std::endl;
	// size_t revenue = cutRod(priceTable, rodLength);
	size_t revenue = bottomUpCutRod(priceTable, rodLength);
	std::cout << "The revenue is " << revenue << std::endl;

	return 0;
}
