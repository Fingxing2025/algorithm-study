#include <bits/stdc++.h>
using namespace std;

/*
  概率 / 期望 DP 基础模板：DAG 上的期望路径长度。

  模型：
  从点 1 出发，每次在当前点的所有出边中等概率随机选一条走。
  给定一张 DAG，边带权，求从 1 走到终点的期望路径长度。

  状态定义：
  E[u] 表示从 u 出发到达终止状态的期望代价。

  转移：
  若 u 有 outdeg[u] 条出边，则
  E[u] = sum(E[v] + w(u,v)) / outdeg[u]

  因为是 DAG，所以可以先拓扑排序，再逆拓扑序递推期望。
*/

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<vector<pair<int, int>>> g(n + 1);
	vector<int> indeg(n + 1, 0), outdeg(n + 1, 0);

	for (int i = 0; i < m; ++i)
	{
		int u, v, w;
		cin >> u >> v >> w;
		g[u].push_back({v, w});
		++indeg[v];
		++outdeg[u];
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

	vector<double> expect(n + 1, 0.0);
	for (int idx = (int)topo.size() - 1; idx >= 0; --idx)
	{
		int u = topo[idx];
		if (outdeg[u] == 0)
			continue;
		double sum = 0.0;
		for (auto [v, w] : g[u])
			sum += expect[v] + w;
		expect[u] = sum / outdeg[u];
	}

	cout << fixed << setprecision(10) << expect[1] << '\n';
	return 0;
}