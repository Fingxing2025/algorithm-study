#include <bits/stdc++.h>
using namespace std;
const int N = 5005;

/*
  最长上升子序列（LIS）朴素模板。

  状态定义：
  dp[i] 表示“以 a[i] 结尾”的最长上升子序列长度。

  为什么这样定义：
  因为 LIS 的最后一个数一旦固定为 a[i]，它前面能接谁就只和 j < i 且 a[j] < a[i] 有关。

  转移：
  dp[i] = max(dp[j] + 1), 其中 0 <= j < i 且 a[j] < a[i]

  复杂度：
  O(n^2)，适合作为 LIS 的入门写法和状态设计范例。
*/

int lis(int n, vector<int> &a)
{
	vector<int> dp(n, 1);
	int ans = 0;
	for (int i = 0; i < n; ++i)
	{
		// 枚举 i 前面的所有位置 j，尝试把 a[i] 接到对应 LIS 后面。
		for (int j = 0; j < i; ++j)
			if (a[i] > a[j])
				dp[i] = max(dp[i], dp[j] + 1);

		// 注意答案不是 dp[n-1]，而是所有“以 i 结尾”的情况里的最大值。
		ans = max(ans, dp[i]);
	}
	return ans;
}

int main()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	cout << lis(n, a);
}
