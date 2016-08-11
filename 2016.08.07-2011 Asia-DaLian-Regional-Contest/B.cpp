#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 50005;
#define ls o << 1, L, mid
#define rs o << 1 | 1, mid + 1, R

struct Input
{
	int x1, y1, x2, y2;
}a[N];
struct data
{
	int x1, y1, x2, y2;
}b[N];
int n, m, w, h;
int c[N * 2], top;

struct Line{int x, y1, y2, flag;}l[N * 2];
int tot;
bool cmp(const Line &A, const Line &B)
{
	return A.x < B.x;
}

int cover[N * 8];
int sum[N * 8];
void up(int o, int L, int R)
{
	if(cover[o]) sum[o] = c[R + 1] - c[L];
	else if(L != R) sum[o] = sum[o << 1] + sum[o << 1 | 1];
	else sum[o] = 0;
}
void sgt_add(int l, int r, int x, int o, int L, int R)
{
	if(r < l) return;
	if(l <= L && R <= r)
	{
		cover[o] += x;
		up(o, L, R);
		return;
	}
	int mid = L + R >> 1;
	if(r <= mid) sgt_add(l, r, x, ls);
	else if(l > mid) sgt_add(l, r, x, rs);
	else sgt_add(l, mid, x, ls), sgt_add(mid + 1, r, x, rs);
	up(o, L, R);
}
LL cal()
{
	tot = 0;

	for(int i = 1; i <= n; i++)
	{
		l[++tot].x = b[i].x1; l[tot].y1 = b[i].y1; l[tot].y2 = b[i].y2; l[tot].flag = 1;  c[tot] = b[i].y1;
		l[++tot].x = b[i].x2; l[tot].y1 = b[i].y1; l[tot].y2 = b[i].y2; l[tot].flag = -1; c[tot] = b[i].y2;
	}
	sort(c + 1, c + tot + 1);
	sort(l + 1, l + tot + 1, cmp);
	top = unique(c + 1, c + tot + 1) - c - 1;

	LL res = 0;

	for(int i = 1; i <= tot; i++)
	{
		int L = lower_bound(c + 1, c + top + 1, l[i].y1) - c;
		int R = lower_bound(c + 1, c + top + 1, l[i].y2) - c;
		if(i > 1) res += (LL) (l[i].x - l[i - 1].x) * sum[1];
		sgt_add(L, R - 1, l[i].flag, 1, 1, top - 1);
	}

	return res;
}
void solve()
{
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d%d%d", &a[i].x1, &a[i].y1, &a[i].x2, &a[i].y2);
		a[i].x1--;
		a[i].y1--;
	}

	LL ans = 0;
	for(int i = 1; i <= n; i++)
	{
		b[i].x1 = a[i].x1;
		b[i].y1 = max(m - 1, a[i].y1);
		b[i].x2 = a[i].x2;
		b[i].y2 = min(h, a[i].y2 + (m - 1));
	}
	ans += (LL) w * (h - m + 1) - cal();

	if(m == 1)
	{
		cout << ans << endl;
		return;
	}

	for(int i = 1; i <= n; i++)
	{
		b[i].x1 = max(m - 1, a[i].x1);
		b[i].y1 = a[i].y1;
		b[i].x2 = min(w, a[i].x2 + (m - 1));
		b[i].y2 = a[i].y2;
	}
	ans += (LL) (w - m + 1) * h - cal();

	cout << ans << endl;
}
int main()
{
	while(scanf("%d%d%d%d", &w, &h, &n, &m) == 4)
	{
		if(w == 0 && h == 0 && n == 0 && m == 0) break;
		top = 0;
		solve();
	}
	return 0;
}
