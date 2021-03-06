#pragma once
class TestClass
{
	int x;
	int y;
public:
	TestClass(int x, int y) {
		this->x = x;
		this->y = y;
	}
	int getX() {
		return this->x;
	}
	int getY() {
		return this->y;
	}
};

