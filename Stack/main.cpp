#include <iostream>
#include <stack>
#include "TestClass.h"
using namespace std;

int main() {
	TestClass tc=TestClass(4,7);
	cout << tc.getX() << endl;
}