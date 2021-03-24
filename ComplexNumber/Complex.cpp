#include "Complex.hpp"


double Complex::abs()
{
	return sqrt(real * real + image * image);
};

double Complex::arg()
{
	return atan2(image, real);
};

const Complex Complex::operator + (Complex& rhs) const
{
	return Complex(real + rhs.re(), image + rhs.im());
};
const Complex Complex::operator - (Complex& rhs) const
{
	return Complex(real - rhs.re(), image - rhs.im());
};
const Complex Complex::operator * (Complex& rhs) const
{
	return Complex(real * rhs.re() - image * rhs.im(), image * rhs.re() * real * rhs.im());
};