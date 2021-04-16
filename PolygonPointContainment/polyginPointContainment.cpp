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

enum class CCW
{
	COUNTER_CLOCKWISE,
	CLOCKWISE,
	ONLINE_BACK,
	ONLINE_FRONT,
	ON_SEGMENT
};

CCW ccw(const Vec2& start, const Vec2& end, const Vec2& subject)
{
	if ((end - start) / (subject - start) > 0)return CCW::COUNTER_CLOCKWISE;
	if ((end - start) / (subject - start) < 0)return CCW::CLOCKWISE;
	if ((end - start) * (subject - start) < 0)return CCW::ONLINE_BACK;
	if ((end - start) * (end - start) < (subject - start) * (subject - start))return CCW::ONLINE_FRONT;
	return CCW::ON_SEGMENT;
}

enum class ISINSIDE
{
	INSIDE,
	OUTSIDE,
	ON_SEGMENT
};

ISINSIDE isInside(const std::vector<Vec2>& poly, const Vec2& query)
{
	int windingNumber = 0;
	std::size_t n = poly.size();
	for (std::size_t i = 0; i < n; i++)
	{
		CCW position;
		double upper;
		double lower;
		position = ccw(poly[i], poly[(i + 1)%n], query);
		upper = std::max(poly[i].getY(), poly[(i + 1)%n].getY());
		lower = std::min(poly[i].getY(), poly[(i + 1)%n].getY());
		if (position == CCW::ON_SEGMENT) return ISINSIDE::ON_SEGMENT;
		if (position == CCW::COUNTER_CLOCKWISE && lower <= query.getY() && query.getY() < upper) windingNumber++;
		if (position == CCW::CLOCKWISE && lower <= query.getY() && query.getY() < upper) windingNumber--;
	}
	if (windingNumber == 0) return ISINSIDE::OUTSIDE;
	else return ISINSIDE::INSIDE;
}

int main()
{
	using namespace std;
	size_t n;
	cin >> n;
	vector<Vec2> vertex(n);
	for (size_t i = 0; i < n; i++) cin >> vertex[i];
	size_t q;
	cin >> q;
	Vec2 query;
	while (cin >> query)
	{
		switch (isInside(vertex, query))
		{
		case ISINSIDE::INSIDE:
			cout << 2 << endl;
			break;
		case ISINSIDE::ON_SEGMENT:
			cout << 1 << endl;
			break;
		case ISINSIDE::OUTSIDE:
			cout << 0 << endl;
			break;
		default:
			break;
		}
	}
}