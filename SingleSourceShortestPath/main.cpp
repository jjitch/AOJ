#include <iostream>
#include <queue>

#define rep(i,n) for (int i=0;i<(n);i++)

using namespace std;


int main() {
	priority_queue<int> pq;
	while (true)
	{
		int a;
		cin >> a;
		pq.emplace(a);
		priority_queue<int> display = pq;
		while (!display.empty()) {
			cout << display.top() << " ";
			display.pop();
		} cout << endl;
	}
}