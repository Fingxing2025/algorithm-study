#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
double w0, w;
int m;
// 判断月利率为 t 时，连续 m 个月后余额是否仍大于 0。
bool check(double t)
{
	double k = w0;
	for (int i = 0; i < m; ++i)
	{
		k = k + k * t / 100 - w;
	}
	return k > 0;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> w0 >> w >> m;
	double l = 0, r = 300;
	// 实数二分通常用“区间长度足够小”为终止条件。
	while (r - l > 1e-3)
	{
		double mid = l + (r - l) / 2;
		if (check(mid))
			r = mid;
		else
			l = mid;
	}
	cout << fixed << setprecision(1) << r;
}
