#include <bits/stdc++.h>
using namespace std;
class Item
{
public:
	int w, v, r;
};

/*
	主件 - 附件型依赖背包。

	约束：
	附件不能单独购买，必须和自己的主件一起买。

	处理套路：
	先按主件把所有“合法购买组合”列出来，
	然后把每个主件对应的若干种合法方案，当作一次分组背包转移。

	这个模板假设每个主件最多带两个附件，
	因此每个主件只需要枚举 4 种合法选择：
	1. 只买主件
	2. 主件 + 附件 1
	3. 主件 + 附件 2
	4. 主件 + 两个附件都买
*/

int main()
{
	int m, n;
	cin >> n >> m;
	vector<Item> item(m + 1);
	vector<int> mit;
	vector<int> dp(n + 1, 0);
	for (int i = 1; i <= m; i++)
	{
		cin >> item[i].w >> item[i].v >> item[i].r;
		// 这里把“价格 * 重要度”直接折算成收益。
		item[i].v *= item[i].w;
		if (item[i].r == 0)
			mit.emplace_back(i);
	}

	// 对每个主件，把所有合法搭配都展开后做 0/1 背包。
	for (int i = 0; i < mit.size(); i++)
	{
		int w0 = item[mit[i]].w, v0 = item[mit[i]].v;
		int v1, w1, v2, w2;
		v1 = v2 = w1 = w2 = 0;
		for (int j = 1; j <= m; j++)
			if (item[j].r == mit[i])
				if (v1 == 0 && w1 == 0)
				{
					v1 = item[j].v;
					w1 = item[j].w;
				}
				else
				{
					v2 = item[j].v;
					w2 = item[j].w;
				}
		for (int j = n; j >= w0; j--)
		{
			// 方案 1：只买主件。
			if (j >= w0)
				dp[j] = max(dp[j], dp[j - w0] + v0);

			// 方案 2：主件 + 附件 1。
			if (j >= w0 + w1)
				dp[j] = max(dp[j], dp[j - w0 - w1] + v0 + v1);

			// 方案 3：主件 + 附件 2。
			if (j >= w0 + w2)
				dp[j] = max(dp[j], dp[j - w0 - w2] + v0 + v2);

			// 方案 4：主件 + 两个附件全买。
			if (j >= w0 + w1 + w2)
				dp[j] = max(dp[j], dp[j - w0 - w1 - w2] + v0 + v1 + v2);
		}
	}
	cout << dp[n];
	return 0;
}
