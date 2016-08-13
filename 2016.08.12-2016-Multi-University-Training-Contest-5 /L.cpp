#include <bits/stdc++.h>

using namespace std;

int n, a[50005];
int t[50005], m;

int c[50005];
int l1[50005], r1[50005], l2[50005], r2[50005];

int query(int o)
{
	int s = 0;
	for(;o;o&=o-1) s += c[o];
	return s;
}
void add(int o, int x)
{
	for(;o<=m;o+=o&-o) c[o]+=x;
}

void solve()
{
	long long tmp1 = 0, tmp2 = 0;

	for(int i = 1; i <= m; i++) c[i] = 0;
	for(int i = 1; i <= n; i++)
	{
		l1[i] = query(a[i] - 1);
		l2[i] = i - 1 - query(a[i]);
		add(a[i], 1);

		tmp1 += l1[i];
		tmp2 += l2[i];
	}
	for(int i = 1; i <= m; i++) c[i] = 0;
	for(int i = n; i>= 1; i--)
	{
		r1[i] = query(a[i] - 1);
		r2[i] = n - i - query(a[i]);
		add(a[i],  1);
	}

	long long ans = 0;
	ans = tmp1 * tmp2;

	for(int i = 1; i <= n; i++)
	{
		ans -= (long long) l2[i] * r2[i];
		ans -= (long long) r1[i] * r2[i];
		ans -= (long long) l1[i] * l2[i];
		ans -= (long long) l1[i] * r1[i];
	}

	cout << ans << endl;

}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), t[i] = a[i];
		sort(t+1,t+n+1);
		m = unique(t + 1, t + n + 1) - t - 1;
		for(int i = 1; i <= n; i++) a[i] = lower_bound(t + 1, t + m + 1, a[i]) - t;
		solve();
	}
	return 0;
}
