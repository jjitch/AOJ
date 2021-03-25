#include "Complex.hpp"

Complex::Complex(double re, double im, bool type=0)
{
	real = re;
	image = im;
	if (type)
	{
		real *= cos(image);
		image = re * sin(image);
	}
};


double Complex::abs()
{
	return sqrt(real * real + image * image);
};

double Complex::arg()
{
	return atan2(image, real);
};

Complex& Complex::operator = (Complex& rhs) {
	real = rhs.re();
	image = rhs.im();
	return *this;
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