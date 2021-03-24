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
	//todo
	//operator/Š„‚èŽZ^‹¤–ð
	//ostream‚É—¬‚µ‚½‚¢
	const Complex operator + (Complex& rhs) const;
	const Complex operator - (Complex& rhs) const;
	const Complex operator * (Complex& rhs) const;
	Complex& operator+=(Complex& other){
		this->real += other.re();
		this->image += other.im();
	}
};

inline Complex::Complex(double re, double im)
{
	this->real = re;
	this->image = im;
};

