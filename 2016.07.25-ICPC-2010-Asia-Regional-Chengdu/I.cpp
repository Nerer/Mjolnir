#include <bits/stdc++.h>
using namespace std;
#define ls o << 1, L, mid
#define rs o << 1 | 1, mid + 1, R
typedef long long LL;
const int N = 50005;
int n, k;
int a[N], mx;
LL add[3][N];
void Add(LL *c, int o, LL x)
{
	for(;o;o -= o&-o) c[o] += x;
}
LL Query(LL *c, int o)
{
	LL s = 0;
	for(;o <= n; o+=o&-o) s += c[o];
	return s;
}
void modify(LL pos, LL x, LL k)
{
	int range = int(sqrt(x) + 1e-8);
	int l = pos - range;
	if(l <= 0) l = 1;
	Add(add[0], pos, k * ((LL)pos * pos - x));
	Add(add[0], l - 1, -k * ((LL)pos * pos - x));
	Add(add[1], pos, -2 * (LL)k * pos);
	Add(add[1], l - 1, 2 * (LL)k * pos);
	Add(add[2], pos, k);
	Add(add[2], l - 1, -k);
}
LL query(LL x)
{
	LL ret0 = Query(add[0], x);
	LL ret1 = Query(add[1], x);
	LL ret2 = Query(add[2], x);
	return a[x] + ret0 + ret1 * x + ret2 * x * x;
}
void input()
{
	mx = 0;
	cin >> n >> k;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		mx = max(mx, a[i]);
	}
}
bool check(LL mid)
{
	int cnt = 0;
	for(int i = 0; i < 3; i++)
		for(int j = 1; j <= n; j++)
			add[i][j] = 0;
	
	for(int i = n; i >= 1; i--)
	{
		LL tmp = query(i);
		if(tmp >= 0)
		{
			int kk = tmp / mid + 1;
			cnt += kk;
			if(cnt > k) return 0;
			modify(i, mid, kk);
		}
	}
	return 1;
}
void solve()
{
	LL l = 1, r = (LL) n * n + mx, mid;
	while(l < r)
	{
		mid = l + r >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l << endl;
}
int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		input();
		solve();
	}
	return 0;
}
