#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
const LL mod = 1e9 + 7;

int n;
int p[20], cnt;
LL ans;

LL pow_mod(LL a,LL b,LL p){LL t=1;for(;b;b>>=1,a=a*a%p)if(b&1)t=t*a%p;return t;}
LL cal(LL n)
{
	return n * (n + 1) % mod * (2 * n + 1) % mod * ((3 * n * n + 3 * n - 1) % mod) % mod * pow_mod(30, mod - 2, mod) % mod;
}
LL sqr(LL n)
{
	return n * n % mod;
}
void dfs(int pos, int sign, LL cur)
{
	if(pos == cnt + 1)
	{
		if(cur == 1) return;
		if(sign == 1) ans -= sqr(cur) * sqr(cur) % mod * cal(n / cur) % mod;
		else          ans += sqr(cur) * sqr(cur) % mod * cal(n / cur) % mod;
		ans %= mod;
		return;
	}
	dfs(pos + 1, sign, cur);
	dfs(pos + 1, -sign, cur * p[pos]);
}

void solve()
{
	int m = n;
	cnt = 0;
	int sq = (int) sqrt(n + 1e-5);
	for(int i = 2; i <= sq; i++) if(n % i == 0)
	{
		p[++cnt] = i;
		while(n % i == 0) n /= i;
	}
	if(n > 1) p[++cnt] = n;
	n = m;

	ans = 0;
	dfs(1, 1, 1);
	ans = cal(1LL * n) - ans;
	cout << (ans % mod + mod) % mod << endl;
}
int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		scanf("%d", &n);
		solve();
	}
	return 0;
}
