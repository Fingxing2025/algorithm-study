#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

/*
    单调队列优化线性 DP。

    模型特征：
    dp[i] 需要从某个滑动窗口 [i-r, i-l] 内的最优 dp[j] 转移而来。

    若朴素枚举前驱，复杂度通常是 O(n(r-l+1))。
    由于每次只需要窗口中的最大值，因此可以用单调队列把复杂度降到 O(n)。

    队列里存的是下标，不是值。
    这样既能比较 dp 值大小，也能判断下标是否已经滑出窗口。
*/

// 定义一个安全的极小值，既能代表"不可达"，又防止加上负数得分时引发 int 溢出。
const int INF = 1e9;

int main()
{
    // 基础的输入输出加速
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, l, r;
    if (!(cin >> n >> l >> r))
        return 0;

    vector<int> a(n + 1);
    for (int i = 0; i <= n; ++i)
    {
        cin >> a[i];
    }

    // dp[i] 表示跳到第 i 个格子时能获得的最大分数
    // 初始化为 -INF 代表该位置暂时不可达
    vector<int> dp(n + 1, -INF);
    dp[0] = a[0]; // 起点分数

    deque<int> q; // 单调队列，里面维护的是当前窗口内可能成为最优前驱的下标。

    // 核心 DP 状态转移
    for (int i = l; i <= n; ++i)
    {
        int enter_idx = i - l; // 当前即将进入滑动窗口的下标

        // 1. 维护队列里的 dp 值单调递减。
        // 新进入的状态若更优，则队尾那些更差的状态以后都不会再被用到。
        while (!q.empty() && dp[q.back()] <= dp[enter_idx])
        {
            q.pop_back();
        }
        q.push_back(enter_idx); // 将新下标入队

        // 2. 剔除已经滑出合法窗口的下标。
        while (!q.empty() && q.front() < i - r)
        {
            q.pop_front();
        }

        // 3. 队头就是当前窗口内 dp 最大的可用前驱。
        if (!q.empty() && dp[q.front()] != -INF)
        {
            dp[i] = a[i] + dp[q.front()];
        }
    }

    // 4. 统计最终答案
    // 只要处于能一步跳出终点 (即越过 n) 的位置，就是合法的结局位置。
    // 能跳过 n 的合法起点范围是 [n - r + 1, n]
    int ans = -INF;
    for (int i = n - r + 1; i <= n; ++i)
    {
        if (i >= 0)
        { // 防止跳跃距离极大导致下标出现负数
            ans = max(ans, dp[i]);
        }
    }

    cout << ans << "\n";

    return 0;
}
