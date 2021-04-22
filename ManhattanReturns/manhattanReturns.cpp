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

std::map<int, size_t> compressor;

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
};

class eventOperator
{
	int order;
	OPERATION ope;
	int x1, y1, x2, y2;
public:
	eventOperator(int _order, OPERATION _ope, int _x1, int _y1, int _x2, int _y2) :
		order(_order), ope(_ope)
	{
		x1 = std::min(_x1, _x2);
		y1 = std::min(_y1, _y2);
		x2 = std::max(_x1, _x2);
		y2 = std::max(_y1, _y2);
	}
	bool operator > (const eventOperator& rhs) const 
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
			st.plusOne(compressor[y1]);
		}
		else if (ope == OPERATION::ERASE)
		{
			st.minusOne(compressor[y1]);
		}
		else
		{
			res = st.getSum(compressor[y1], compressor[y2]+1);
		}
		return res;
	}
};

int main()
{
	using namespace std;
	size_t n;
	cin >> n;
	priority_queue<eventOperator, vector<eventOperator>, greater<eventOperator>> eventQueue;
	set<int> noDuplicatedY;
	int x1, y1, x2, y2;
	while(n--)
	{
		cin >> x1 >> y1 >> x2 >> y2;
		if (x1 == x2)
		{
			eventQueue.emplace(x1, OPERATION::SEARCH, x1, y1, x2, y2);
		}
		else
		{
			eventQueue.emplace(min(x1, x2), OPERATION::INSERT, x1, y1, x2, y2);
			eventQueue.emplace(max(x1, x2), OPERATION::ERASE, x1, y1, x2, y2);
		}
		noDuplicatedY.insert(y1);
		noDuplicatedY.insert(y2);
	}
	size_t compressedIndex = 0;
	for (auto y = noDuplicatedY.begin(); y!=noDuplicatedY.end();y++)
	{
		compressor.emplace(*y, compressedIndex);
		compressedIndex++;
	}
	SegTree<size_t> horizons(compressedIndex);
	size_t ans = 0;
	while (!eventQueue.empty())
	{
		eventOperator q = eventQueue.top();
		eventQueue.pop();
		ans += q.execute(horizons);
	}
	cout << ans << endl;
}
