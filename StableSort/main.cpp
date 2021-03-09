#include <iostream>
#include <vector>
#include <string>

using namespace std;


void bubbleSort(vector<string>& A, size_t N) {
	bool flag = true;
	while (flag)
	{
		flag = false;
		for (size_t i = N - 1; i > 0; i--)
		{
			if (A[i][1] < A[i - 1][1])
			{
				string tmp = A[i];
				A[i] = A[i - 1];
				A[i - 1] = tmp;
				flag = true;
			}
		}
	}
}

void selectionSort(vector<string>& A, size_t N) {
	for (size_t i = 0; i < N; i++)
	{
		int minj = i;
		for (size_t j = i; j < N; j++) {
			if (A[j][1] < A[minj][1]) {
				minj = j;
			}
		}
		if (minj != i) {
			string tmp = A[i];
			A[i] = A[minj];
			A[minj] = tmp;
		}
	}
}


int main() {
	

	size_t n;
	cin >> n;
	vector<string> A(n);
	for (size_t i = 0; i < n; i++)
	{
		cin >> A[i];
	}
	vector<string> B = A;
	bubbleSort(A, n);
	selectionSort(B, n);
	for (size_t i = 0; i < A.size() - 1; i++)
	{
		cout << A[i] << " ";
	}
	cout << A.back() << endl;
	cout << "Stable" << endl;
	
	for (size_t i = 0; i < B.size() - 1; i++)
	{
		cout << B[i] << " ";
	}
	cout << B.back() << endl;
	for (size_t i = 0; i < n; i++)
	{
		if (A[i] != B[i]) {
			cout << "Not stable" << endl;
			return 0;
		}
	}
	cout << "Stable" << endl;
}