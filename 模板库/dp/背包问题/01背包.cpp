#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
	0/1 背包模板。

	状态定义：
	dp[j] 表示容量不超过 j 时，能够获得的最大价值。

	转移：
	对于每件物品 i，尝试把它放入容量 j：
	dp[j] = max(dp[j], dp[j - weight[i]] + value[i])

	为什么容量倒序：
	因为每件物品最多只能选一次。
	倒序能保证本轮更新 dp[j] 时，dp[j - weight[i]] 仍然是“上一轮”的值。
*/

int pack01(int W, int N, const vector<int> &weights, const vector<int> &values)
{
	vector<int> dp(W + 1, 0);
	for (int i = 0; i < N; ++i)
		// 倒序枚举容量，避免同一件物品被重复使用。
		for (int j = W; j >= weights[i]; --j)
			dp[j] = max(dp[j], dp[j - weights[i]] + values[i]);
	return dp[W];
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int w, n;
	cin >> n >> w;
	vector<int> wt(n), val(n);
	for (int i = 0; i < n; ++i)
		cin >> wt[i] >> val[i];
	cout << pack01(w, n, wt, val);
}
