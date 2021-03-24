#pragma once
#include <math.h>
class Complex
{
private:
	double real;
	double image;
public:
	Complex(double re, double im);
	double re() { return real; };
	double im() { return image; };
	double abs();
	double arg();
};

inline Complex::Complex(double re, double im)
{
	this->real = re;
	this->image = im;
};