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
	const double operator % (const Vec2& other) const
	{
		return x * other.y - y * other.x;
	}
	template<class U> const Vec2 operator / (const U& t) const
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

};

std::pair<Vec2, double> incircle(const Vec2& vertexA, const Vec2& vertexB, const Vec2& vertexC)
{
	double edgeA = sqrt((vertexC - vertexB) * (vertexC - vertexB));
	double edgeB = sqrt((vertexA - vertexC) * (vertexA - vertexC));
	double edgeC = sqrt((vertexB - vertexA) * (vertexB - vertexA));
	Vec2 center = (edgeA * vertexA + edgeB * vertexB + edgeC * vertexC) / (edgeA + edgeB + edgeC);
	double radius = (vertexB - vertexA) % (vertexC - vertexA) / (edgeA + edgeB + edgeC);
	return { center, abs(radius) };
}

int main()
{
	using namespace std;
	Vec2 VertexA, VertexB, VertexC;
	cin >> VertexA >> VertexB >> VertexC;
	pair<Vec2,double> ans = incircle(VertexA, VertexB, VertexC);
	cout << setprecision(10) <<fixed << ans.first << " " << ans.second << endl;
}