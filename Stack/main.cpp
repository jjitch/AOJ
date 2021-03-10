#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main() {

    stack<int> S;
    int a, b;
    string t;
    while (cin >> t) {
        if (t[0] == '+') {
            a = S.top(); S.pop();
            b = S.top(); S.pop();
            S.push(a + b);
        }
        else if (t[0] == '-') {
            a = S.top(); S.pop();
            b = S.top(); S.pop();
            S.push(b - a);
        }
        else if (t[0] == '*') {
            a = S.top(); S.pop();
            b = S.top(); S.pop();
            S.push(a * b);
        }
        else {
            S.push(atoi(t.c_str()));
        }
    }
    cout << S.top() << endl;
}

