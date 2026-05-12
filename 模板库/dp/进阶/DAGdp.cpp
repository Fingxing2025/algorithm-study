#include <bits/stdc++.h>
using namespace std;

/*
  DAG DP 基础模板：有向无环图上的最长路。

  模型：
  给定 DAG 和起点 s，求从 s 到每个点的最长路。

  做法：
  先拓扑排序，再按拓扑序做 DP。

  状态定义：
  dp[u] 表示从 s 到 u 的最长路长度。

  注意：
  不可达状态不能初始化为 0，否则会污染答案，
  应初始化为负无穷。
*/

const long long NEG_INF = -(1LL << 60);

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, s;
	cin >> n >> m >> s;

	vector<vector<pair<int, int>>> g(n + 1);
	vector<int> indeg(n + 1, 0);

	for (int i = 0; i < m; ++i)
	{
		int u, v, w;
		cin >> u >> v >> w;
		g[u].push_back({v, w});
		++indeg[v];
	}

	queue<int> q;
	for (int i = 1; i <= n; ++i)
		if (indeg[i] == 0)
			q.push(i);

	vector<int> topo;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		topo.push_back(u);
		for (auto [v, w] : g[u])
		{
			if (--indeg[v] == 0)
				q.push(v);
		}
	}

	vector<long long> dp(n + 1, NEG_INF);
	dp[s] = 0;

	for (int u : topo)
	{
		if (dp[u] == NEG_INF)
			continue;
		for (auto [v, w] : g[u])
		{
			dp[v] = max(dp[v], dp[u] + w);
		}
	}

	for (int i = 1; i <= n; ++i)
	{
		if (dp[i] == NEG_INF)
			cout << -1;
		else
			cout << dp[i];
		cout << (i == n ? '\n' : ' ');
	}
	return 0;
}