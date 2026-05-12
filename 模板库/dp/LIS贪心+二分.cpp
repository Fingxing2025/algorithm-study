#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
	LIS 贪心 + 二分优化模板。

	核心维护量：
	t[len - 1] 表示“长度为 len 的上升子序列的最小可能结尾值”。

	为什么维护最小结尾：
	对同样长度的上升子序列来说，结尾越小，后面越容易接新元素。

	更新方式：
	1. 若当前值比所有结尾都大，则可以新开一个更长的 LIS。
	2. 否则用它去替换第一个 >= 它的位置，保持同长度下结尾尽量小。

	注意：
	这个写法一般只能直接求 LIS 长度；若要求具体方案，需要额外记录前驱。
*/

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> a(n), b(n + 1);
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	for (int i = 0; i < n; ++i)
	{
		int x;
		cin >> x;
		b[x] = i + 1;
	}
	for (int i = 0; i < n; ++i)
		a[i] = b[a[i]];
	vector<int> t;
	for (int i = 0; i < n; ++i)
	{
		// 找到第一个 >= a[i] 的位置。
		// 若存在，就用 a[i] 更新该长度的最优结尾；否则扩展 LIS 长度。
		auto it = lower_bound(t.begin(), t.end(), a[i]);
		if (it == t.end())
			t.push_back(a[i]);
		else
			*it = a[i];
	}
	cout << t.size();
}
