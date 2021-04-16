#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

constexpr double EPS = 1e-6;

class Vec2
{
	double x;
	double y;
public:
	Vec2() :x(0), y(0) {};
	Vec2(double _x, double _y) : x(_x), y(_y) {}
	const double getX() const { return x; }
	const double getY() const { return y; }
	const double getAngle() const { return atan2(y, x); }
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

class Segment
{
	Vec2 p1;
	Vec2 p2;
public:
	Segment() :p1(Vec2()), p2(Vec2()) {}
	Segment(Vec2 _p1, Vec2 _p2) :p1(_p1), p2(_p2) {}
	Segment& operator = (const Segment& other)
	{
		p1 = other.p1;
		p2 = other.p2;
		return *this;
	}
	Vec2 getP1() const { return p1; }
	Vec2 getP2() const { return p2; }
	Vec2 normalizedDir() const { return (p2 - p1) / Vec2::norm(p2 - p1); }
	Vec2 normalizedNor() const { return Vec2::rotate90(p2 - p1) / Vec2::norm(p2 - p1); }
	friend std::istream& operator >> (std::istream& is, Segment& line)
	{
		std::cin >> line.p1 >> line.p2;
		return is;
	}
	friend std::ostream& operator << (std::ostream& os, const Segment& line)
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

/*
Indicate the position of target point against the directed segment.
Segment includes initial point but not terminal point.
*/
enum class CCW
{
	COUNTER_CLOCKWISE,
	CLOCKWISE,
	ONLINE_BACK,
	ONLINE_FRONT,
	ON_SEGMENT
};
CCW ccw(const Segment& seg, const Vec2& target)
{
	const Vec2& start = seg.getP1();
	const Vec2& end = seg.getP2();
	if (Vec2::cross(end - start, target - start) > EPS)return CCW::COUNTER_CLOCKWISE;
	if (Vec2::cross(end - start, target - start) < -EPS)return CCW::CLOCKWISE;
	if (Vec2::dot(end - start, target - start) < -EPS)return CCW::ONLINE_BACK;
	if (Vec2::dot(end - start, end - start) <= Vec2::dot(target - start, target - start))return CCW::ONLINE_FRONT;
	return CCW::ON_SEGMENT;
}

enum class ISINSIDE
{
	INSIDE,
	OUTSIDE,
	ON_SEGMENT
};
ISINSIDE isInside(const std::vector<Vec2>& poly, const Vec2& query)
{
	int windingNumber = 0;
	std::size_t n = poly.size();
	for (std::size_t i = 0; i < n; i++)
	{
		CCW position;
		double upper;
		double lower;
		position = ccw({ poly[i], poly[(i + 1) % n] }, query);
		upper = std::max(poly[i].getY(), poly[(i + 1) % n].getY());
		lower = std::min(poly[i].getY(), poly[(i + 1) % n].getY());
		if (position == CCW::ON_SEGMENT) return ISINSIDE::ON_SEGMENT;
		if (position == CCW::COUNTER_CLOCKWISE && lower <= query.getY() && query.getY() < upper) windingNumber++;
		if (position == CCW::CLOCKWISE && lower <= query.getY() && query.getY() < upper) windingNumber--;
	}
	if (windingNumber == 0) return ISINSIDE::OUTSIDE;
	else return ISINSIDE::INSIDE;
}

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

double polygonArea(const std::vector<Vec2>& poly)
{
	double res = 0;
	std::size_t n = poly.size();
	for (size_t i = 0; i < n; i++) { res += Vec2::cross(poly[i], poly[(i + 1) % n]); }
	res /= 2.;
	return res;
}

double splitCircle(const Circle& cir, const Segment& seg)
{
	double res = 0;
	const Vec2 p1 = seg.getP1() - cir.getCenter();
	const Vec2 p2 = seg.getP2() - cir.getCenter();
	const double cross = Vec2::cross(p1, p2) / 2.;
	if (cross == 0 && Vec2::dot(p1, p2) < 0) { return cir.getRadius() * cir.getRadius() * M_PI / 2.; }
	res += p1.getAngle() - p2.getAngle();
	if (cross > 0 && (p1.getY() <= 0 || p2.getY() >= 0)) res += 2. * M_PI;
	if (cross < 0 && (p1.getY() <= 0 && p2.getY() >= 0)) res += 2. * M_PI;
	res *= cir.getRadius() * cir.getRadius() / 2.;
	res += cross;
	return res;
}

/*Cut the convex by given line. And then return the trimed convex on the left hand side.*/
std::vector<Vec2> convexCut(const std::vector<Vec2>& poly, const Line& line)
{
	std::vector<Vec2> res;
	std::size_t n = poly.size();
	for (size_t i = 0; i < n; i++)
	{
		double before = Vec2::cross(line.getP2() - line.getP1(), poly[i] - line.getP1());
		double after = Vec2::cross(line.getP2() - line.getP1(), poly[(i + 1) % n] - line.getP1());
		if (before >= 0)
		{
			res.push_back(poly[i]);
			if (after < 0)
			{
				res.push_back(crossPointLines(Line(poly[(i + 1) % n], poly[i]), line));
			}
		}
		else if (after > 0)
		{
			res.push_back(crossPointLines(Line(poly[(i + 1) % n], poly[i]), line));
		}
	}
	return res;
}

std::vector<Vec2> intersectionPoints(const Circle& cir, const Line& line)
{
	const double distFromPoint = -lineToPoint(line, cir.getCenter());
	const Vec2 nor = line.normalizedNor();
	const Vec2 dir = line.normalizedDir();
	if (abs(distFromPoint) == cir.getRadius())
	{
		return { cir.getCenter() + distFromPoint * nor };
	}
	else if (abs(distFromPoint) > cir.getRadius())
	{
		return {};
	}
	const Vec2 crossA = cir.getCenter() + distFromPoint * nor - sqrt(cir.getRadius() * cir.getRadius() - distFromPoint * distFromPoint) * dir;
	const Vec2 crossB = cir.getCenter() + distFromPoint * nor + sqrt(cir.getRadius() * cir.getRadius() - distFromPoint * distFromPoint) * dir;
	return { crossA, crossB };
}

std::vector<Vec2> intersectionPoints(const Circle& cir, const Segment& seg)
{
	const double distFromPoint = -lineToPoint(Line(seg.getP1(), seg.getP2()), cir.getCenter());
	if (abs(distFromPoint) > cir.getRadius()) { return {}; }
	const Vec2 nor = seg.normalizedNor();
	const Vec2 dir = seg.normalizedDir();
	const Vec2 halfOfChord = sqrt(cir.getRadius() * cir.getRadius() - distFromPoint * distFromPoint) * dir;
	const Vec2 crossA = cir.getCenter() + distFromPoint * nor - halfOfChord;
	const Vec2 crossB = cir.getCenter() + distFromPoint * nor + halfOfChord;
	if (abs(distFromPoint) == cir.getRadius()) { return { crossA }; }
	std::vector<Vec2> res;
	if (ccw(seg, crossA) != CCW::ONLINE_BACK && ccw(seg, crossA) != CCW::ONLINE_FRONT) res.push_back(crossA);
	if (ccw(seg, crossB) != CCW::ONLINE_BACK && ccw(seg, crossB) != CCW::ONLINE_FRONT) res.push_back(crossB);
	return res;
}

std::vector<Vec2> intersectionPoints(const Circle& cirA, const Circle& cirB)
{
	const Vec2 dir = cirB.getCenter() - cirA.getCenter();
	const double ratio = cirA.getRadius() * cirA.getRadius() - cirB.getRadius() * cirB.getRadius() + Vec2::dot(dir, dir);
	const Vec2 equinox = cirA.getCenter() + ratio * dir / (2. * Vec2::dot(dir, dir));
	const Line bisection(equinox, equinox + Vec2::rotate90(dir));
	return intersectionPoints(cirA, bisection);
}

std::vector<Vec2> tangentToPoint(const Circle& cir, const Vec2& point)
{
	Circle alongCenterPoint((cir.getCenter() + point) / 2., Vec2::norm(cir.getCenter() - point) / 2.);
	return intersectionPoints(cir, alongCenterPoint);
}

std::vector<Vec2> commonTangent(const Circle& cirA, const Circle& cirB)
{
	std::vector<Vec2> res;
	std::vector<Vec2> tangents;
	const Vec2& cA = cirA.getCenter();
	const Vec2& cB = cirB.getCenter();
	const double& rA = cirA.getRadius();
	const double& rB = cirB.getRadius();
	switch (POC(cirA, cirB))
	{
	case PAIR_OF_CIRCLES::NOT_CONTACT: {
		tangents = tangentToPoint(cirA, (rB * cA + rA * cB) / (rA + rB));
		res.push_back(tangents[0]);
		res.push_back(tangents[1]);
		if (rA != rB) { tangents = tangentToPoint(cirA, (-rB * cA + rA * cB) / (rA - rB)); }
		else { tangents = intersectionPoints(cirA, Line(cA, Vec2::rotate90(cB - cA) + cA)); }
		res.push_back(tangents[0]);
		res.push_back(tangents[1]);
		break;
	}
	case PAIR_OF_CIRCLES::CIRCUMSCRIBED: {
		tangents = tangentToPoint(cirA, (rB * cA + rA * cB) / (rA + rB));
		res.push_back(tangents[0]);
		if (rA != rB) { tangents = tangentToPoint(cirA, (-rB * cA + rA * cB) / (rA - rB)); }
		else { tangents = intersectionPoints(cirA, Line(cA, Vec2::rotate90(cB - cA) + cA)); }
		res.push_back(tangents[0]);
		res.push_back(tangents[1]);
		break;
	}
	case PAIR_OF_CIRCLES::INTERSECT: {
		if (rA != rB) { tangents = tangentToPoint(cirA, (-rB * cA + rA * cB) / (rA - rB)); }
		else { tangents = intersectionPoints(cirA, Line(cA, Vec2::rotate90(cB - cA) + cA)); }
		res.push_back(tangents[0]);
		res.push_back(tangents[1]);
		break;
	}
	case PAIR_OF_CIRCLES::INSCRIBED: {
		tangents = intersectionPoints(cirA, cirB);
		res.push_back(tangents[0]);
		break;
	}
	case PAIR_OF_CIRCLES::INCLUDED: { break; }
	default: { break; }
	}
	return res;
}

double intersectionArea(const Circle& cir, const std::vector<Vec2> poly)
{
	double res = 0;
	std::vector<std::vector<Vec2>> intersections;
	std::vector<Vec2> partial;
	const std::size_t n = poly.size();
	Vec2 prev;
	Vec2 next;
	for (std::size_t i = 0; i < n; i++)
	{
		prev = poly[i];
		next = poly[(i + 1) % n];

		if (Vec2::norm(prev - cir.getCenter()) < cir.getRadius()) partial.push_back(prev);
		std::vector<Vec2> intersectionPoint = intersectionPoints(cir, Segment(prev, next));
		std::for_each(intersectionPoint.cbegin(), intersectionPoint.cend(), [&](const Vec2& v) {partial.push_back(v); });
		if (Vec2::norm(next - cir.getCenter()) > cir.getRadius())
		{
			if (partial.size() > 1) intersections.push_back(partial);
			partial.clear();
		}
	}
	//if (partial.size() > 1) intersections.push_back(partial);
	if (Vec2::norm(poly.front() - cir.getCenter()) <= cir.getRadius())
	{
		intersections.push_back(partial);
		const std::vector<Vec2> front = intersections.front();
		std::vector<Vec2> back = intersections.back();
		back.insert(back.end(), front.begin(), front.end());
		intersections.front() = back;
		intersections.pop_back();
	}
	// 
	if (intersections.size() == 0)
	{
		if (Vec2::norm(poly.front() - cir.getCenter()) <= cir.getRadius()) return polygonArea(poly);
		else
		{
			if (isInside(poly, cir.getCenter()) == ISINSIDE::INSIDE) return cir.getRadius() * cir.getRadius() * M_PI;
			else return 0.;
		}
	}

	std::for_each(intersections.cbegin(), intersections.cend(), [&](const std::vector<Vec2> fragment) {
		if (fragment.size() > 1)
		{
			res += polygonArea(fragment);
			res += splitCircle(cir, { fragment.front(), fragment.back() });
		}});
	res = fmod(res, cir.getRadius() * cir.getRadius() * M_PI);
	return res;
}


int main()
{
	using namespace std;
	size_t n;
	double r;
	cin >> n >> r;
	vector<Vec2> polygon(n);
	for (size_t i = 0; i < n; i++) cin >> polygon[i];
	Circle circle{ {0,0}, r };
	double area = intersectionArea(circle, polygon);
	cout << setprecision(12) << fixed << area << endl;
}