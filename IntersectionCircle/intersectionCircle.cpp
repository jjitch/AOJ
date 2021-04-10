#include <iostream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

class Vec2
{
	double x;
	double y;
public:
	Vec2() :x(0), y(0) {};
	Vec2(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
	const double getX() const { return x; }
	const double getY() const { return y; }
	const double getAngle() const { return atan(y / x); }
	void rotate(const double& theta)
	{
		double tmpX = x * cos(theta) - y * sin(theta);
		double tmpY = x * sin(theta) + y * cos(theta);
		x = tmpX;
		y = tmpY;
	}
	void flipX() { x *= -1; }
	void flipY() { y *= -1; }

	// Assignment operator

	Vec2& operator = (const Vec2& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	// Binary operator

	const Vec2 operator + (const Vec2& other) const
	{
		return Vec2(x + other.x, y + other.y);
	}
	const Vec2 operator - (const Vec2& other) const
	{
		return Vec2(x - other.x, y - other.y);
	}
	// Inner product
	const double operator * (const Vec2& other) const
	{
		return x * other.x + y * other.y;
	}
	template<class U> const Vec2 operator * (const U& t) const
	{
		return Vec2(x * t, y * t);
	}
	template<class U> friend const Vec2 operator * (const U& a, const Vec2& vec2)
	{
		return Vec2(vec2.x * a, vec2.y * a);
	}
	// Outer product
	const double operator / (const Vec2& other) const
	{
		return x * other.y - y * other.x;
	}

	//Urary operator

	Vec2& operator+=(const Vec2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vec2& operator-=(const Vec2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	// IO operator

	friend std::ostream& operator << (std::ostream& os, const Vec2& vec2)
	{
		std::cout << vec2.x << " " << vec2.y;
		return os;
	}
	friend std::istream& operator >> (std::istream& is, Vec2& vec2)
	{
		std::cin >> vec2.x >> vec2.y;
		return is;
	}

	// Relatinal operator

	bool operator < (const Vec2& other) const { return x < other.x || (!(other.x < x) && y < other.y); }
	bool operator > (const Vec2& other) const { return x > other.x || (!(other.x > x) && y > other.y); }
	bool operator <= (const Vec2& other) const { return !(*this > other); }
	bool operator >= (const Vec2& other) const { return !(*this < other); }
	bool operator == (const Vec2& other) const { return x == other.x && y == other.y; }
	bool operator != (const Vec2& other) const { return !(*this == other); }

};

enum class PAIR_OF_CIRCLES
{
	DONT_CROSS,
	CIRCUMSCRIBED,
	INTERSECT,
	INSCRIBED,
	INCLUDED
};

PAIR_OF_CIRCLES poc(const Vec2& c1, const double& r1, const Vec2& c2, const double& r2)
{
	double d = (c1 - c2) * (c1 - c2);
	double sumR = (r1 + r2) * (r1 + r2);
	double subR = (r1 - r2) * (r1 - r2);
	if (sumR < d)
	{
		return PAIR_OF_CIRCLES::DONT_CROSS;
	}
	else if (sumR == d)
	{
		return PAIR_OF_CIRCLES::CIRCUMSCRIBED;
	}
	else if (subR < d)
	{
		return PAIR_OF_CIRCLES::INTERSECT;
	}
	else if (subR == d)
	{
		return PAIR_OF_CIRCLES::INSCRIBED;
	}
	else
	{
		return PAIR_OF_CIRCLES::INCLUDED;
	}
}

int main()
{
	using namespace std;
	Vec2 c1, c2;
	double r1, r2;
	cin >> c1 >> r1 >> c2 >> r2;
	switch (poc(c1, r1, c2, r2))
	{
	case PAIR_OF_CIRCLES::DONT_CROSS:
		cout << 4 << endl;
		break;
	case PAIR_OF_CIRCLES::CIRCUMSCRIBED:
		cout << 3 << endl;
		break;
	case PAIR_OF_CIRCLES::INTERSECT:
		cout << 2 << endl;
		break;
	case PAIR_OF_CIRCLES::INSCRIBED:
		cout << 1 << endl;
		break;
	case PAIR_OF_CIRCLES::INCLUDED:
		cout << 0 << endl;
	default:
		break;
	}
}