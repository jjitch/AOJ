#include <iostream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <queue>
#include <map>

enum class OPERATION
{
	INSERT = 0,
	SEARCH = 1,
	ERASE = 2
};

template<class T>
class SegTree
{
public:
	size_t n;
	std::vector<T> nodes;
public:
	SegTree(size_t _n)
	{
		size_t x = 1;
		while (x < _n)
		{
			x *= 2;
		}
		n = x;
		nodes.resize(2 * n - 1, 0);
	}
	void plusOne(size_t i)
	{
		size_t index = n - 1 + i;
		while (index > 0)
		{
			nodes[index]++;
			index--;
			index /= 2;
		}
		nodes[0]++;
	}
	void minusOne(size_t i)
	{
		size_t index = n - 1 + i;
		while (index > 0)
		{
			nodes[index]--;
			index--;
			index /= 2;
		}
		nodes[0]--;
	}
	T getSum(size_t queryLeft, size_t queryRight) { return subQuery(queryLeft, queryRight, 0, 0, n); };
	T subQuery(size_t queryLeft, size_t queryRight, size_t depth, size_t subLeft, size_t subRight) {
		return 1;
	};
	friend std::ostream& operator<<(std::ostream& os, const SegTree& st)
	{
		std::cout << "------------\n";
		std::cout << "number of leaves: " << st.n << "\n";
		std::size_t splitFlag = 0;
		for (std::size_t i = 0; i < st.nodes.size(); i++)
		{
			std::cout << st.nodes[i]<<" ";
			if (i == splitFlag)
			{
				std::cout << "\n";
				splitFlag = 2 * (splitFlag + 1);
			}
		}
		std::cout << "------------\n";
		return os;
	}
};

struct eventQueue
{
	int order;
	OPERATION ope;
	int x1, y1, x2, y2;
	eventQueue(int _order, OPERATION _ope, int _x1, int _y1, int _x2, int _y2) :
		order(_order), ope(_ope), x1(_x1), y1(_y1), x2(_x2), y2(_y2)
	{}
	bool operator < (eventQueue rhs)
	{
		if (order != rhs.order)
		{
			return order < rhs.order;
		}
		else
		{
			return (int)ope < (int)rhs.ope;
		}
	}
	bool operator > (eventQueue rhs)
	{
		if (order != rhs.order)
		{
			return order > rhs.order;
		}
		else
		{
			return (int)ope > (int)rhs.ope;
		}
	}
	std::size_t execute()
	{
		std::size_t res = 0;
		if (ope == OPERATION::INSERT)
		{

		}
		else if (ope == OPERATION::ERASE)
		{

		}
		else
		{

		}
		return res;
	}
};


void testSegTree()
{
	using namespace std;
	SegTree<size_t> st(9);
	st.plusOne(0);
	st.plusOne(4);
	st.plusOne(8);
	st.plusOne(1);
	st.minusOne(4);
	cout << st << endl;
}


int main()
{
	using namespace std;
	testSegTree();
}