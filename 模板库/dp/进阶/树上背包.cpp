#include <bits/stdc++.h>
using namespace std;

/*
  树上背包基础模板：有依赖关系的选点。

  模型：
  每个点有一个收益，若要选一个点，必须先选它的父亲。
  求恰好选 m 个真实点时的最大收益。

  这是 P2014 选课 的标准骨架：
  1. 建一个虚根 0
  2. 所有没有父亲的点都连到 0
  3. dp[u][k] 表示在 u 的子树里，选 k 个点且必须选 u 时的最大收益

  由于虚根 0 不算真实点，最后答案取 dp[0][m+1]。
*/

const int N = 305;
const int NEG_INF = -1e9;

int n, m;
int val[N];
int sz[N];
vector<int> g[N];
int dp[N][N];

void dfs(int u)
{
	sz[u] = 1;
	for (int i = 0; i <= m + 1; ++i)
		dp[u][i] = NEG_INF;
	dp[u][1] = val[u];

	for (int v : g[u])
	{
		dfs(v);
		for (int i = min(sz[u], m + 1); i >= 1; --i)
		{
			for (int j = 1; j <= min(sz[v], m + 1 - i); ++j)
			{
				dp[u][i + j] = max(dp[u][i + j], dp[u][i] + dp[v][j]);
			}
		}
		sz[u] += sz[v];
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
	{
		int parent;
		cin >> parent >> val[i];
		g[parent].push_back(i);
	}

	val[0] = 0;
	dfs(0);
	cout << dp[0][m + 1] << '\n';
	return 0;
}