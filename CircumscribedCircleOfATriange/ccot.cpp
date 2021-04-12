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
	Vec2(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
	const double getX() const { return x; }
	const double getY() const { return y; }
	const double getAngle() const { return atan(y / x); }
	Vec2& rotate(const double& theta)
	{
		double tmpX = x * cos(theta) - y * sin(theta);
		double tmpY = x * sin(theta) + y * cos(theta);
		x = tmpX;
		y = tmpY;
		return *this;
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
	template<class T> const Vec2 operator * (const T& t) const
	{
		return Vec2(x * t, y * t);
	}
	template<class T> friend const Vec2 operator * (const T& a, const Vec2& vec2)
	{
		return Vec2(vec2.x * a, vec2.y * a);
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
};

class Line
{
	Vec2 p1;
	Vec2 p2;
public:
	Line(Vec2 _p1, Vec2 _p2) :p1(_p1), p2(_p2){}
	
	static Vec2 intersect(const Line& a, const Line& b)
	{
		Vec2 normalA = a.p1 - a.p2;
		Vec2 normalB = b.p1 - b.p2;
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
	double radius = (edgeA * edgeB * edgeC) / (2 *Vec2::cross(BA, AC));
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


int main()
{
	using namespace std;
	Vec2 VertexA, VertexB, VertexC;
	cin >> VertexA >> VertexB >> VertexC;
	pair<Vec2, double> ans = circumscribedCircle(VertexA, VertexB, VertexC);
	cout << setprecision(10) << fixed << ans.first << " " << ans.second << endl;
	ans = circumscribedCircle2(VertexA, VertexB, VertexC);
	cout << setprecision(10) << fixed << ans.first << " " << ans.second << endl;
}