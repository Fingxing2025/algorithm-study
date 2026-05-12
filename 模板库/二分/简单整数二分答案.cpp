#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll m;
ll a[1000005];
int n;
// 检查把所有树木裁到高度 h 后，能否至少得到 m 的木材。
bool check(int h)
{
	ll ans = 0;
	for (int i = 0; i < n; ++i)
	{
		if (a[i] > h)
			ans += a[i] - h;
	}
	return ans >= m;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	ll l = 0, r = 0, ans = -1;
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i];
		r = max(r, a[i] + 1);
	}
	// 二分“最大可行值”：如果 mid 可行，就继续向右找更高的锯子高度。
	while (l <= r)
	{
		ll mid = l + (r - l) / 2;
		if (check(mid))
		{
			ans = mid;
			l = mid + 1;
		}
		else
			r = mid - 1;
	}
	cout << ans;
}
