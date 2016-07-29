#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL x, y;
void exGcd(LL a, LL b)
{
	if (b == 0) {
		x = 1;
		y = 0;
		return;
	}
	exGcd(b, a % b);
	LL k = y;
	y = x - a / b * y;
	x = k;
}
LL inversion(LL a, LL b)
{
	exGcd(a, b);
	return (x % b + b) % b;
}

LL CRT(vector<LL> m, vector<LL> a)
{
	int N = (int) m.size();
	LL M = 1, ret = 0;
	for(int i = 0; i < N; ++ i)
		M *= m[i];
	
	for(int i = 0; i < N; ++ i) {
		ret = (ret + (M / m[i]) * a[i] % M * inversion(M / m[i], m[i])) % M;
	}
	return ret;
}

int n;
LL l, r;
LL p[20], a[20];
vector <LL> pp, aa;
void input()
{
	cin >> n >> l >> r;
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld%lld", &p[i], &a[i]);
	}
}
LL cal(LL n, LL x, LL lcm)
{
	if(n == 0) return 0;
	if(n < x) return 0;
	if (x == 0) {
		return (n - x) / lcm;
	} else {
		return (n - x) / lcm + 1;
	}
}
void solve()
{
	LL ans = 0;
	for(int s = 1; s < (1 << n); s++)
	{
		pp.clear();
		aa.clear();
		LL lcm = 1, x;
		for(int i = 1; i <= n; i++) if(s >> i - 1 & 1)
		{
			pp.push_back(p[i]);
			aa.push_back(a[i]);
			lcm = lcm * p[i];
		}
		pp.push_back(7);
		aa.push_back(0);
		lcm *= 7;
		x = CRT(pp, aa);
		LL tmp = cal(r, x, lcm) - cal(l - 1, x, lcm);
		if(__builtin_popcount(s) & 1) ans += tmp;
		else ans -= tmp;
	}
	ans = r / 7 - (l - 1) / 7 - ans;
	cout << ans << endl;
}
int main()
{
	int t;
	cin >> t;
	for(int i = 1; i <= t; i++)
	{
		printf("Case #%d: ", i);
		input();
		solve();
	}
	return 0;
}
