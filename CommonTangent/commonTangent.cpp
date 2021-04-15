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
	Vec2 getP1() const { return p1; }
	Vec2 getP2() const { return p2; }
	Vec2 normalizedDir() const { return (p2 - p1) / Vec2::norm(p2 - p1); }
	Vec2 normalizedNor() const { return Vec2::rotate90(p2 - p1) / Vec2::norm(p2 - p1); }
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
	Vec2 getCenter() const { return center; }
	double getRadius() const { return radius; }
	friend std::istream& operator >> (std::istream& is, Circle& circle)
	{
		std::cin >> circle.center >> circle.radius;
		return is;
	}
	friend std::ostream& operator << (std::ostream& os, const Circle& cir)
	{
		std::cout << cir.getCenter() << " " << cir.getRadius();
		return os;
	}
};

enum class PAIR_OF_CIRCLES
{
	NOT_CONTACT,
	CIRCUMSCRIBED,
	INTERSECT,
	INSCRIBED,
	INCLUDED
};

PAIR_OF_CIRCLES POC(const Circle& cirA, const Circle& cirB)
{
	double d = Vec2::dot(cirA.getCenter() - cirB.getCenter(), cirA.getCenter() - cirB.getCenter());
	double sumR = (cirA.getRadius() + cirB.getRadius()) * (cirA.getRadius() + cirB.getRadius());
	double subR = (cirA.getRadius() - cirB.getRadius()) * (cirA.getRadius() - cirB.getRadius());
	if (sumR < d)
	{
		return PAIR_OF_CIRCLES::NOT_CONTACT;
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

/* The distance from line to point. When the point is located on the left hand side, the sign is positive. */
double lineToPoint(const Line& line, const Vec2& v)
{
	return Vec2::cross(line.getP2() - line.getP1(), v - line.getP1()) / Vec2::norm(line.getP2() - line.getP1());
}

Vec2 crossPointLines(const Line& lineA, const Line& lineB)
{
	const Vec2 dirA = lineA.getP1() - lineA.getP2();
	const Vec2 dirB = lineB.getP1() - lineB.getP2();
	const double crossA = Vec2::cross(dirA, lineA.getP1());
	const double crossB = Vec2::cross(dirB, lineB.getP1());
	const double x = (dirB.getX() * crossA - dirA.getX() * crossB) / Vec2::cross(dirA, dirB);
	const double y = (dirB.getY() * crossA - dirA.getY() * crossB) / Vec2::cross(dirA, dirB);
	return Vec2(x, y);
}

std::pair<Vec2, Vec2> crossPointsCircleAndLine(const Circle& cir, const Line& line)
{
	const double distFromPoint = -lineToPoint(line, cir.getCenter());
	const Vec2 nor = line.normalizedNor();
	const Vec2 dir = line.normalizedDir();
	const Vec2 crossA = cir.getCenter() + distFromPoint * nor + sqrt(cir.getRadius() * cir.getRadius() - distFromPoint * distFromPoint) * dir;
	const Vec2 crossB = cir.getCenter() + distFromPoint * nor - sqrt(cir.getRadius() * cir.getRadius() - distFromPoint * distFromPoint) * dir;
	return { crossA, crossB };
}

std::pair<Vec2, Vec2> crossPointsCircles(const Circle& cirA, const Circle& cirB)
{
	const Vec2 dir = cirB.getCenter() - cirA.getCenter();
	const double ratio = cirA.getRadius() * cirA.getRadius() - cirB.getRadius() * cirB.getRadius() + Vec2::dot(dir, dir);
	const Vec2 equinox = cirA.getCenter() + ratio * dir / (2. * Vec2::dot(dir, dir));
	const Line bisection(equinox, equinox + Vec2::rotate90(dir));
	return crossPointsCircleAndLine(cirA, bisection);
}

std::pair<Vec2, Vec2> tangentToPoint(const Circle& cir, const Vec2& point)
{
	Circle alongCenterPoint((cir.getCenter() + point) / 2., Vec2::norm(cir.getCenter() - point) / 2.);
	return crossPointsCircles(cir, alongCenterPoint);
}

std::vector<Vec2> commonTangent(const Circle& cirA, const Circle& cirB)
{
	std::vector<Vec2> res;
	std::pair<Vec2, Vec2> pairTangent;
	const Vec2& cA = cirA.getCenter();
	const Vec2& cB = cirB.getCenter();
	const double& rA = cirA.getRadius();
	const double& rB = cirB.getRadius();
	switch (POC(cirA, cirB))
	{
	case PAIR_OF_CIRCLES::NOT_CONTACT: {
		pairTangent = tangentToPoint(cirA, (rB * cA + rA * cB) / (rA + rB));
		res.push_back(pairTangent.first);
		res.push_back(pairTangent.second);
		if (rA != rB) { pairTangent = tangentToPoint(cirA, (-rB * cA + rA * cB) / (rA - rB)); }
		else { pairTangent = crossPointsCircleAndLine(cirA, Line(cA, Vec2::rotate90(cB - cA) + cA)); }
		res.push_back(pairTangent.first);
		res.push_back(pairTangent.second);
		break;
	}
	case PAIR_OF_CIRCLES::CIRCUMSCRIBED: {
		pairTangent = tangentToPoint(cirA, (rB * cA + rA * cB) / (rA + rB));
		res.push_back(pairTangent.first);
		if (rA != rB) { pairTangent = tangentToPoint(cirA, (-rB * cA + rA * cB) / (rA - rB)); }
		else { pairTangent = crossPointsCircleAndLine(cirA, Line(cA, Vec2::rotate90(cB - cA) + cA)); }
		res.push_back(pairTangent.first);
		res.push_back(pairTangent.second);
		break;
	}
	case PAIR_OF_CIRCLES::INTERSECT: {
		if (rA != rB) { pairTangent = tangentToPoint(cirA, (-rB * cA + rA * cB) / (rA - rB)); }
		else { pairTangent = crossPointsCircleAndLine(cirA, Line(cA, Vec2::rotate90(cB - cA) + cA)); }
		res.push_back(pairTangent.first);
		res.push_back(pairTangent.second);
		break;
	}
	case PAIR_OF_CIRCLES::INSCRIBED: {
		pairTangent = crossPointsCircles(cirA, cirB);
		res.push_back(pairTangent.first);
		break;
	}
	case PAIR_OF_CIRCLES::INCLUDED: { break; }
	default: { break; }
	}
	return res;
}

int main()
{
	using namespace std;
	Circle c1, c2;
	cin >> c1 >> c2;
	vector<Vec2> ans = commonTangent(c1, c2);
	sort(ans.begin(), ans.end());
	cout << setprecision(10) << fixed;
	for_each(ans.cbegin(), ans.cend(), [](const Vec2& v) {cout << v << endl; });
}