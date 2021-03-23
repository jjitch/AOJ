#include "Complex.hpp"
#include <sstream>
#include <math.h>

double Complex::abs()
{
	return sqrt(this->real * this->real + this->image * this->image);
}

double Complex::arg()
{
	return atan(this->image/this->real);
}