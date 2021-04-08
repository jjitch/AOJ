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

const double INF = 10000.;

double closestPair(std::vector<Vec2>::iterator a, size_t n)
{
	if (n <= 1) return INF;
	size_t m = n / 2;
	double x = a[m].getX();
	double d = std::min(closestPair(a, m), closestPair(a + m, n - m));
	std::inplace_merge(a, a + m, a + n, [](const Vec2& a, const Vec2& b) {return a.getY() < b.getY(); });

	std::vector<Vec2> b;
	for (size_t i = 0; i < n; i++)
	{
		if (std::abs(a[i].getX() - x) >= d) continue;
		for (size_t j = 0; j < b.size(); j++)
		{
			Vec2 v = a[i] - b[b.size() - 1 - j];
			if (std::abs(v.getY()) >= d) break;
			d = std::sqrt(v * v);
		}
		b.push_back(a[i]);
	}
	return d;
}

int main()
{
	using namespace std;
	size_t n;
	cin >> n;
	vector<Vec2> vv(n);
	for (size_t i = 0; i < n; i++) cin >> vv[i];
	sort(vv.begin(), vv.end());
	double ans = closestPair(vv.begin(), n);
	cout << setprecision(10) << fixed << ans << endl;
}