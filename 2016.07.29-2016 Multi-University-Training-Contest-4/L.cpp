#include <bits/stdc++.h>
using namespace std;
int n, a[100010];
int c[100010];
int l[100010], r[100010];
int get(int o)
{
	o = n - o + 1;
	int s = 0;
	for(;o;o&=o-1) s+=c[o];
	return s;
}
void add(int o)
{
	o = n - o + 1;
	for(;o <= n;o += o&-o) c[o]++;
}
void input()
{
	cin >> n;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), c[i] = 0;
}
void solve()
{
	for(int i = 1; i <= n; i++)
	{
		l[a[i]] = i - get(a[i]);
		add(a[i]);
		r[a[i]] = max(a[i], i);
	}
	for(int i = 1; i <= n; i++) printf("%d%c", r[i] - l[i], " \n"[i == n]);
}
int main()
{
	int t;
	cin >> t;
	for(int i = 1; i <= t; i++)
	{
		printf("Case #%d: ",i);
		input();
		solve();
	}
	return 0;
}
