#include <iostream>

using namespace std;


int EEA(int a, int b, int& x, int& y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	int d = EEA(b, a % b, y, x);
	y -= a / b * x;
	return d;
}


int main()
{
	int a, b, x, y;
	cin >> a >> b;
	int d = EEA(a, b, x, y);
	cout << x << " " << y << endl;
}