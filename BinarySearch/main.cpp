#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
#define rep(i,n) for (size_t i=0;i<(n);i++)

int main() {
	size_t cnt = 0;
	size_t n;
	cin >> n;
	vector<int> s(n);
	rep(i, n)cin >> s[i];
	int head = s[0];
	int last = s.back();
	size_t q;
	cin >> q;
	vector<int> t(q);
	rep(i, q)cin >> t[i];
	s.push_back(1 << 30);
	for (int v : t) {
		if (v < head || last < v) {
			continue;
		}
		auto lower = lower_bound(s.begin(), s.end(), v);
		auto upper = upper_bound(s.begin(), s.end(), v);
		cnt += (upper - lower);
	}
	cout << cnt << endl;
}