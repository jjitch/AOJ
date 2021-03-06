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
	double a = 0.7;
	std::cout << std::setprecision(2) << a << std::endl;
}