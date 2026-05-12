#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
	多重背包模板。

	模型：每种物品有固定件数 num，不能无限拿。

	朴素做法要枚举“当前物品拿几件”，复杂度较高。
	这里使用二进制拆分：
	num = 1 + 2 + 4 + ... + 剩余量

	拆分后，每一块都看成一件新的 0/1 物品，
	总物品数从 O(num) 降到 O(log num)。
*/

void multipack()
{
	int N, W;
	cin >> N >> W;
	vector<int> dp(W + 1, 0);
	for (int i = 0; i < N; ++i)
	{
		int v, w, num;
		cin >> v >> w >> num;

		// 用二进制块依次拆分件数。
		for (int k = 1; num > 0; k <<= 1)
		{
			int take = min(k, num);
			int now_v = take * v;
			int now_w = take * w;

			// 拆完后的每一块都只允许选一次，因此仍然按 0/1 背包倒序更新。
			for (int j = W; j >= now_w; --j)
				dp[j] = max(dp[j], dp[j - now_w] + now_v);
			num -= take;
		}
	}
	cout << dp[W];
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	multipack();
}
