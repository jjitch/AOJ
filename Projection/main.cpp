#include <iostream>

template<typename T>
class Vec2
{
	
public:
	T x;
	T y;
	Vec2 operator - (Vec2 obj) {
		return Vec2(this->x - obj.x, this->y - obj.y);
	}
	T operator * (Vec2 obj) {
		return this->x * obj.x + this->y * obj.y;
	}
	Vec2(T x, T y) {
		this->x = x;
		this->y = y;
	}
};

int main() {
	Vec2<int> a(5, 6);
	Vec2<int> b(3, 7);
	std::cout << a * b << std::endl;
}