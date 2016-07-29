#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, a[N];
int c[N * 10 + N];
int mx;
int getmax(int l)
{
	l = mx - l + 1;
	int s = 0;
	for(;l;l&=l-1) s = max(s, c[l]);
	return s;
}
void insert(int pos, int x)
{
	pos = mx - pos + 1;
	for(;pos <= mx; pos += pos & -pos) c[pos] = max(c[pos], x);
}
void input()
{
	mx = 0;
	scanf("%d", &n);

	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
}
void solve()
{
	int cnt0 = 0;
	for(int i = n; i >= 1; i--)
	{
		if(a[i] == 0)
		{
			cnt0++;
		}
		else
		{
			a[i] += cnt0;
		}
		mx = max(mx, a[i]);
	}

	for(int i = 0; i <= mx; i++) c[i] = 0;

	int ans = 1;
	cnt0 = 0;
	for(int i = n; i >= 1; i--)
	{
		if(a[i] == 0)
		{
			ans = getmax(1) + cnt0 + 1;
			cnt0++;
		}
		else
		{
			int tmp = getmax(a[i] + 1) + 1;
			insert(a[i], tmp);
			ans = max(ans, tmp + cnt0);
		}
	}
	printf("%d\n", ans);
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
