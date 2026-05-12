#include <bits/stdc++.h>
using namespace std;

/*
  换根 DP 基础模板：求每个点作为根时，到所有点的距离和。

  第一遍 DFS：
  sz[u]   = u 子树大小
  down[u] = 以 1 为根时，u 子树内所有点到 u 的距离和

  第二遍 DFS：
  ans[u] 表示以 u 为根时，到全树所有点的距离和。

  当根从 u 换到儿子 v 时：
  ans[v] = ans[u] + (n - 2 * sz[v])

  理解：
  1. v 子树里的 sz[v] 个点离新根更近 1
  2. 其余 n - sz[v] 个点离新根更远 1
*/

const int N = 200005;

int n;
vector<int> g[N];
int sz[N];
long long down_sum[N], ans[N];

void dfs1(int u, int parent)
{
	sz[u] = 1;
	down_sum[u] = 0;
	for (int v : g[u])
	{
		if (v == parent)
			continue;
		dfs1(v, u);
		sz[u] += sz[v];
		down_sum[u] += down_sum[v] + sz[v];
	}
}

void dfs2(int u, int parent)
{
	for (int v : g[u])
	{
		if (v == parent)
			continue;
		ans[v] = ans[u] + (n - 2LL * sz[v]);
		dfs2(v, u);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n;
	for (int i = 1; i < n; ++i)
	{
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	dfs1(1, 0);
	ans[1] = down_sum[1];
	dfs2(1, 0);

	for (int i = 1; i <= n; ++i)
		cout << ans[i] << (i == n ? '\n' : ' ');
	return 0;
}