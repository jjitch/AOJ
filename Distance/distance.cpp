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

enum class CCW
{
	COUNTER_CLOCKWISE,
	CLOCKWISE,
	ONLINE_BACK,
	ONLINE_FRONT,
	ON_SEGMENT
};

CCW ccw(const Vec2& a, const Vec2& b)
{
	if (a / b > 0)return CCW::COUNTER_CLOCKWISE;
	if (a / b < 0)return CCW::CLOCKWISE;
	if (a * b < 0)return CCW::ONLINE_BACK;
	if (a * a < b * b)return CCW::ONLINE_FRONT;
	return CCW::ON_SEGMENT;
}

double pointToLine(const Vec2& begin, const Vec2& end, const Vec2& p)
{
	if ((p - begin) * (end - begin) <= 0) return sqrt((p - begin) * (p - begin));
	if ((p - end) * (begin - end) <= 0) return sqrt((p - end) * (p - end));
	return abs((end - begin) / (p - begin)) / sqrt((end - begin) * (end - begin));
}

int main()
{
	using namespace std;
	int q;
	cin >> q;
	Vec2 v0, v1, v2, v3;
	while (cin >> v0 >> v1 >> v2 >> v3)
	{
		CCW v2FromS1 = ccw(v1 - v0, v2 - v0);
		CCW v3FromS1 = ccw(v1 - v0, v3 - v0);
		CCW v0FromS2 = ccw(v3 - v2, v0 - v2);
		CCW v1FromS2 = ccw(v3 - v2, v1 - v2);
		if ((v2FromS1 == CCW::COUNTER_CLOCKWISE && v3FromS1 == CCW::CLOCKWISE) || (v2FromS1 == CCW::CLOCKWISE && v3FromS1 == CCW::COUNTER_CLOCKWISE))
		{
			if ((v0FromS2 == CCW::COUNTER_CLOCKWISE && v1FromS2 == CCW::CLOCKWISE) || (v0FromS2 == CCW::CLOCKWISE && v1FromS2 == CCW::COUNTER_CLOCKWISE))
			{
				cout << setprecision(10) << fixed << 0 << endl;
				continue;
			}
		}
		double ans = 1e9;
		ans = min(ans, pointToLine(v0, v1, v2));
		ans = min(ans, pointToLine(v0, v1, v3));
		ans = min(ans, pointToLine(v2, v3, v0));
		ans = min(ans, pointToLine(v2, v3, v1));
		cout << setprecision(10) << fixed << ans << endl;
	}
}