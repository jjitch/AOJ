#include <iostream>
#include <vector>

using namespace std;

int cnt = 0;
void selectionSort(vector<int>& A, size_t N) {
	for (size_t i = 0; i < N; i++)
	{
		int minj = i;
		for (size_t j = i; j < N; j++) {
			if (A[j] < A[minj]) {
				minj = j;
			}
		}
		if (minj != i) {
			int tmp = A[i];
			A[i] = A[minj];
			A[minj] = tmp;
			cnt++;
		}
	}
}


int main() {
	size_t n;
	cin >> n;
	vector<int> A(n);
	for (size_t i = 0; i < n; i++)
	{
		cin >> A[i];
	}
	selectionSort(A, n);
	for (size_t i = 0; i < A.size() - 1; i++)
	{
		cout << A[i] << " ";
	}
	cout << A.back() << endl;
	cout << cnt << endl;
}