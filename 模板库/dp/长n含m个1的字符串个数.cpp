#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
	计数 DP：统计长度为 n 的二进制串中，至少出现一次连续 m 个 1 的方案数。

	常用思路：正面直接统计“至少出现一次”较难，改成补集更自然：
	1. 先统计“不含连续 m 个 1”的方案数。
	2. 再用总串数 2^n 减掉它。

	状态定义：
	dp[i][j] 表示长度为 i，且末尾连续 1 的个数恰好为 j 的合法串数。

	这里只依赖上一层，因此可以使用滚动数组压空间。
*/

int main()
{
	int n, m;
	while (true)
	{
		cin >> n >> m;
		if (n == -1 && m == -1)
			break;

		// 这里只开两层：当前层和上一层。
		vector<vector<ll>> dp(2, vector<ll>(m, 0));
		dp[1][1] = dp[1][0] = 1;
		for (int i = 2; i <= n; ++i)
		{
			// 末尾补 0：之前任何合法状态都能转来，且连续 1 长度清零。
			dp[i % 2][0] = 0;
			for (int j = 0; j < m; ++j)
				dp[i % 2][0] += dp[(i - 1) % 2][j];

			// 末尾补 1：只能从“连续 1 长度少 1”的状态转移过来。
			for (int j = 1; j < m; ++j)
			{
				dp[i % 2][j] = dp[(i - 1) % 2][j - 1];
			}
		}

		// 最后用总方案数减去补集。
		ll ans = (ll)1 << n;
		for (int j = 0; j < m; ++j)
			ans -= dp[n % 2][j];
		cout << ans << "\n";
	}
}
