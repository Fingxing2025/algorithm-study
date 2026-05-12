#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Edge
{
	int u, v, w;
};
int fa[100005];
int find(int x)
{
	return fa[x] == x ? x : (fa[x] = find(fa[x]));
}
// Kruskal：按边权从小到大选边，若两端点不连通就加入生成树。
ll kruskal(int n, vector<Edge> &edges)
{
	for (int i = 1; i <= n; ++i)
		fa[i] = i;
	sort(edges.begin(), edges.end(), [](const Edge &x, const Edge &y)
		 { return x.w < y.w; });
	ll mw = 0;
	int cnt = 0;
	for (const auto &e : edges)
	{
		int rtu = find(e.u);
		int rtv = find(e.v);
		if (rtu != rtv)
		{
			fa[rtu] = rtv;
			mw += e.w;
			++cnt;
			if (cnt == n - 1)
				break;
		}
	}

	return (cnt == n - 1) ? mw : -1;
}
int main()
{
	int n, m;
	vector<Edge> edges;
	cin >> n >> m;
	for (int i = 0; i < m; ++i)
	{
		int u, v, w;
		cin >> u >> v >> w;
		edges.push_back({u, v, w});
	}
	cout << kruskal(n, edges);
}
