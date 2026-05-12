#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // 用于 reverse
using namespace std;

// 这些高精度函数都采用“低位在前”的 vector<int> 存储方式。
// ==========================================
// 0. 辅助函数：比较 A 是否大于等于 B
// ==========================================
bool cmp(vector<int> &A, vector<int> &B)
{
    // 位数不同，位数更长的数一定更大。
    if (A.size() != B.size())
        return A.size() > B.size();
    // 位数相同时，从最高位往低位逐位比较。
    for (int i = A.size() - 1; i >= 0; i--)
    {
        if (A[i] != B[i])
            return A[i] > B[i];
    }
    return true; // A == B 时也返回 true
}

// ==========================================
// 1. 高精度加法 (A + B)
// ==========================================
vector<int> add(vector<int> &A, vector<int> &B)
{
    vector<int> C;
    int t = 0; // 进位
    for (int i = 0; i < A.size() || i < B.size(); i++)
    {
        // t 在进入这一轮时，先携带上一次留下来的进位。
        if (i < A.size())
            t += A[i];
        if (i < B.size())
            t += B[i];
        // 当前位存个位，十位及以上继续作为下一轮的进位。
        C.push_back(t % 10);
        t /= 10;
    }
    // 最后一轮若还有进位，就补成新的最高位。
    if (t)
        C.push_back(1);
    return C;
}

// ==========================================
// 2. 高精度减法 (A - B) -> 前提保证 A >= B
// ==========================================
vector<int> sub(vector<int> &A, vector<int> &B)
{
    vector<int> C;
    int t = 0; // 借位
    for (int i = 0; i < A.size(); i++)
    {
        // t 此时只会是 0 或 1，表示上一位是否向当前位借过 1。
        t = A[i] - t;
        if (i < B.size())
            t -= B[i];
        // (t+10)%10 统一处理“够减”和“不够减”两种情况，得到当前位结果。
        C.push_back((t + 10) % 10);
        // 若当前位不够减，说明下一位还得继续借 1。
        if (t < 0)
            t = 1;
        else
            t = 0;
    }
    // 去除前导零
    while (C.size() > 1 && C.back() == 0)
        C.pop_back();
    return C;
}

// ==========================================
// 3. 高精度乘法 (A * B)
// ==========================================
// 高精度加法。
vector<int> mul(vector<int> &A, vector<int> &B)
{
    vector<int> C(A.size() + B.size(), 0);
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < B.size(); j++)
        {
            // A[i] 与 B[j] 的乘积，会落到结果的第 i+j 位上。
            C[i + j] += A[i] * B[j];
        }
    }
    int t = 0;
    for (int i = 0; i < C.size(); i++)
    {
        // 把前面累计在这一位上的值和进位一起结算。
        t += C[i];
        C[i] = t % 10;
        t /= 10;
    }
    while (C.size() > 1 && C.back() == 0)
        C.pop_back();
    return C;
}
// 高精度减法，使用前要保证 A >= B。

// ==========================================
// 4. 高精度 除以 低精度 (A / b) -> b 是普通 int
// ==========================================
vector<int> div_low(vector<int> &A, int b, int &r)
{
    vector<int> C;
    r = 0;
    // 从高位开始
    for (int i = A.size() - 1; i >= 0; i--)
    {
        // 把余数左移一位，再拼上当前数字，模拟手算长除法。
        r = r * 10 + A[i];
        C.push_back(r / b);
        // 当前位商写下后，剩下的就是下一位要继续往下带的余数。
        r %= b;
    }
    reverse(C.begin(), C.end()); // 翻转以统一格式
    while (C.size() > 1 && C.back() == 0)
        C.pop_back();
    return C;
}

// 高精度乘法：朴素竖式乘法。
// ==========================================
// 5. 高精度 除以 高精度 (A / B)
// 注意：参数 A 传值而不是引用，因为内部要不断改变 A 的值
// ==========================================
vector<int> div_high(vector<int> A, vector<int> &B, vector<int> &R)
{
    vector<int> C;
    if (!cmp(A, B))
    { // A < B，商 0 余 A
        R = A;
        C.push_back(0);
        return C;
    }

    int len_diff = A.size() - B.size();
    vector<int> B_shifted = B;
    // B 后面补 0对齐
    B_shifted.insert(B_shifted.begin(), len_diff, 0);

    for (int i = 0; i <= len_diff; i++)
    {
        int q = 0; // 当前位的商
        // 当前位置的商，就是“当前对齐后的除数还能从 A 里减掉多少次”。
        while (cmp(A, B_shifted))
        {
            A = sub(A, B_shifted); // 疯狂相减
            q++;
        }
        C.push_back(q);
        if (!B_shifted.empty())
        {
            // 去掉一位 0，相当于把除数整体右移一位，开始试商下一位。
            B_shifted.erase(B_shifted.begin()); // 删掉开头的 0，右移一位
        }
    }

    reverse(C.begin(), C.end());
    while (C.size() > 1 && C.back() == 0)
        C.pop_back();
    R = A; // A 被减剩下的就是余数
    return C;
}

// ==========================================
// 统一的输出函数
// 高精度除以高精度，R 返回余数。
// ==========================================
void print(const vector<int> &C)
{
    if (C.empty())
    {
        cout << 0 << endl;
        return;
    }
    for (int i = C.size() - 1; i >= 0; i--)
    {
        cout << C[i];
    }
    cout << endl;
}

// ==========================================
// 主函数示例：测试输入与调用
// ==========================================
int main()
{
    // 假设读入两个大整数 A 和 B
    string str_a = "12345678901234567890"; // 被除数 / 操作数1
    string str_b = "987654321098765432";   // 除数 / 操作数2

    vector<int> A, B;
    // 输入字符串转倒序数位数组，统一成前面所有函数使用的格式。
    for (int i = str_a.size() - 1; i >= 0; i--)
        A.push_back(str_a[i] - '0');
    for (int i = str_b.size() - 1; i >= 0; i--)
        B.push_back(str_b[i] - '0');

    // 1. 加法
    cout << "A + B = ";
    print(add(A, B));

    // 2. 减法
    cout << "A - B = ";
    if (cmp(A, B))
        print(sub(A, B));
    else
    {
        cout << "-";
        print(sub(B, A));
    }

    // 3. 乘法
    // 统一输出高精度结果。
    cout << "A * B = ";
    print(mul(A, B));

    // 4. 高精除低精
    int low_b = 12345;
    int r_low = 0;
    vector<int> C_low = div_low(A, low_b, r_low);
    cout << "A / " << low_b << " = ";
    print(C_low);
    cout << "余数(低精) = " << r_low << endl;

    // 5. 高精除高精
    vector<int> R_high; // 高精度余数
    vector<int> C_high = div_high(A, B, R_high);
    cout << "A / B = ";
    print(C_high);
    cout << "余数(高精) = ";
    print(R_high);

    return 0;
}
