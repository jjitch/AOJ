#include <iostream>
#include <vector>
#include <iomanip>

#define rep(i,a,n) for (int i=a;i<(n);i++)

using namespace std;
using pdd = pair<double, double>;

template<class T>
pair<T, T> operator + (pair<T, T> a, pair<T, T> b) {
	return pair<T, T>(a.first + b.first, a.second + b.second);
};

template<class T>
pair<T, T> operator - (pair<T, T> a, pair<T, T> b) {
	return pair<T, T>(a.first - b.first, a.second - b.second);
};

template<class T>
T operator ^ (pair<T, T> a, pair<T, T> b) {
	return a.first * b.second - a.second * b.first;
}

int main() {
	int n;
	cin >> n;
	vector<pdd> p(n, pdd());
	rep(i, 0, n) {
		cin >> p[i].first >> p[i].second;
	}
	pdd head = p[0];
	double ans = 0;
	rep(i, 1, n - 1) {
		ans += (p[i] - head) ^ (p[i + 1] - head);
	}
	cout << fixed << setprecision(1) << ans / 2. << endl;
}