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

int main()
{
	using namespace std;
	size_t n;
	cin >> n;
	vector<Vec2> points(n);
	for (size_t i = 0; i < n; i++) cin >> points[i];

	sort(points.begin(), points.end(), [](const Vec2& a, const Vec2& b) {return a.getY() < b.getY() || (!(b.getY() < a.getY()) && a.getX() < b.getX()); });

	vector<Vec2> right;
	right.push_back(*points.cbegin());
	right.push_back(*(points.cbegin() + 1));
	for_each(points.cbegin() + 2, points.cend(), [&](const Vec2& next) {
		while (right.size() > 1)
		{
			if (ccw(*(right.cend() - 2), right.back(), next) == CCW::CLOCKWISE)
			{
				right.pop_back();
				continue;
			}
			break;
		}
		right.push_back(next);
			 });

	vector<Vec2> left;
	left.push_back(points.back());
	left.push_back(*(points.cend() - 2));
	for_each(points.crbegin() + 2, points.crend(), [&](const Vec2& next) {
		while (left.size() > 1)
		{
			if (ccw(*(left.cend() - 2), left.back(), next) == CCW::CLOCKWISE)
			{
				left.pop_back();
				continue;
			}
			break;
		}
		left.push_back(next);
			 });

	cout << right.size() + left.size() - 2 << endl;
	for_each(right.begin(), right.end() - 1, [](const Vec2& v) {cout << v << endl; });
	for_each(left.begin(), left.end() - 1, [](const Vec2& v) {cout << v << endl; });
}