#include <iostream>
#include "Complex.hpp"

using namespace std;

int main()
{
	Complex c(3., 6);
	cout << c.abs() << endl;
	cout << c.arg() << endl;
}