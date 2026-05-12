#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 100005;
vector<int> adj[MAXN];
int in_degree[MAXN];
int n, m;
// Kahn 算法：不断取出入度为 0 的点，删除它的出边。
vector<int> topo_sort()
{
	queue<int> q;
	vector<int> result;
	// 所有入度为 0 的点都可以作为拓扑序的当前起点，先全部入队。
	for (int i = 1; i <= n; ++i)
		if (in_degree[i] == 0)
			q.push(i);
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		// 一个点出队，说明它已经可以确定排在当前拓扑序的下一位。
		result.push_back(u);
		for (int v : adj[u])
		{
			// “删掉 u 的出边”在代码里的体现，就是把后继点的入度减 1。
			--in_degree[v];
			// 某个点一旦入度减到 0，说明它前面的依赖已经全部处理完，可以入队。
			if (in_degree[v] == 0)
				q.push(v);
		}
	}
	// 若最后没取满 n 个点，说明仍有一些点始终无法把入度降到 0，图里就存在环。
	if (result.size() < n)
		return {};
	return result;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 0; i < m; ++i)
	{
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		in_degree[v]++;
	}
	vector<int> res = topo_sort();
	if (res.empty())
		cout << "Cycle detected";
	else
	{
		for (int x : res)
			cout << x << " ";
		cout << "\n";
	}
}
