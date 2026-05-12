#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int fa[N];
int sz[N];
// 初始化：每个点单独成一个集合，集合大小为 1。
void init(int n)
{
	for (int i = 1; i <= n; ++i)
	{
		fa[i] = i;
		sz[i] = 1;
	}
}

int find(int x)
{
	// 若 x 不是根，就递归找到根，并把路径上所有点直接挂到根上。
	// 这就是路径压缩：后续再查这些点时会快很多。
	return fa[x] == x ? x : (fa[x] = find(fa[x]));
}

// 按大小合并：总是把小集合挂到大集合上。
void unite(int x, int y)
{
	// 合并前先各自找到所在集合的根，真正参与合并的是“集合”，不是原始点编号。
	int rx = find(x);
	int ry = find(y);
	if (rx != ry)
	{
		// 按大小合并：把小集合挂到大集合上，避免树退化得太深。
		if (sz[rx] < sz[ry])
			swap(rx, ry);
		fa[ry] = rx;
		// 新根对应集合的大小，要把被并进来的那一整棵树也算进去。
		sz[rx] += sz[ry];
	}
}

int main()
{
	int n, m;
	cin >> n >> m;
	init(n);
	while (m--)
	{
		int op, x, y;
		cin >> op >> x >> y;
		// op==1 表示合并两个集合；
		// 否则就询问它们当前是否已经在同一个连通块里。
		if (op == 1)
			unite(x, y);
		else
		{
			if (find(x) == find(y))
				cout << "Y" << "\n";
			else
				cout << "N" << "\n";
		}
	}
}
