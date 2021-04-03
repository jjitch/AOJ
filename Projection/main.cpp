#include <iostream>
#include <vector>
#include <iomanip>
#include <stdlib.h>

template<typename T>
class Vec2
{
	T x;
	T y;
public:
	Vec2() :x(0), y(0) {};
	Vec2(T x, T y)
	{
		this->x = x;
		this->y = y;
	}
	T getX() { return x; }
	T getY() { return y; }
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
	const T operator * (const Vec2& other)
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
	const T operator ^ (const Vec2& other)
	{
		return x * other.y - y * other.x;
	}
	Vec2& operator+=(const Vec2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	Vec2& operator-=(const Vec2& other) {
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
	using V = Vec2<double>;
	V v1, v2;
	cin >> v1 >> v2;
	v2 -= v1;
	int q;
	cin >> q;
	V v;
	while (cin >> v)
	{
		v -= v1;
		cout <<setprecision(18)<< v1 + ((v * v2) / (v2 * v2)) * v2 << endl;;
	}
}