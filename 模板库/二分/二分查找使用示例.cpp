#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, c, ans = 0;
	cin >> n >> c;
	vector<ll> a(n);
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	sort(a.begin(), a.end());
	// 枚举每一种不同的 a[i]，统计满足 a[j]-a[i]=c 的配对数。
	for (int i = 0; i < n && a[i] + c <= a[n - 1];)
	{
		// lower_bound 找到第一个 >= a[i]+c 的位置；
		// 如果这个位置正好等于 a[i]+c，说明目标值存在。
		auto it = lower_bound(a.begin(), a.end(), a[i] + c);
		// upper_bound(a.begin(), a.end(), a[i]) 找到第一个 > a[i] 的位置；
		// 因此 [i, it2) 正好覆盖所有值等于 a[i] 的元素。
		auto it2 = upper_bound(a.begin(), a.end(), a[i]);
		// [it, it1) 是值为 a[i]+c 的区间，[i, it2) 是值为 a[i] 的区间。
		if (*it == a[i] + c)
		{
			auto it1 = upper_bound(a.begin(), a.end(), a[i] + c);
			// cnt1 是目标值 a[i]+c 出现次数，cnt2 是当前值 a[i] 出现次数。
			// 两类元素可以两两配对，所以新增方案数是乘积。
			ll cnt1 = it1 - it;
			ll cnt2 = it2 - a.begin() - i;
			ans += cnt1 * cnt2;
		}
		// 跳过这一整段相同的 a[i]，避免重复统计同一个值。
		i = it2 - a.begin();
	}
	cout << ans;
}
