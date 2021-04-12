#define _USE_MATH_DEFINES

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
	Vec2(double _x, double _y) : x(_x), y(_y) {}
	const double getX() const { return x; }
	const double getY() const { return y; }
	const double getAngle() const { return atan(y / x); }
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
	template<class T> const Vec2 operator * (const T& t) const
	{
		return Vec2(x * t, y * t);
	}
	template<class T> friend const Vec2 operator * (const T& t, const Vec2& vec2)
	{
		return Vec2(vec2.x * t, vec2.y * t);
	}
	template<class T> const Vec2 operator / (const T& t) const
	{
		return Vec2(x / t, y / t);
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
	template<class T> Vec2& operator*=(const T& t)
	{
		x *= t;
		y *= t;
		return *this;
	}
	template<class T> Vec2& operator/=(const T& t)
	{
		x /= t;
		y /= t;
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

	static double dot(const Vec2& a, const Vec2& b) { return a.x * b.x + a.y * b.y; }
	static double cross(const Vec2& a, const Vec2& b) { return a.x * b.y - a.y * b.x; }
	static double norm(const Vec2& a) { return sqrt(dot(a, a)); }
	static Vec2 rotate(const Vec2& a, const double& theta) { return Vec2(a.x * cos(theta) - a.y * sin(theta), a.x * sin(theta) + a.y * cos(theta)); }
	static Vec2 rotate90(const Vec2& a) { return Vec2(-a.y, a.x); }
};

class Line
{
	Vec2 p1;
	Vec2 p2;
public:
	Line(Vec2 _p1, Vec2 _p2) :p1(_p1), p2(_p2) {}

	static Vec2 intersect(const Line& a, const Line& b)
	{
		Vec2 dirA = a.p1 - a.p2;
		Vec2 dirB = b.p1 - b.p2;
		const double crossA = Vec2::cross(dirA, a.p1);
		const double crossB = Vec2::cross(dirB, b.p1);
		const double x = (dirB.getX() * crossA - dirA.getX() * crossB) / Vec2::cross(dirA, dirB);
		const double y = (dirB.getY() * crossA - dirA.getY() * crossB) / Vec2::cross(dirA, dirB);
		return Vec2(x, y);
	}
};

double diameterOfConvexPolygon(const std::vector<Vec2>& poly, const std::size_t& n)
{
	double diameter = 0.;
	std::size_t farest;
	for (size_t i = 0; i < n; i++)
	{
		double distance = Vec2::norm(poly[0] - poly[i]);
		if (distance > diameter)
		{
			diameter = distance;
			farest = i;
		}
	}
	std::pair<Vec2, Vec2> antipodal = { poly[0], poly[farest] };
	size_t i = 0;
	size_t j = farest;
	do
	{
		j %= n;
		if (Vec2::cross(poly[i + 1] - poly[i], poly[(j + 1) % n] - poly[j])<0)
		{

		}
	} while (!(j == 0 && i == farest));
	return diameter;
}

int main()
{
	using namespace std;
	size_t n;
	cin >> n;
	vector<Vec2> polygon(n);
	for (size_t i = 0; i < n; i++) cin >> polygon[i];
	double d = diameterOfConvexPolygon(polygon, n);
	cout << setprecision(10) << fixed << d << endl;
}
