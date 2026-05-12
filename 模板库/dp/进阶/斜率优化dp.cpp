#include <bits/stdc++.h>
using namespace std;

/*
  斜率优化 DP 基础模板。

  模型：
  dp[i] = min_{0 <= j < i} { dp[j] + (s[i] - s[j] - L)^2 }

  其中 s[i] 为前缀和，且查询点 s[i] 单调不降。

  展开后可得：
  dp[i] = s[i]^2 + min_j { [dp[j] + (s[j] + L)^2] - 2 * s[i] * (s[j] + L) }

  因此每个 j 可以看成一条直线：
  y = m * x + b
  其中：
  m = -2 * (s[j] + L)
  b = dp[j] + (s[j] + L)^2

  当 s[i] 单调时，可以用单调队列维护凸包。
*/

using ll = long long;
using i128 = __int128_t;

struct Line
{
	ll m, b;
};

ll value(const Line &line, ll x)
{
	return line.m * x + line.b;
}

bool bad(const Line &a, const Line &b, const Line &c)
{
	return (i128)(b.b - a.b) * (b.m - c.m) >= (i128)(c.b - b.b) * (a.m - b.m);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	ll L;
	cin >> n >> L;

	vector<ll> a(n + 1), s(n + 1), dp(n + 1, 0);
	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
		s[i] = s[i - 1] + a[i];
	}

	deque<Line> q;
	auto make_line = [&](int j) -> Line
	{
		ll xj = s[j] + L;
		return {-2 * xj, dp[j] + xj * xj};
	};

	q.push_back(make_line(0));
	for (int i = 1; i <= n; ++i)
	{
		while (q.size() >= 2 && value(q[0], s[i]) >= value(q[1], s[i]))
			q.pop_front();

		dp[i] = s[i] * s[i] + value(q.front(), s[i]);

		Line cur = make_line(i);
		while (q.size() >= 2 && bad(q[q.size() - 2], q.back(), cur))
			q.pop_back();
		q.push_back(cur);
	}

	cout << dp[n] << '\n';
	return 0;
}