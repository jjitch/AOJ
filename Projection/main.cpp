#include <iostream>
#include <vector>
#include <iomanip>

template<typename T>
class Vec2
{
	
public:
	T x;
	T y;
	Vec2 operator - (Vec2 obj) {
		return Vec2(this->x - obj.x, this->y - obj.y);
	}
	Vec2 operator + (Vec2 obj) {
		return Vec2(this->x + obj.x, this->y + obj.y);
	}
	T operator * (Vec2 obj) {
		return this->x * obj.x + this->y * obj.y;
	}
	template<class U>
	Vec2 operator * (U t) {
		return Vec2(this->x * t, this->y * t);
	}
	Vec2(T x, T y) {
		this->x = x;
		this->y = y;
	}
};

int main() {
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
		std::cout <<std::setprecision(18)<< ans[i].x << " " << ans[i].y << std::endl;
	}
}