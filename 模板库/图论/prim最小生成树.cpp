#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 5005;
ll g[MAXN][MAXN];
ll dis[MAXN];
bool vis[MAXN];
// Prim：每次把“距离当前生成树最近”的点加入答案。
ll prim(int n)
{
	fill(dis, dis + n + 1, INF);
	dis[1] = 0;
	ll res = 0;
	for (int i = 0; i < n; ++i)
	{
		int u = -1;
		for (int j = 1; j <= n; ++j)
			if (!vis[j] && (u == -1 || dis[j] < dis[u]))
				u = j;
		if (dis[u] == INF)
			return -1;
		vis[u] = true;
		res += dis[u];
		for (int j = 1; j <= n; ++j)
			if (!vis[j] && g[u][j] < dis[j])
				dis[j] = g[u][j];
	}
	return res;
}
int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			g[i][j] = INF;
	for (int i = 0; i < m; ++i)
	{
		int u, v, w;
		cin >> u >> v >> w;
		// 最小生成树处理的是无向图，重边时保留较小边权。
		g[u][v] = min(g[u][v], (ll)w);
		g[v][u] = min(g[v][u], (ll)w);
	}
	cout << prim(n);
}
