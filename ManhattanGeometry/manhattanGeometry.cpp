#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <queue>

std::set<int> s;

enum class OPERATION
{
	INSERT = 0,
	SEARCH = 1,
	ERASE = 2
};

struct eventQueue
{
	int order;
	OPERATION ope;
	int x1, y1, x2, y2;
	eventQueue(int _order, OPERATION _ope, int _x1, int _y1, int _x2, int _y2):
		order(_order), ope(_ope), x1(_x1), y1(_y1), x2(_x2), y2(_y2){}
	bool operator < (eventQueue rhs)
	{
		if (order!=rhs.order)
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
		std::size_t res=0;
		if (ope==OPERATION::INSERT)
		{
			s.insert(y1);
		}
		else if (ope==OPERATION::ERASE)
		{
			s.erase(y1);
		}
		else
		{
			res = std::distance(s.lower_bound(y1), s.upper_bound(y2));
		}
		return res;
	}
};

int main()
{
	using namespace std;
	auto c = [](eventQueue l, eventQueue r) {return l>r; };
	size_t n;
	cin >> n;
	priority_queue<eventQueue, vector<eventQueue>, decltype(c)> pq(c);
	int x1, y1, x2, y2;
	for (size_t i = 0; i < n; i++)
	{
		cin >> x1 >> y1 >> x2 >> y2;
		if (x1==x2)
		{
			pq.emplace(x1, OPERATION::SEARCH, x1, min(y1,y2), x2, max(y1,y2));
		}
		else
		{
			pq.emplace(min(x1,x2), OPERATION::INSERT, min(x1,x2), y1, max(x1,x2), y2);
			pq.emplace(max(x1,x2), OPERATION::ERASE, min(x1,x2), y1, max(x1,x2), y2);
		}
	}
	size_t ans = 0;
	while (!pq.empty())
	{
		eventQueue q = pq.top();
		pq.pop();
		ans += q.execute();
	}
	cout << ans << endl;

}