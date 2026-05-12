#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll Mod = 998244353;
const ll G = 3, invG = 332748118;
// 快速幂。
ll qp(ll x, ll n)
{
	ll ans = 1;
	while (n > 0)
	{
		// 指数当前位为 1，就把这一位对应的贡献乘进答案。
		if (n & 1)
			ans = ans * x % Mod;
		// 底数平方，对应二进制位向更高位推进。
		x = x * x % Mod;
		// 继续处理下一位二进制位。
		n >>= 1;
	}
	return ans;
}
// NTT 本体：flag=false 为正变换，flag=true 为逆变换。
void ntt(vector<ll> &a, bool flag)
{
	int len = a.size();
	// 正变换用原根 G，逆变换用它在模意义下的逆元 invG。
	ll g = flag ? invG : G;
	// 位逆序重排。
	for (int i = 1, j = 0; i < len; ++i)
	{
		int bit = len >> 1;
		// 这段是在模拟“二进制加一”时从低位往高位的进位过程，
		// 最终得到 i 的 bit-reversal 对应位置 j。
		while (j & bit)
		{
			j ^= bit;
			bit >>= 1;
		}
		j ^= bit;
		// 若目标位置在后面，就交换到位逆序后的下标上。
		if (i < j)
			swap(a[i], a[j]);
	}
	// 蝴蝶操作，区间长度每次翻倍。
	for (int s = 2; s <= len; s <<= 1)
	{
		// wl 是当前层单位根，每次把 w 乘上 wl 就是在当前长度 s 的圆周上前进一步。
		ll wl = qp(g, (Mod - 1) / s);
		for (int i = 0; i < len; i += s)
		{
			ll w = 1;
			for (int j = 0; j < s / 2; ++j)
			{
				// u 是前半段当前点，v 是后半段当前点乘上旋转因子 w 后的值。
				ll u = a[i + j], v = (a[i + j + s / 2] * w) % Mod;
				// 两式就是 NTT 的标准蝶形合并：
				// 前半段得到 u+v，后半段得到 u-v。
				a[i + j] = (u + v) % Mod;
				a[i + j + s / 2] = (u - v + Mod) % Mod;
				// 更新到下一个位置对应的旋转因子。
				w = w * wl % Mod;
			}
		}
	}
	if (flag)
	{
		// 逆变换做完后，每个位置都要再乘上 len 的逆元，恢复真正的系数值。
		ll invn = qp(len, Mod - 2);
		for (int i = 0; i < len; ++i)
			a[i] = a[i] * invn % Mod;
	}
}
int main()
{
	int n1, n2, len = 1;
	cin >> n1 >> n2;
	// len 需要扩到不小于 n1+n2-1 的最小 2 的幂。
	while (len < n1 + n2 - 1)
		len <<= 1;
	// a、b 先装系数，c 用来装点值相乘后的结果。
	vector<ll> a(len, 0), b(len, 0), c(len, 0);
	for (int i = 0; i < n1; ++i)
		cin >> a[i];
	for (int i = 0; i < n2; ++i)
		cin >> b[i];
	ntt(a, false);
	ntt(b, false);
	// 点值相乘等价于系数卷积。
	for (int i = 0; i < len; ++i)
		c[i] = a[i] * b[i] % Mod;
	ntt(c, true);
	for (int i = 0; i < n1 + n2 - 1; ++i)
		cout << c[i] << " ";
}
