#include <iostream>
#include <queue>
#include <vector>

#define rep(i,n) for (int i=0;i<(n);i++)
#define cost first
#define vertex second

using namespace std;
using ll = long long;
using P = pair<ll, ll>;

const ll INF = 1LL << 60;

vector<ll> dis;
vector<vector<P>> G;

void dijkstra(size_t start)
{
	priority_queue<P, vector<P>, greater<P>> pq;
	P init(0, start);
	dis[start] = 0;
	pq.push(init);
	while (!pq.empty())
	{
		P seeking = pq.top();
		pq.pop();
		if (seeking.cost > dis[seeking.vertex]) continue;
		for (P next : G[seeking.vertex])
		{
			if (dis[next.vertex] > dis[seeking.vertex] + next.cost)
			{
				dis[next.vertex] = dis[seeking.vertex] + next.cost;
				pq.emplace(dis[next.vertex], next.vertex);
			}
		}
	}
}


int main()
{
	size_t v, e, s;
	cin >> v >> e >> s;
	G.resize(v);
	dis.resize(v, INF);
	rep(i, e)
	{
		ll v;
		P p;
		cin >> v >> p.vertex >> p.cost;
		G[v].push_back(p);
	}
	dijkstra(s);
	rep(i, v)
	{
		if (dis[i] == INF)
		{
			cout << "INF" << endl;
			continue;
		}
		cout << dis[i] << endl;
	}
}