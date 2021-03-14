#include <iostream>
using namespace std;
using ll = long long;

ll pow(int base, int p, ll mod) {
	ll ret = 1;
	ll cum = base;
	while (p!=0)
	{
		if (p % 2 == 1) {
			ret *= cum;
			ret %= mod;
		}
		cum *= cum;
		cum %= mod;
		p /= 2;
	}
	return ret;
}


int main() {
	int m, n;
	cin >> m >> n;
	const ll mod = 1000000007;
	ll ans = pow(m, n, mod);
	cout << ans << endl;
}
