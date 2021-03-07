#include <iostream>
#include <vector>

using namespace std;

int cnt = 0;

void bubbleSort(vector<int>& A, size_t N) {
	bool flag = true;
	while (flag)
	{
		flag = false;
		for (size_t i = N-1; i > 0; i--)
		{
			if (A[i] < A[i - 1])
			{
				int tmp = A[i];
				A[i] = A[i - 1];
				A[i - 1] = tmp;
				flag = true;
				cnt++;
			}
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
	bubbleSort(A, n);
	for (size_t i = 0; i < A.size()-1; i++)
	{
		cout << A[i] << " ";
	}
	cout << A.back() << endl;
	cout << cnt << endl;
}