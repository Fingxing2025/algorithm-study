#include <bits/stdc++.h>
using namespace std;

/*
  树形 DP 基础模板：点权树上最大独立集。

  模型：
  每个点有点权，选一个点后，它的相邻点都不能选。
  求能选出的最大总权值。

  状态定义：
  dp[u][0] 表示 u 不选时，u 子树内的最大权值和。
  dp[u][1] 表示 u 选时，u 子树内的最大权值和。

  转移：
  1. 若不选 u，则每个儿子可选可不选：
	 dp[u][0] += max(dp[v][0], dp[v][1])
  2. 若选 u，则儿子都不能选：
	 dp[u][1] += dp[v][0]
*/

const int N = 100005;

int n;
int w[N];
vector<int> g[N];
long long dp[N][2];

void dfs(int u, int parent)
{
	dp[u][0] = 0;
	dp[u][1] = w[u];

	for (int v : g[u])
	{
		if (v == parent)
			continue;
		dfs(v, u);
		dp[u][0] += max(dp[v][0], dp[v][1]);
		dp[u][1] += dp[v][0];
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> w[i];

	for (int i = 1; i < n; ++i)
	{
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	dfs(1, 0);
	cout << max(dp[1][0], dp[1][1]) << '\n';
	return 0;
}