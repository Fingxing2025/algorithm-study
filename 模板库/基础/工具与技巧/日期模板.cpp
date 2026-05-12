#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 闰年判断和每月天数模板。
// 1. 基础工具：月份天数表与闰年判断
int daysOfMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isLeap(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int getDays(int y, int m)
{
    if (m == 2 && isLeap(y))
        return 29;
    return daysOfMonth[m];
}

// 把日期转成“从某个基准点开始累计的天数”，便于做日期差。
// 2. 日期转天数 (用于计算两个日期之间的差值)
// 原理：将日期转换为从公元0年开始的总天数
long long dateToDays(int y, int m, int d)
{
    long long total = 0;
    for (int i = 0; i < y; i++)
        total += isLeap(i) ? 366 : 365;
    for (int i = 1; i < m; i++)
        total += getDays(y, i);
    total += d;
    return total;
}

// 日期往后平移 n 天。
// 3. 日期累加 (用于求 N 天后的日期)
void addDays(int &y, int &m, int &d, int n)
{
    d += n;
    while (d > getDays(y, m))
    {
        d -= getDays(y, m);
        m++;
        if (m > 12)
        {
            m = 1;
            y++;
        }
    }
}

// 求星期，返回值范围为 0~6。
// 4. 计算星期几 (基姆拉尔森公式)
// 返回 0-6，0代表星期日，1-6代表星期一到星期六
int getWeekday(int y, int m, int d)
{
    if (m == 1 || m == 2)
    {
        m += 12;
        y--;
    }
    return (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400 + 1) % 7;
}

// main 只是演示这些日期函数如何调用。
// ==========================================
// 主函数示例：如何灵活运用
// ==========================================
int main()
{
    // 示例：日期差值
    int y1 = 2026, m1 = 4, d1 = 20;
    int y2 = 2026, m2 = 5, d2 = 1;
    long long diff = abs(dateToDays(y1, m1, d1) - dateToDays(y2, m2, d2));
    cout << "相差天数: " << diff << endl;

    // 示例：N 天后的日期
    addDays(y1, m1, d1, 10);
    cout << "10天后是: " << y1 << "-" << m1 << "-" << d1 << endl;

    // 示例：星期几
    cout << "今天是星期: " << getWeekday(2026, 4, 20) << endl;

    return 0;
}
