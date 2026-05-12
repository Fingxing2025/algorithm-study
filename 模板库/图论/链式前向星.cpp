#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const int M = 1e5 + 5;
struct Edge
{
	int to, next, w;
} edge[M];
int head[N], cnt;
// 加边后，新边会挂到 head[u] 指向的链表最前面。
void add_edge(int u, int v, int w)
{
	edge[++cnt].to = v;
	edge[cnt].w = w;
	edge[cnt].next = head[u];
	head[u] = cnt;
}
int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; ++i)
	{
		int u, v, w;
		cin >> u >> v >> w;
		add_edge(u, v, w);
	}
	int u0;
	cin >> u0;
	// 沿着 u0 的邻接链表向后遍历即可访问所有出边。
	for (int i = head[u0]; i != 0; i = edge[i].next)
	{
		int v = edge[i].to;
		int w = edge[i].w;
		cout << v << " " << w << "\n";
	}
}
