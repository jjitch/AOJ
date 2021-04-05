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
	size_t n;
	cin >> n;
	vector<Vec2> v(n);
	for (size_t i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	bool isConvex = true;
	for (size_t i = 0; i < n-2; i++)
	{
		if ((v[i + 1] - v[i]) / (v[i + 2] - v[i + 1]) < 0)
		{
			isConvex = false;
		}
	}
	if ((v[n - 1] - v[n - 2]) / (v[0] - v[n - 1]) < 0)isConvex = false;
	if ((v[0] - v[n - 1]) / (v[1] - v[0]) < 0)isConvex = false;
	cout << isConvex << endl;
}