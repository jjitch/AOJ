#include <iostream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <math.h>

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
	const double getX() { return x; }
	const double getY() { return y; }
	const double getAngle() { return atan(y / x); }
	void rotate(const double& theta)
	{
		double tmpX = x * cos(theta) - y * sin(theta);
		double tmpY = x * sin(theta) + y * cos(theta);
		x = tmpX;
		y = tmpY;
	}
	void flipX() { x *= -1; }
	void flipY() { y *= -1; }
	Vec2& operator=(const Vec2& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}
	const Vec2 operator + (const Vec2& other)
	{
		return Vec2(x + other.x, y + other.y);
	}
	const Vec2 operator - (const Vec2& other)
	{
		return Vec2(x - other.x, y - other.y);
	}
	// Inner product
	const double operator * (const Vec2& other)
	{
		return x * other.x + y * other.y;
	}
	template<class U> const Vec2 operator * (const U& t)
	{
		return Vec2(x * t, y * t);
	}
	template<class U> friend const Vec2 operator * (const U& a, const Vec2& vec2)
	{
		return Vec2(vec2.x * a, vec2.y * a);
	}
	// Outer product
	const double operator / (const Vec2& other)
	{
		return x * other.y - y * other.x;
	}
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
	friend std::ostream& operator<<(std::ostream& os, const Vec2& vec2)
	{
		std::cout << vec2.x << " " << vec2.y;
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Vec2& vec2)
	{
		std::cin >> vec2.x >> vec2.y;
		return is;
	}
};

int main()
{
	using namespace std;
	int q;
	cin >> q;
	Vec2 v0, v1, v2, v3;
	Vec2 L1, L2;
	while (cin >> v0 >> v1 >> v2 >> v3)
	{
		L1 = v1 - v0;
		L2 = v3 - v2;
		if (L1 / L2 == 0)
		{
			cout << 2 << endl;
		}
		else if (L1 * L2 == 0)
		{
			cout << 1 << endl;
		}
		else
		{
			cout << 0 << endl;
		}
	}
}