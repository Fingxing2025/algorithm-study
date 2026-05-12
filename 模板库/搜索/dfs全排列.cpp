#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int a[N], n;
bool vis[N];
// step 表示当前要填写排列的第几个位置。
void dfs(int step)
{
	if (step > n)
	{
		// 当 step 走到 n+1，说明前 n 个位置都已经填完，得到一个完整排列。
		for (int i = 1; i <= n; ++i)
			cout << a[i];
		cout << "\n";
		return;
	}
	for (int i = 1; i <= n; ++i)
	{
		// 每个数字只能使用一次。
		if (!vis[i])
		{
			// 先标记数字 i 已经被放进当前排列。
			vis[i] = true;
			// 把数字 i 放到第 step 个位置。
			a[step] = i;
			// 继续递归去填写下一个位置。
			dfs(step + 1);
			// 回溯：撤销当前选择。
			// 这样后面的数字才能再次尝试填到这个位置上。
			vis[i] = false;
		}
	}
}
int main()
{
	cin >> n;
	// 从第 1 个位置开始逐步构造排列。
	dfs(1);
}
