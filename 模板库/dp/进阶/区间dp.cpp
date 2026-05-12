#include <bits/stdc++.h>
using namespace std;

/*
  区间 DP 基础模板：石子合并。

  模型：
  每次合并一段连续区间的两部分，代价为这一整段石子的总和。
  求把整个区间合并成一堆的最小代价。

  状态定义：
  dp[l][r] 表示把区间 [l, r] 合并成一堆的最小代价。

  转移：
  枚举最后一次合并的位置 k：
  dp[l][r] = min(dp[l][k] + dp[k+1][r] + sum(l, r))

  循环顺序：
  必须按区间长度从小到大递推。
*/

const int N = 305;
const long long INF = (1LL << 60);

int n;
long long a[N], prefix[N], dp[N][N];

long long range_sum(int l, int r)
{
	return prefix[r] - prefix[l - 1];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
		prefix[i] = prefix[i - 1] + a[i];
	}

	for (int len = 2; len <= n; ++len)
	{
		for (int l = 1; l + len - 1 <= n; ++l)
		{
			int r = l + len - 1;
			dp[l][r] = INF;
			for (int k = l; k < r; ++k)
			{
				dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + range_sum(l, r));
			}
		}
	}

	cout << dp[1][n] << '\n';
	return 0;
}