#include <iostream>
#include <vector>

using namespace std;


int gcd(int a, int b) {
	if (b == 0) {
		return a;
	}
	return gcd(b, a % b);
}


unsigned int lcm(int n, vector<int> a) {
	unsigned int ans = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			a[j] /= gcd(a[j], a[i]);
		}
	}
	for (int i = 0; i < n; i++)
	{
		ans *= a[i];
	}
	return ans;
}

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	unsigned int ans = lcm(n, a);
	cout << ans << endl;
}