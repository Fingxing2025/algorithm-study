#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1000000 + 5;
const int V = 1000000 + 5;
const int S = 1024;
const int B = 2005;
const int LG = 12;

int n, q, a[N], head[V], nxt[N], fa[N], sz[N], c[N], bel[N], L[B], R[B], st[B][LG], Log2[B];
int maxa;
ll w[N], lastans;
unsigned char vis[N];

inline int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}

inline bool cmp(int x, int y)
{
	if (!x || !c[x])
		return false;
	if (!y || !c[y])
		return true;
	__int128 t1 = (__int128)w[x] * c[y];
	__int128 t2 = (__int128)w[y] * c[x];
	if (t1 != t2)
		return t1 > t2;
	return c[x] > c[y];
}

inline int find(int x)
{
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int main()
{
	for (int i = 2; i < B; ++i)
		Log2[i] = Log2[i >> 1] + 1;

	n = read();
	q = read();
	for (int i = 1; i <= n; ++i)
	{
		a[i] = read();
		if (a[i] > maxa)
			maxa = a[i];
		nxt[i] = head[a[i]];
		head[a[i]] = i;
		fa[i] = i;
		sz[i] = 1;
	}

	ll sum = 0;
	int cnt = 0;
	for (int num = 1; num <= maxa; ++num)
	{
		if (!head[num])
			continue;
		for (int p = head[num]; p; p = nxt[p])
		{
			vis[p] = 1;
			++cnt;
			++sum;
			if (p > 1 && vis[p - 1])
			{
				int x = find(p - 1), y = find(p);
				if (x != y)
				{
					if (sz[x] < sz[y])
						swap(x, y);
					sum -= 1LL * sz[x] * sz[x];
					sum -= 1LL * sz[y] * sz[y];
					fa[y] = x;
					sz[x] += sz[y];
					sum += 1LL * sz[x] * sz[x];
					--cnt;
				}
			}
			if (p < n && vis[p + 1])
			{
				int x = find(p + 1), y = find(p);
				if (x != y)
				{
					if (sz[x] < sz[y])
						swap(x, y);
					sum -= 1LL * sz[x] * sz[x];
					sum -= 1LL * sz[y] * sz[y];
					fa[y] = x;
					sz[x] += sz[y];
					sum += 1LL * sz[x] * sz[x];
					--cnt;
				}
			}
		}

		if (!c[cnt])
		{
			w[cnt] = sum;
			c[cnt] = num;
		}
		else
		{
			__int128 t1 = (__int128)sum * c[cnt];
			__int128 t2 = (__int128)w[cnt] * num;
			if (t1 > t2 || (t1 == t2 && num > c[cnt]))
			{
				w[cnt] = sum;
				c[cnt] = num;
			}
		}
	}

	int tot = (n + S - 1) / S;
	for (int i = 1; i <= tot; ++i)
	{
		L[i] = (i - 1) * S + 1;
		R[i] = min(n, i * S);
		for (int j = L[i]; j <= R[i]; ++j)
		{
			bel[j] = i;
			if (cmp(j, st[i][0]))
				st[i][0] = j;
		}
	}

	for (int j = 1; (1 << j) <= tot; ++j)
	{
		for (int i = 1; i + (1 << j) - 1 <= tot; ++i)
		{
			int x = st[i][j - 1], y = st[i + (1 << (j - 1))][j - 1];
			st[i][j] = cmp(x, y) ? x : y;
		}
	}

	for (int i = 1; i <= q; ++i)
	{
		ll aa = read(), bb = read(), x = read(), y = read();
		ll lst = lastans;
		ll l = (aa * lst + x - 1) % n + 1;
		ll r = (bb * lst + y - 1) % n + 1;
		if (l > r)
			swap(l, r);

		int ans = 0;
		if (bel[l] == bel[r])
		{
			for (int j = (int)l; j <= (int)r; ++j)
			{
				if (cmp(j, ans))
					ans = j;
			}
		}
		else
		{
			for (int j = (int)l; j <= R[bel[l]]; ++j)
			{
				if (cmp(j, ans))
					ans = j;
			}
			for (int j = L[bel[r]]; j <= (int)r; ++j)
			{
				if (cmp(j, ans))
					ans = j;
			}
			if (bel[r] - bel[l] > 1)
			{
				int l1 = bel[l] + 1, r1 = bel[r] - 1;
				int k = Log2[r1 - l1 + 1];
				int x1 = st[l1][k], x2 = st[r1 - (1 << k) + 1][k];
				int m = cmp(x1, x2) ? x1 : x2;
				if (cmp(m, ans))
					ans = m;
			}
		}

		if (!ans)
		{
			printf("-1 -1\n");
			printf("%lld %lld %lld\n", l, r, lst);
			lastans = 1 % n;
		}
		else
		{
			printf("%lld %d\n", w[ans], c[ans]);
			printf("%lld %lld %lld\n", l, r, lst);
			lastans = (ll)((__int128)w[ans] * c[ans] % n);
		}
	}

	return 0;
}