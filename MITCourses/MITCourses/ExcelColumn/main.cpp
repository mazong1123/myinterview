#include <string>
#include <vector>

void convertToColumnName(unsigned int num, std::string& columnName)
{
	if (num == 0)
	{
		return;
	}

	std::vector<unsigned int> radixVec;
	while (num > 0)
	{
		unsigned int r = num % 26;
		num = num / 26;

		if (r == 0)
		{
			r = 26;
			--num;
		}

		radixVec.push_back(r);
	}

	std::string result;
	for (auto it = radixVec.rbegin(); it != radixVec.rend(); ++it)
	{
		result += (char)(65 + *it - 1);
	}

	columnName = result;
}

int main()
{
	std::string columnName;

	convertToColumnName(16384, columnName);

	return 0;
}
