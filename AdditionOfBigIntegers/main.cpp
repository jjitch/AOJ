#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

class BigInt
{
	vector<int> nums;
	int isMinus = 0;
	void carryAndFix(size_t n)
	{
		for (size_t i = 0; i < n-1; i++)
		{
			int digit = nums[i];
			if (digit>10)
			{
				int k = digit / 10;
				nums[i] -= k * 10;
				nums[i + 1] += k;
			}
		}
	}
public:
	// constructor
	BigInt()
	{
		nums = {};
	}
	BigInt(string s)
	{
		auto c = s.end();
		do
		{
			c--;
			if (*c == '-')
			{
				isMinus = 1;
				break;
			}
			nums.push_back(*c - '0');
		} while (c != s.begin());
	}
	const BigInt operator+(const BigInt& rhs)
	{
		size_t thisSize = this->nums.size();
		size_t rhsSize = rhs.nums.size();
		size_t retSize = max(thisSize, rhsSize);
		BigInt ret;
		// plus vs plus
		if (!this->isMinus && !rhs.isMinus)
		{
			for (size_t i = 0; i < retSize; i++)
			{
				int newDigit = (i < thisSize ? this->nums[i] : 0) + (i < rhsSize ? rhs.nums[i] : 0);
				ret.nums.push_back(newDigit);
			}
		}
		carryAndFix(retSize);
		return ret;
	}
	friend ostream& operator<<(ostream& os, const BigInt& bigInt)
	{
		if (bigInt.isMinus)
		{
			os << '-';
		}
		auto value = bigInt.nums.end();
		do
		{
			value--;
			os << *value;
		} while (value != bigInt.nums.begin());
		return os;
	};
};


int main()
{
	string s1, s2;
	cin >> s1 >> s2;
	BigInt bi1(s1), bi2(s2);
	cout << bi1 + bi2 << endl;
}