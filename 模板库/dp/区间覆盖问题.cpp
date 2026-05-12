#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll Mod = 998244353;

/*
	区间覆盖型 DP。

	题目模型可以概括成：
	给若干带权区间，求覆盖前缀中恰好若干个点的最小代价。

	状态定义：
	dp[i][j] 表示前 i 个位置里，恰好覆盖了 j 个点时的最小代价。

	常见转移思路：
	1. 不让位置 i 被最后一段覆盖，直接继承前一个前缀。
	2. 枚举“最后一段连续覆盖了多少个点”，把问题缩到更短前缀。

	这是非常典型的“最后一步 / 最后一段”模型。
*/

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	for (int q = 0; q < T; ++q)
	{
		int n, m, k;
		cin >> n >> m >> k;

		// w[l][r] 预处理成“用一条区间刚好负责覆盖 [l, r] 这一段时的最小代价”。
		vector<vector<ll>> w(n + 1, vector<ll>(n + 1, LLONG_MAX));

		vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, LLONG_MAX));
		for (int i = 0; i < m; ++i)
		{
			int l, r;
			ll cst;
			cin >> l >> r >> cst;
			for (int j = l; j <= r; ++j)
				w[j][r] = min(w[j][r], cst);
		}
		for (int i = 0; i <= n; ++i)
			dp[i][0] = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= i; ++j)
			{
				// 情况 1：位置 i 不被最后一段覆盖。
				dp[i][j] = dp[i - 1][j];

				// 情况 2：最后一段连续覆盖了 t 个点，即 [i-t+1, i]。
				for (int t = 1; t <= j; ++t)
					if (w[i - t + 1][i] != LLONG_MAX && dp[i - t][j - t] != LLONG_MAX)
						dp[i][j] = min(dp[i][j], dp[i - t][j - t] + w[i - t + 1][i]);
			}
		ll ans = dp[n][k];
		cout << "case #" << q << ":\n";
		if (ans == LLONG_MAX)
			cout << "-1\n";
		else
			cout << ans << "\n";
	}
}
