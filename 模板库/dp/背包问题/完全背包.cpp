#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
  完全背包模板。

  与 0/1 背包的唯一区别在于：
  每件物品可以选无限次。

  因此转移时需要正序枚举容量，
  让当前物品在同一轮中可以继续基于“已经选过当前物品”的状态再选一次。
*/

int compack(int W, int N, const vector<int> &weights, const vector<int> &values)
{
	vector<int> dp(W + 1, 0);
	for (int i = 0; i < N; ++i)
		// 正序枚举容量，使当前物品可以被重复选取。
		for (int j = weights[i]; j <= W; ++j)
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
	cout << compack(w, n, wt, val);
}
