#include <queue>
#include <iostream>
#include <string>

using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)

int main() {
	int n, q;
	cin >> n >> q;
	queue<pair<string, int>> qsi;
	rep(i, n) {
		string name;
		int time;
		cin >> name >> time;
		qsi.push(pair<string, int>(name, time));
	}
	int spent = 0;
	while (!qsi.empty())
	{
		pair<string, int> task = qsi.front();
		qsi.pop();
		int need = task.second;
		if (need <= q) {
			spent += need;
			cout << task.first << " " << spent << endl;
		}
		else {
			spent += q;
			task.second -= q;
			qsi.push(task);
		}
	}
}

