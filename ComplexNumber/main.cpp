#include <iostream>
#include "Complex.hpp"

using namespace std;

int main()
{
	Complex c=Complex(3.,3.14/6.,POLAR);
	cout << c.re() << " " << c.im() << endl;
	cout << c.abs() <<" "<< c.arg() << endl;
}