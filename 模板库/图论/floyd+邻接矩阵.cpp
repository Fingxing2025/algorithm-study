#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 305;
const ll INF = 0x3f3f3f3f3f3f3f3f;
ll f[MAXN][MAXN];
int main()
{
	// 初始化邻接矩阵：自己到自己距离为 0，其余设为无穷大。
	for (int i = 0; i < MAXN; ++i)
		for (int j = 0; j < MAXN; ++j)
			f[i][j] = (i == j ? 0 : INF);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; ++i)
	{
		int u, v, w;
		cin >> u >> v >> w;
		f[u][v] = min(f[u][v], (ll)w);
	}
	// Floyd 的核心顺序必须是“中转点 k 在最外层”。
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (f[i][k] != INF && f[k][j] != INF)
					f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
	int u, v;
	cin >> u >> v;
	cout << f[u][v];
}
