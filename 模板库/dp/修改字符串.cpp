#include <bits/stdc++.h>
using namespace std;

/*
	编辑距离模板。

	状态定义：
	dp[i][j] 表示把 s1 的前 i 个字符修改成 s2 的前 j 个字符的最小代价。

	最后一步有三种可能：
	1. 删除 s1 的最后一个字符：来自 dp[i-1][j] + 1
	2. 在 s1 末尾插入一个字符：来自 dp[i][j-1] + 1
	3. 把最后一个字符改成目标字符，或本来就相同：来自 dp[i-1][j-1] + cost

	这是非常典型的“前缀对前缀”二维 DP。
*/

int main()
{
	int n;
	cin >> n;
	for (int q = 0; q < n; ++q)
	{
		string s1, s2;
		cin >> s1 >> s2;
		int l1 = s1.size(), l2 = s2.size();

		// 初值先设成一个很大的数，表示当前状态还没被合法转移更新到。
		vector<vector<int>> dp(l1 + 1, vector<int>(l2 + 1, 0x3ffffff));

		// 把前 i 个字符变成空串，只能一直删除。
		for (int i = 0; i <= l1; ++i)
			dp[i][0] = i;

		// 把空串变成前 j 个字符，只能一直插入。
		for (int j = 0; j <= l2; ++j)
			dp[0][j] = j;

		for (int i = 1; i <= l1; ++i)
			for (int j = 1; j <= l2; ++j)
			{
				// 情况 1：删除 s1 的最后一个字符。
				if (i - 1 >= 0)
					dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);

				// 情况 2：插入一个字符，让目标串的最后一个字符被补出来。
				if (j - 1 >= 0)
					dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);

				// 情况 3：处理两串的最后一个字符。
				// 若字符相同，代价为 0；否则相当于做一次替换，代价为 1。
				if (i - 1 >= 0 && j - 1 >= 0)
					dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + int(s1[i - 1] != s2[j - 1]));
			}

		cout << dp[l1][l2] << "\n";
	}
}
