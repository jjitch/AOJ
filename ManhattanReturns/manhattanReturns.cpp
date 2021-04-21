#include <iostream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <queue>
#include <map>
#include <cassert>


std::map<int, size_t> m;

enum class OPERATION
{
	INSERT = 0,
	SEARCH = 1,
	ERASE = 2
};

template<class T>
class SegTree
{
	size_t numLeaf;
	std::vector<T> nodes;
	T subQuery(size_t queryLeft, size_t queryRight, size_t index, size_t subLeft, size_t subRight)
	{
		if (subRight <= queryLeft || queryRight <= subLeft)
		{
			return 0;
		}
		else if (queryLeft <= subLeft && subRight <= queryRight)
		{
			return nodes[index];
		}
		else
		{
			T valLeft = subQuery(queryLeft, queryRight, 2 * index + 1, subLeft, (subLeft + subRight) / 2);
			T valRight = subQuery(queryLeft, queryRight, 2 * index + 2, (subLeft + subRight) / 2, subRight);
			return valLeft + valRight;
		}
	};
public:
	SegTree(size_t _n)
	{
		size_t x = 1;
		while (x < _n)
		{
			x *= 2;
		}
		numLeaf = x;
		nodes.resize(2 * numLeaf - 1, 0);
	}
	void plusOne(size_t i)
	{
		size_t index = numLeaf - 1 + i;
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
		size_t index = numLeaf - 1 + i;
		while (index > 0)
		{
			nodes[index]--;
			index--;
			index /= 2;
		}
		nodes[0]--;
	}
	T getSum(size_t queryLeft, size_t queryRight) { return subQuery(queryLeft, queryRight, 0, 0, numLeaf); }

	friend std::ostream& operator<<(std::ostream& os, const SegTree& st)
	{
		std::cout << "------------\n";
		std::cout << "number of leaves: " << st.numLeaf << "\n";
		std::size_t splitFlag = 0;
		for (std::size_t i = 0; i < st.nodes.size(); i++)
		{
			std::cout << st.nodes[i] << " ";
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

class eventQueue
{
	int order;
	OPERATION ope;
	int x1, y1, x2, y2;
public:
	eventQueue(int _order, OPERATION _ope, int _x1, int _y1, int _x2, int _y2) :
		order(_order), ope(_ope), x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
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
	template<class T>
	std::size_t execute(SegTree<T>& st)
	{
		std::size_t res = 0;
		if (ope == OPERATION::INSERT)
		{
			st.plusOne(m[y1]);
		}
		else if (ope == OPERATION::ERASE)
		{
			st.minusOne(m[y1]);
		}
		else
		{
			res = st.getSum(m[y1], m[y2]);
		}
		return res;
	}
};

void testSegTree()
{
	using namespace std;
	SegTree<size_t> st(4);
	st.plusOne(0);
	st.plusOne(1);
	st.plusOne(5);
	cout << st << endl;
	//assert(st.getSum(0, 7) == 2);
}

int main()
{
	using namespace std;
	auto c = [](eventQueue l, eventQueue r) {return l > r; };
	size_t n;
	cin >> n;
	priority_queue<eventQueue, vector<eventQueue>, decltype(c)> pq(c);
	set<int> s;
	int x1, y1, x2, y2;
	for (size_t i = 0; i < n; i++)
	{
		cin >> x1 >> y1 >> x2 >> y2;
		if (x1 == x2)
		{
			pq.emplace(x1, OPERATION::SEARCH, x1, min(y1, y2), x2, max(y1, y2));
		}
		else
		{
			pq.emplace(min(x1, x2), OPERATION::INSERT, min(x1, x2), y1, max(x1, x2), y2);
			pq.emplace(max(x1, x2), OPERATION::ERASE, min(x1, x2), y1, max(x1, x2), y2);
		}
		s.insert(y1);
		s.insert(y2);
	}
	size_t compressedIndex = 0;
	for (auto y = s.begin(); y!=s.end();y++)
	{
		m.emplace(*y, compressedIndex);
		compressedIndex++;
	}
	SegTree<size_t> horizons(compressedIndex);
	size_t ans = 0;
	while (!pq.empty())
	{
		eventQueue q = pq.top();
		pq.pop();
		ans += q.execute(horizons);
	}
	cout << ans << endl;
}