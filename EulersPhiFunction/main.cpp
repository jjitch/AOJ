#include <iostream>
#include <math.h>
#include <unordered_set>

using namespace std;
using ll = unsigned long long;

ll EPF(ll n)
{
	ll ret = n;
	unordered_set<ll> s;
	for (size_t i = 2; i <= (size_t)sqrt(n); i++)
	{
		while (n % i == 0)
		{
			s.insert(i);
			n /= i;
		}
	}
	if (n != 1) s.insert(n);
	for (auto v : s)
	{
		ret *= (v - 1);
		ret /= v;
	}
	return ret;
}

int main()
{
	ll n;
	cin >> n;
	ll ans = EPF(n);
	cout << ans << endl;
}