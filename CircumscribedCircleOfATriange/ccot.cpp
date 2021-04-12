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
		/*dirA /= Vec2::norm(dirA);
		dirB /= Vec2::norm(dirB);*/
		dirA /= 2048.;
		dirB /= 2048.;
		const double crossA = Vec2::cross(dirA, a.p1);
		const double crossB = Vec2::cross(dirB, b.p1);
		const double x = (dirB.getX() * crossA - dirA.getX() * crossB) / Vec2::cross(dirA, dirB);
		const double y = (dirB.getY() * crossA - dirA.getY() * crossB) / Vec2::cross(dirA, dirB);
		return Vec2(x, y);
	}
};

std::pair<Vec2, double> circumscribedCircle(const Vec2& vertexA, const Vec2& vertexB, const Vec2& vertexC)
{
	Vec2 BA = vertexB - vertexA;
	Vec2 CB = vertexC - vertexB;
	Vec2 AC = vertexA - vertexC;

	double weightA = Vec2::dot(BA, AC) * Vec2::cross(BA, AC) * Vec2::norm(CB);
	double weightB = Vec2::dot(CB, BA) * Vec2::cross(CB, BA) * Vec2::norm(AC);
	double weightC = Vec2::dot(AC, CB) * Vec2::cross(AC, CB) * Vec2::norm(BA);
	double edgeA = Vec2::norm(CB);
	double edgeB = Vec2::norm(AC);
	double edgeC = Vec2::norm(BA);

	Vec2 center = (weightA * vertexA + weightB * vertexB + weightC * vertexC) / (weightA + weightB + weightC);
	double radius = (edgeA * edgeB * edgeC) / (2 * Vec2::cross(BA, AC));
	return { center, abs(radius) };
}

std::pair<Vec2, double> circumscribedCircle2(const Vec2& vertexA, const Vec2& vertexB, const Vec2& vertexC)
{
	Vec2 BA = vertexB - vertexA;
	Vec2 CB = vertexC - vertexB;
	Vec2 AC = vertexA - vertexC;

	double sin2A = sin(2. * (BA.getAngle() - AC.getAngle()));
	double sin2B = sin(2. * (CB.getAngle() - BA.getAngle()));
	double sin2C = sin(2. * (AC.getAngle() - CB.getAngle()));

	double edgeA = Vec2::norm(CB);
	double edgeB = Vec2::norm(AC);
	double edgeC = Vec2::norm(BA);

	Vec2 center = (sin2A * vertexA + sin2B * vertexB + sin2C * vertexC) / (sin2A + sin2B + sin2C);
	double radius = (edgeA * edgeB * edgeC) / (2 * Vec2::cross(BA, AC));
	return { center, abs(radius) };
}

std::pair<Vec2, double> circumscribedCircle3(const Vec2& vertexA, const Vec2& vertexB, const Vec2& vertexC)
{
	const Vec2 BA = vertexB - vertexA;
	const Vec2 CB = vertexC - vertexB;
	const Vec2 AC = vertexA - vertexC;
	const Vec2 midAB = (vertexA + vertexB) / 2.;
	const Vec2 midAC = (vertexA + vertexC) / 2.;
	const Line verticalBisectorAB(midAB, midAB + Vec2::rotate90(BA));
	const Line verticalBisectorAC(midAC, midAC + Vec2::rotate90(AC));
	const Vec2 center = Line::intersect(verticalBisectorAB, verticalBisectorAC);
	const double edgeA = Vec2::norm(CB);
	const double edgeB = Vec2::norm(AC);
	const double edgeC = Vec2::norm(BA);
	const double radius = (edgeA * edgeB * edgeC) / (2 * Vec2::cross(BA, AC));
	return { center, abs(radius) };
}

int main()
{
	using namespace std;
	Vec2 VertexA, VertexB, VertexC;
	cin >> VertexA >> VertexB >> VertexC;
	pair<Vec2, double> ans = circumscribedCircle3(VertexA, VertexB, VertexC);
	cout << setprecision(10) << fixed << ans.first << " " << ans.second << endl;
}

/*
-10000 10000
10000 -10000
1 1
->
-49999999.50000000000000000000 -49999999.50000000000000000000 70710678.82576153362606419250

’Ê‚·‚Ì‘å•Ï‚¾‚Á‚½
*/