#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll Mod = 998244353;

// 最大公约数。
ll gcd(ll a, ll b)
{ // 最大公约数
	// 欧几里得算法：gcd(a,b)=gcd(b,a mod b)。
	// 当 b 变成 0 时，当前的 a 就是答案。
	return b == 0 ? a : gcd(b, a % b);
}
// 最小公倍数。
ll lcm(ll a, ll b)
{ // 最小公倍数
	// 先除后乘，避免直接 a*b 时更容易溢出。
	return a / gcd(a, b) * b;
}
// 快速幂：计算 x^n mod Mod。
ll qp(ll x, ll n)
{ // 快速幂
	ll ans = 1;
	// 先把底数压到模意义下，后面每次乘法都保持在 mod 范围内。
	x %= Mod;
	while (n > 0)
	{
		// 若当前二进制位为 1，就把这一位贡献乘进答案。
		if (n & 1)
			ans = (ans * x) % Mod;
		// 底数平方，对应“二进制位向高位推进一位”。
		x = (x * x) % Mod;
		// 指数右移，继续处理下一位二进制位。
		n >>= 1;
	}
	return ans;
}
const int N = 1e6 + 5;
bool is_prime[N];
int prime[N], cnt = 0;
// 线性筛：prime 数组中保存所有质数。
void sieve(int n)
{ // 线性筛
	// 先默认 [2,n] 都可能是质数，后面在筛的过程中再删掉合数。
	fill(is_prime + 2, is_prime + n + 1, true);
	for (int i = 2; i <= n; ++i)
	{
		// 若 i 还没被筛掉，说明它是质数，收进 prime 数组。
		if (is_prime[i])
			prime[cnt++] = i;
		for (int j = 0; j < cnt && i * prime[j] <= n; ++j)
		{
			// 每个合数 i*prime[j] 在这里第一次被它的最小质因子筛掉。
			is_prime[i * prime[j]] = false;
			// 一旦 prime[j] 是 i 的最小质因子，就必须停下。
			// 这样才能保证每个合数只被筛一次，这就是线性筛名字的来源。
			if (i % prime[j] == 0)
				break;
		}
	}
}
int main()
{
}
