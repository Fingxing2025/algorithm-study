#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 100005;
const int MAXM = 500005;
struct Edge
{
	int to, next, w;
} edge[MAXM];
int head[MAXN], cnt = 0;
void add_edge(int u, int v, int w)
{
	// 把新边挂到 u 的邻接链表表头，后面遍历时就能顺着 next 找到所有出边。
	edge[++cnt] = {v, head[u], w};
	head[u] = cnt;
}
// Dijkstra 适用于非负边权最短路。
// dist[v] 表示起点到 v 的当前最短路估计值。
void dijkstra(int start, int n)
{
	vector<ll> dist(n + 1, INF);
	// 起点到自己距离为 0，这是所有松弛过程的出发点。
	dist[start] = 0;
	// 小根堆里存的是“当前发现的一条到某点的最短路估计值”。
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
	pq.push({0, start});
	while (!pq.empty())
	{
		ll d = pq.top().first;
		int u = pq.top().second;
		pq.pop();
		// 若取出的状态不是最新最短路，直接丢弃。
		// 因为同一个点可能被多次入堆，只有 dist[u] 对应的那次才有效。
		if (d > dist[u])
			continue;
		for (int i = head[u]; i != 0; i = edge[i].next)
		{
			int v = edge[i].to;
			int w = edge[i].w;
			// 松弛：若经过 u 再走一条边到 v 更短，就更新 dist[v]。
			if (dist[v] > dist[u] + w)
			{
				dist[v] = dist[u] + w;
				// 更新后的 dist[v] 要重新丢进堆里，让它以后也能继续扩展别人。
				pq.push({dist[v], v});
			}
		}
	}
	for (int i = 1; i <= n; ++i)
		cout << dist[i] << " ";
}
int main()
{
	int n, m, tg;
	cin >> n >> m >> tg;
	for (int i = 0; i < m; ++i)
	{
		int u, v, w;
		cin >> u >> v >> w;
		// 这份模板按有向图写；若题目是无向图，需要再补 add_edge(v, u, w)。
		add_edge(u, v, w);
	}

	dijkstra(tg, n);
}
