#include <iostream>
#include <vector>
#include <string>

#define pic pair<int,char>

using namespace std;

pic parseCard(string card) {
	char mark = card[0];
	int num = card[1] - '0';
	return pic(num, mark);
}

string margeCard(pic crad) {

}


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

	/*size_t n;
	cin >> n;
	vector<string> A(n);
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
	cout << cnt << endl;*/
}