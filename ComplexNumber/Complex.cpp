#include "Complex.hpp"

double Complex::abs()
{
	return sqrt(real * real + image * image);
};

double Complex::arg()
{
	return atan2(image, real);
}