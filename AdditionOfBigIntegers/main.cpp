#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

class BigInt
{
	vector<int> bigInt;
	int sign;
public:
	BigInt(string s):sign(1)
	{
		if (s[0] == '-')
		{
			sign = -1;
		}
		for (const char& c : s)
		{
			bigInt.push_back(static_cast<int>(c - '0'));
		}
	}
	string getBigInt()
	{
		string s;
		for (int i : bigInt)
		{
			s.push_back(static_cast<char>(i + '0'));
		}
		return s;
	}
	BigInt operator + (BigInt rhs)
	{

	}
};

int main()
{
	string s1, s2;
	cin >> s1 >> s2;
	BigInt bi1 = BigInt(s1);
	BigInt bi2 = BigInt(s2);
}