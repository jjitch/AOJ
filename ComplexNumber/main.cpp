#include "Complex.hpp"
#include <iostream>

int main()
{
	using namespace std;
	Complex c(1., 1.);
	cout << c.abs() << endl;
	cout << c.arg() << endl;
	cout << c.re() << endl;
}