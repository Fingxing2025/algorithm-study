#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;
using u128 = __uint128_t;

// 把 __int128 转成字符串，方便把精确乘积直接输出出来。
// 常见场景是 long long * long long 会溢出，但 __int128 能先把真实结果托住。
string toString128(i128 value)
{
	if (value == 0)
		return "0";
	bool is_negative = value < 0;
	u128 magnitude = is_negative ? static_cast<u128>(-(value + 1)) + 1 : static_cast<u128>(value);
	string digits;
	while (magnitude > 0)
	{
		digits.push_back(char('0' + magnitude % 10));
		magnitude /= 10;
	}
	if (is_negative)
		digits.push_back('-');
	reverse(digits.begin(), digits.end());
	return digits;
}

void print128(i128 value)
{
	cout << toString128(value);
}

// 把数规范到 [0, mod - 1]，这样后面的取模乘法和快速幂都能统一处理负数底数。
ll normalizeMod(ll value, ll mod)
{
	value %= mod;
	if (value < 0)
		value += mod;
	return value;
}

// 安全计算 (a * b) % mod。
// 核心思想是先把乘法放到 __int128 里做，再对 mod 取余，避免 long long 中间乘积溢出。
// 这个写法适用于 a、b、mod 本身都在 long long 范围内的常见竞赛题。
ll multiplyMod(ll a, ll b, ll mod)
{
	a = normalizeMod(a, mod);
	b = normalizeMod(b, mod);
	return static_cast<ll>((static_cast<i128>(a) * b) % mod);
}

// 二进制快速幂。
// 每次遇到指数当前位是 1，就把答案乘上当前底数；
// 每轮都把底数平方，并把指数右移一位。
// 这里所有乘法都通过 multiplyMod 完成，保证不会在 long long 乘法时炸掉。
ll fastPowerMod(ll base, ll exponent, ll mod)
{
	base = normalizeMod(base, mod);
	ll result = 1 % mod;
	while (exponent > 0)
	{
		if (exponent & 1)
			result = multiplyMod(result, base, mod);
		base = multiplyMod(base, base, mod);
		exponent >>= 1;
	}
	return result;
}

/*
输入格式：
一行输入四个整数 a、b、exponent、mod。

含义说明：
a、b 用来演示“先乘再取模”时如何避免 long long 中间乘积溢出。
exponent、mod 用来演示 a^exponent mod mod 的快速幂写法。

使用前提：
1. a、b、exponent、mod 都在 long long 范围内。
2. exponent >= 0。
3. mod > 0。

输入样例：
123456789123456789 987654321987654321 1234567 1000000007

输出样例：
a * b = 121932631356500531347203169112635269
(a * b) % mod = 327846861
a^exponent % mod = 346632033

补充说明：
如果 a、b、mod 本身已经是 __int128 级别，这种“直接用 __int128 托乘法”的写法就不一定够了，
因为 __int128 * __int128 仍然可能溢出。那种场景通常要改用龟速乘、Barrett Reduction 或 Montgomery。
*/

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll a, b, exponent, mod;
	cin >> a >> b >> exponent >> mod;

	if (mod <= 0)
	{
		cout << "mod must be positive\n";
		return 0;
	}
	if (exponent < 0)
	{
		cout << "exponent must be non-negative\n";
		return 0;
	}

	// 这是“精确乘积”展示，说明 __int128 能兜住两个 long long 的乘法结果。
	i128 exact_product = static_cast<i128>(a) * b;
	cout << "a * b = ";
	print128(exact_product);
	cout << '\n';

	// 这是竞赛里更常见的写法：虽然最终只要模意义下的值，
	// 但中间乘法先放进 __int128，避免 long long 溢出后再取模变错。
	cout << "(a * b) % mod = " << multiplyMod(a, b, mod) << '\n';

	// 快速幂中的每一步乘法也都要经过 multiplyMod，
	// 否则 base * base 或 result * base 仍然可能在 long long 上溢出。
	cout << "a^exponent % mod = " << fastPowerMod(a, exponent, mod) << '\n';

	// 常用编译命令：g++ -std=c++17 int128快速幂与防溢出乘法.cpp
	return 0;
}