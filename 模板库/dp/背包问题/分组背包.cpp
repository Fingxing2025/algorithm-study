#include <bits/stdc++.h>
using namespace std;

/*
	分组背包模板。

	模型：
	每件物品属于某一组，每组最多选一件。

	转移顺序必须是：
	先枚举组，再倒序枚举容量，最后枚举组内选哪件。

	这样才能保证：
	当前组的决策只基于“前面各组已经处理完”的结果，
	不会在同一组里错误地选出多件物品。
*/

int main()
{
	int n, m, w, v, g, g_max = -1;
	int dt[105][105][2] = {0}, l[105] = {0};
	int dp[1005] = {0};
	cin >> m >> n;
	// dt[g][k] 保存第 g 组第 k 件物品的体积和价值。
	for (int i = 1; i <= n; i++)
	{
		cin >> w >> v >> g;
		dt[g][l[g]][0] = w;
		dt[g][l[g]++][1] = v;
		g_max = g > g_max ? g : g_max;
	}
	for (int i = 1; i <= g_max; i++)
		for (int j = m; j >= 0; j--)
			// 每组最多选一件，所以容量仍要倒序，避免同组内多次使用更新后的状态。
			for (int k = 0; k < l[i]; k++)
				if (j >= dt[i][k][0])
					dp[j] = max(dp[j], dp[j - dt[i][k][0]] + dt[i][k][1]);
	cout << dp[m] << endl;
	return 0;
}
