#include <bits/stdc++.h>
using namespace std;

/*
  轮廓线 / Broken Profile DP 基础模板：统计 n * m 空棋盘的多米诺骨牌铺法数。

  状态理解：
  按行推进，mask 表示“当前行中哪些格子已经被上一行伸下来的竖骨牌占用”。

  对于当前行，我们从左到右 DFS：
  1. 若当前位置已被占用，跳过
  2. 否则尝试横放一个骨牌
  3. 或尝试竖放一个骨牌，把占用信息留给下一行的 next_mask

  这类模板的重点不在题目本身，而在“用一条轮廓线状态描述行与行之间的衔接”。
*/

int n, m;
vector<long long> dp, next_dp;

void dfs_fill_row(int col, int cur_mask, int next_mask, long long ways)
{
	if (col == m)
	{
		next_dp[next_mask] += ways;
		return;
	}

	if (cur_mask & (1 << col))
	{
		dfs_fill_row(col + 1, cur_mask, next_mask, ways);
		return;
	}

	// 横放：占用当前格和右边一格。
	if (col + 1 < m && !(cur_mask & (1 << (col + 1))))
		dfs_fill_row(col + 2, cur_mask, next_mask, ways);

	// 竖放：当前格占到下一行，因此记录到 next_mask。
	dfs_fill_row(col + 1, cur_mask, next_mask | (1 << col), ways);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> m;
	if (n < m)
		swap(n, m);

	int states = 1 << m;
	dp.assign(states, 0);
	dp[0] = 1;

	for (int row = 0; row < n; ++row)
	{
		next_dp.assign(states, 0);
		for (int mask = 0; mask < states; ++mask)
		{
			if (dp[mask] == 0)
				continue;
			dfs_fill_row(0, mask, 0, dp[mask]);
		}
		dp.swap(next_dp);
	}

	cout << dp[0] << '\n';
	return 0;
}