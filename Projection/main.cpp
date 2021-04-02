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
	double x1, y1, x2, y2;
	std::cin >> x1 >> y1 >> x2 >> y2;
	Vec2<double> p1(x1, y1);
	Vec2<double> p2 = Vec2<double>(x2, y2) - p1;
	int q;
	std::cin >> q;
	std::vector<Vec2<double>> ans(q,Vec2<double>(0,0));
	for (int i = 0; i < q; i++)
	{
		double x, y;
		std::cin >> x >> y;
		Vec2<double> p = Vec2<double>(x, y) - p1;
		ans[i] = p1 + p2 * ((p * p2) / (p2 * p2));
	}
	for (int i = 0; i < q; i++) {
		std::cout <<std::setprecision(18)<< ans[i] << std::endl;
	}
}