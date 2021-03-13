#include <iostream>
#include <vector>
#include <string>
#define rep(i,n) for(int i=0;i<n;i++)

class Node
{
public:
	Node(int value_ = 0) :
		prev(NULL), next(NULL), value(value_) {};

private:
	Node* prev;
	Node* next;
	int value;
};

class Nodes
{
public:
	Nodes() : nil(NULL) {};
	void insert(Node* node) {};
private:
	Node* nil;
};

int main() {
	using namespace std;
	int n;
	cin >> n;

}