#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
	二维 0/1 背包模板。

	每件物品同时消耗两种资源：
	1. 容量 weights[i]
	2. 时间 ts[i]

	状态定义：
	dp[j][k] 表示容量不超过 j、时间不超过 k 时的最大价值。

	本质上仍然是 0/1 背包，只是费用维度从一维变成了二维。
	因此两个费用维都必须倒序枚举。
*/

int pack2D(int W, int T, int N, const vector<int> &weights, const vector<int> &ts, const vector<int> &values)
{
	vector<vector<int>> dp(W + 1, vector<int>(T + 1, 0));
	for (int i = 0; i < N; ++i)
		// 两个费用维都倒序，避免同一件物品在同一轮转移中被重复使用。
		for (int j = W; j >= weights[i]; --j)
			for (int k = T; k >= ts[i]; --k)
				dp[j][k] = max(dp[j][k], dp[j - weights[i]][k - ts[i]] + values[i]);
	return dp[W][T];
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int w, n, t;
	cin >> n >> w >> t;
	vector<int> we(n), te(n), val(n);
	for (int i = 0; i < n; ++i)
		cin >> we[i] >> te[i] >> val[i];
	cout << pack2D(w, t, n, we, te, val);
}
