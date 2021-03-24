#pragma once
#include <math.h>
class Complex
{
private:
	double real;
	double image;
public:
	Complex(double re, double im);
};

Complex::Complex(double re, double im)
{
	this->real = re;
	this->image = im;
}