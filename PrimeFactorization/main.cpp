#include <iostream>
#include <vector>
#include <math.h>

int main() {
	using namespace std;
	int n;
	cin >> n;
	cout << n << ":";
	int lim = (int)sqrt(n);
	vector<int> ans;
	int i = 2;
	while (n!=1)
	{
		if (i > lim&&ans.size()==0) {
			ans.push_back(n);
			break;
		}
		if (n % i == 0) {
			ans.push_back(i);
			n /= i;
		}
		else {
			i++;
		}
	}

	for (int  j = 0; j < (int)ans.size(); j++)
	{
		cout << " " << ans[j];
	}
	cout << endl;
}