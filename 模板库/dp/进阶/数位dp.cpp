#include <bits/stdc++.h>
using namespace std;

/*
  数位 DP 基础模板：统计 [0, n] 中不含数字 4 且不含连续子串 62 的数有多少个。

  这个模板的重点不在题意，而在骨架：
  1. 把数字拆成数位数组
  2. 写 dfs(pos, prev, tight, started)
  3. tight 为假时记忆化

  started 表示前面是否已经放过非前导零数字。
  若还没开始，就不应把前导零错误地计入限制状态。
*/

long long memo[20][10][2];
bool vis[20][10][2];
vector<int> digits;

long long dfs(int pos, int prev_digit, bool tight, bool started)
{
	// 所有数位都处理完后，说明当前构造是一种合法方案。
	if (pos == -1)
		return 1;

	// 只有在“不受上界限制”时，这个状态未来的转移才完全固定，可以安全记忆化。
	if (!tight && vis[pos][prev_digit][started])
		return memo[pos][prev_digit][started];

	// tight=true 时，这一位最多填到原数字对应位；否则可以自由填 0..9。
	int up = tight ? digits[pos] : 9;
	long long ans = 0;

	for (int d = 0; d <= up; ++d)
	{
		// 一旦填入非 0，就说明后续已经正式进入数字本体，不再是前导零阶段。
		bool next_started = started || (d != 0);

		if (next_started)
		{
			// 限制 1：数字里不能出现 4。
			if (d == 4)
				continue;
			// 限制 2：已经开始构造后，不能让“上一位是 6、当前位是 2”连在一起。
			if (started && prev_digit == 6 && d == 2)
				continue;
		}

		// 若还没开始，prev_digit 没有真实含义，统一置 0 占位即可；
		// 若已经开始，就把当前位 d 作为下一层的“上一位”。
		int next_prev = next_started ? d : 0;
		// tight 只有在“当前位也贴着上界去填”时才会继续保持为真。
		ans += dfs(pos - 1, next_prev, tight && (d == up), next_started);
	}

	if (!tight)
	{
		// 记下这个自由状态，下次再遇到同样的 pos/prev/started 组合就能直接复用。
		vis[pos][prev_digit][started] = true;
		memo[pos][prev_digit][started] = ans;
	}
	return ans;
}

long long solve(long long n)
{
	if (n < 0)
		return 0;
	digits.clear();
	// 把数字拆成低位在前的形式，方便 dfs 按 pos 从高位往低位处理。
	while (n > 0)
	{
		digits.push_back(n % 10);
		n /= 10;
	}
	// n=0 时 while 不会进，需要手动补一个 0 位，保证 dfs 至少处理一位。
	if (digits.empty())
		digits.push_back(0);
	return dfs((int)digits.size() - 1, 0, true, false);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	long long l, r;
	cin >> l >> r;
	memset(vis, 0, sizeof(vis));
	cout << solve(r) - solve(l - 1) << '\n';
	return 0;
}