#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 5;
const int LOG = 20;
vector<int> adj[N];
int depth[N];
int fa[N][LOG + 1];
// 预处理每个点的深度和 2^i 级祖先。
void dfs(int u, int p)
{
	// 深度比父亲多 1；这里把 0 号点当成“虚父亲”，方便根的深度初始化。
	depth[u] = depth[p] + 1;
	// fa[u][0] 就是 u 的直接父亲。
	fa[u][0] = p;
	for (int i = 1; i <= LOG; ++i)
		// 倍增递推：u 的 2^i 级祖先 = “u 的 2^(i-1) 级祖先”的 2^(i-1) 级祖先。
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (int v : adj[u])
		if (v != p)
			// 只往儿子递归，避免沿无向边又走回父亲。
			dfs(v, u);
}
// 先把更深的点跳到同一深度，再一起向上跳。
int get_lca(int x, int y)
{
	if (depth[x] < depth[y])
		swap(x, y);
	// 第一步：把较深的 x 提到和 y 同一层。
	// 从大步长往小步长跳，能保证总复杂度是 O(log n)。
	for (int i = LOG; i >= 0; --i)
		if (depth[fa[x][i]] >= depth[y])
			x = fa[x][i];
	// 若此时已经重合，说明较浅的那个点本身就是 LCA。
	if (x == y)
		return x;
	// 第二步：让 x 和 y 同时尽量往上跳，
	// 但必须保证“跳完之后它们还没相遇”，这样才能把 LCA 卡在它们正上方那一层。
	for (int i = LOG; i >= 0; --i)
		if (fa[x][i] != fa[y][i])
		{
			x = fa[x][i];
			y = fa[y][i];
		}
	// 循环结束后，x 和 y 已经分别处在 LCA 的两个儿子位置，因此它们的父亲就是答案。
	return fa[x][0];
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m, root;
	cin >> n >> m >> root;
	for (int i = 1; i < n; ++i)
	{
		int u, v;
		cin >> u >> v;
		// 树是无向图，所以两边都要加。
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	depth[0] = 0;
	dfs(root, 0);
	for (int i = 0; i < m; ++i)
	{
		int u, v;
		cin >> u >> v;
		cout << get_lca(u, v) << "\n";
	}
}
