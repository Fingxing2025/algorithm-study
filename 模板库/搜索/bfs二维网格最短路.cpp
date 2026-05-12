#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
// 四联通方向数组：右、下、左、上。
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int n, m, edx, edy;
bool vis[N][N];
struct Node
{
	int x, y, dist;
};
// BFS 适用于边权全为 1 的最短路。
// 队列中保存当前位置以及从起点到这里的步数。
int bfs(int stx, int sty)
{
	queue<Node> q;
	q.push({stx, sty, 0});
	vis[stx][sty] = true;
	while (!q.empty())
	{
		Node cur = q.front();
		q.pop();
		if (cur.x == edx && cur.y == edy)
			return cur.dist;
		for (int i = 0; i < 4; ++i)
		{
			int tx = cur.x + dx[i];
			int ty = cur.y + dy[i];
			// 只有在边界内且没访问过时才入队，否则会重复扩展同一个点。
			if (tx > 0 && tx <= n && ty > 0 && ty <= m && !vis[tx][ty])
			{
				vis[tx][ty] = true;
				q.push({tx, ty, cur.dist + 1});
			}
		}
	}
	return -1;
}
int main()
{
}
