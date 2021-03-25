#pragma once
#include <math.h>

#define CARTESIAN 0
#define POLAR 1

class Complex
{
private:
	double real;
	double image;
public:
	Complex(double re, double im, bool type);
	double re() { return real; };
	double im() { return image; };
	double abs();
	double arg();

	// substitute
	Complex& operator=(Complex& rhs);

	// add
	const Complex operator + (Complex& rhs) const;
	
	// substrate
	const Complex operator - (Complex& rhs) const;

	// multiply
	const Complex operator * (Complex& rhs) const;
	Complex& operator+=(Complex& other){
		this->real += other.re();
		this->image += other.im();
	}
};


