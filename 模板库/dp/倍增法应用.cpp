#include <bits/stdc++.h>
using namespace std;

/*
    合并型 DP / 倍增式区间合并模板。

    状态定义：
    f[x][i] 表示从位置 i 开始，是否能拼出一个“值为 x”的合法区间；
    如果能，f[x][i] 记录该区间结束后的下一个位置。

    这样设计的好处：
    当要继续往后拼接下一段时，不需要重新找终点，直接跳到 f[x][i] 即可。

    核心转移：
    若从 i 开始能拼出一段值为 x-1 的区间，且紧接着还能再拼出一段值为 x-1 的区间，
    那么这两段就能合并成一段值为 x 的区间。
*/

int f[60][270000], n, ans = 0;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        int num;
        cin >> num;

        // 初始时，每个位置本身就能作为长度为 1 的一个基础块。
        f[num][i] = i + 1;
    }
    for (int i = 2; i <= 58; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            // 若两段值为 i-1 的区间首尾相接，就能合并成一段值为 i 的区间。
            if (!f[i][j])
                f[i][j] = f[i - 1][f[i - 1][j]];
            if (f[i][j])
                ans = i;
        }
    }
    cout << ans;
    return 0;
}
