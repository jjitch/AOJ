#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int cnt;

void printVector(const deque<int>& A) {
	for (size_t i = 0; i < A.size() - 1; i++) {
		cout << A[i] << " ";
	}
	cout << A.back() << endl;
}

void insertionSort(vector<int>& A, int N, int g) {
	for (int i = g; i < N; i++) {
		int v = A[i];
		int j = i - g;
		while (j >= 0 && A[j] > v)
		{
			A[j + g] = A[j];
			j -= g;
			cnt++;
		}
		A[j + g] = v;
	}
}

void shellSort(vector<int>& A, int n) {
	cnt = 0;
	deque<int> G;
	int g = 1;
	while (g <= n)
	{
		G.push_front(g);
		g = 3 * g + 1;
	}
	size_t m = G.size();
	cout << m << endl;
	for (size_t i = 0; i < m-1; i++) {
		cout << G[i] << " ";
	}
	cout << G.back() << endl;
	for (size_t i = 0; i < m; i++)
	{
		insertionSort(A, n, G[i]);
	}
}

int main() {
	size_t n;
	cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < n; i++) {
		cin >> a[i];
	}
	shellSort(a, n);
	cout << cnt << endl;
	for (size_t i = 0; i < n; i++)
	{
		cout << a[i] << endl;
	}
}