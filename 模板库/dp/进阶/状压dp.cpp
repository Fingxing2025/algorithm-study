#include <bits/stdc++.h>
using namespace std;

/*
  状压 DP 基础模板：TSP 型最短 Hamilton 路。

  模型：
  给定 n 个点和两两距离，求从 0 号点出发，访问所有点一次的最短路径长度。

  状态定义：
  dp[mask][i] 表示已经访问的点集为 mask，且当前停在 i 时的最短路。

  转移：
  枚举下一个未访问点 j：
  dp[mask | (1 << j)][j] = min(dp[mask | (1 << j)][j], dp[mask][i] + dist[i][j])
*/

const long long INF = (1LL << 60);

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	vector<vector<long long>> dist(n, vector<long long>(n));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> dist[i][j];

	int full = 1 << n;
	vector<vector<long long>> dp(full, vector<long long>(n, INF));
	dp[1][0] = 0;

	for (int mask = 1; mask < full; ++mask)
	{
		for (int i = 0; i < n; ++i)
		{
			if (!(mask & (1 << i)) || dp[mask][i] == INF)
				continue;
			for (int j = 0; j < n; ++j)
			{
				if (mask & (1 << j))
					continue;
				int next_mask = mask | (1 << j);
				dp[next_mask][j] = min(dp[next_mask][j], dp[mask][i] + dist[i][j]);
			}
		}
	}

	long long ans = INF;
	for (int i = 0; i < n; ++i)
		ans = min(ans, dp[full - 1][i]);
	cout << ans << '\n';
	return 0;
}