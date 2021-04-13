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

	const Vec2 operator + (const Vec2& other) const { return Vec2(x + other.x, y + other.y); }
	const Vec2 operator - (const Vec2& other) const { return Vec2(x - other.x, y - other.y); }
	template<class T> const Vec2 operator * (const T& t) const { return Vec2(x * t, y * t); }
	template<class T> friend const Vec2 operator * (const T& t, const Vec2& vec2) { return Vec2(vec2.x * t, vec2.y * t); }
	template<class T> const Vec2 operator / (const T& t) const { return Vec2(x / t, y / t); }

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
	Line() :p1(Vec2()), p2(Vec2()) {}
	Line(Vec2 _p1, Vec2 _p2) :p1(_p1), p2(_p2) {}
	Line& operator = (const Line& other)
	{
		p1 = other.p1;
		p2 = other.p2;
		return *this;
	}
	Vec2 normalizedDir() const { return (p2 - p1) / Vec2::norm(p2 - p1); }
	Vec2 normalizedNor() const { return Vec2::rotate90(p2 - p1) / Vec2::norm(p2 - p1); }

	// The distance from line to point. When the point is located on the left hand side, the sign is positive.
	double toPoint(const Vec2& v) const
	{
		return Vec2::cross(p2 - p1, v - p1) / Vec2::norm(p2 - p1);
	}
	// The intersection of two lines.
	static Vec2 intersection(const Line& a, const Line& b)
	{
		Vec2 dirA = a.p1 - a.p2;
		Vec2 dirB = b.p1 - b.p2;
		const double crossA = Vec2::cross(dirA, a.p1);
		const double crossB = Vec2::cross(dirB, b.p1);
		const double x = (dirB.getX() * crossA - dirA.getX() * crossB) / Vec2::cross(dirA, dirB);
		const double y = (dirB.getY() * crossA - dirA.getY() * crossB) / Vec2::cross(dirA, dirB);
		return Vec2(x, y);
	}

	friend std::istream& operator >> (std::istream& is, Line& line)
	{
		std::cin >> line.p1 >> line.p2;
		return is;
	}
	friend std::ostream& operator << (std::ostream& os, const Line& line)
	{
		std::cout << line.p1 << " " << line.p2;
		return os;
	}
};

class Circle
{
	Vec2 center;
	double radius;
public:
	Circle() :center(Vec2()), radius(0) {}
	Circle(Vec2 _c, double _r) :center(_c), radius(_r) {}
	Vec2 getCentor() { return center; }
	double getRadius() { return radius; }
	std::pair<Vec2, Vec2> crossPointsToLine(const Line& line) const
	{
		const double distFromPoint = -line.toPoint(center);
		const Vec2 nor = line.normalizedNor();
		const Vec2 dir = line.normalizedDir();
		const Vec2 cross1 = center + distFromPoint * nor + sqrt(radius * radius - distFromPoint * distFromPoint) * dir;
		const Vec2 cross2 = center + distFromPoint * nor - sqrt(radius * radius - distFromPoint * distFromPoint) * dir;
		return { std::min(cross1,cross2), std::max(cross1,cross2) };
	}
	std::pair<Vec2, Vec2> crossPointsToCircle(const Circle& cir) const
	{
		const Vec2 dir = cir.center - center;
		const double ratio = radius * radius - cir.radius * cir.radius + Vec2::dot(dir, dir);
		const Vec2 equinox = center + ratio * dir / (2. * Vec2::dot(dir, dir));
		const Line bisection(equinox, equinox + Vec2::rotate90(dir));
		return crossPointsToLine(bisection);
	}
	std::pair<Vec2, Vec2> tangentToPoint(const Vec2& point) const
	{
		Circle alongCenterPoint((center + point) / 2., Vec2::norm(center - point) / 2.);
		return crossPointsToCircle(alongCenterPoint);
	}
	friend std::istream& operator >> (std::istream& is, Circle& circle)
	{
		std::cin >> circle.center >> circle.radius;
		return is;
	}
};

int main()
{
	using namespace std;
	Vec2 p;
	Circle c;
	cin >> p >> c;
	pair<Vec2, Vec2> ans = c.tangentToPoint(p);
	cout << setprecision(10) << fixed;
	cout << ans.first << endl;
	cout << ans.second << endl;
}