#include <bits/stdc++.h>

using namespace std;
const double eps = 1e-8;

int n, m, q;

int fa[50005];
char ans[50005];
int cnt[20];
struct Data
{
	char op;
	int x, y, l, w, r, c;
}a[50005];

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
void color(int l, int r, int c)
{
	if(l < 1) l = 1;
	if(r > m) r = m;
	for(int j = l; j <= r; )
	{
		if(!ans[j])
		ans[j] = c;
		fa[j] = find(j + 1);
		j = fa[j];
	}
}
void solve()
{
	char ch[20];
	for(int i = 1; i <= q; i++)
	{
		scanf("%s", ch);
		if(ch[0] == 'C')
		{
			a[i].op = 'C';
			scanf("%d%d%d%d", &a[i].x, &a[i].y, &a[i].r, &a[i].c);
			a[i].x++;
			a[i].y++;
		}
		else if(ch[0] == 'D')
		{
			a[i].op = 'D';
			scanf("%d%d%d%d", &a[i].x, &a[i].y, &a[i].r, &a[i].c);
			a[i].x++;
			a[i].y++;
		}
		else if(ch[0] == 'R')
		{
			a[i].op = 'R';
			scanf("%d%d%d%d%d", &a[i].x, &a[i].y, &a[i].l, &a[i].w, &a[i].c);
			a[i].x++;
			a[i].y++;
		}
		else
		{
			a[i].op = 'T';
			scanf("%d%d%d%d", &a[i].x, &a[i].y, &a[i].w, &a[i].c);
			a[i].x++;
			a[i].y++;
			a[i].x += a[i].w - 1 >> 1;
		} 
	}

	memset(cnt, 0, sizeof cnt);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			fa[j] = j;
			ans[j] = 0;
		}
		fa[m + 1] = m + 1;

		for(int j = q; j >= 1; j--)
		{
			int x = a[j].x, y = a[j].y, c = a[j].c;
			if(a[j].op == 'C')
			{
				int r = a[j].r;
				if(max(1, x - r) <= i && i <= min(n, x + r))
				{
					int tmp = (int) sqrt(r * r - (x - i) * (x - i) + eps);
					int y1 = x - tmp, y2 = x + tmp;
					color(y1, y2, c);
				}
			}
			else if(a[j].op == 'D')
			{
				int r = a[j].r;
				if(max(1, x - r) <= i && i <= min(n, x + r))
				{
					color(y - r + abs(i - x), y + r - abs(i - x), c);
				}
			}
			else if(a[j].op =='R')
			{
				int l = a[j].l, w = a[j].w;
				if(max(1, x) <= i && i <= min(n, x + l - 1))
				{
					color(y, y + w - 1, c);
				}
			}
			else
			{
				int w = a[j].w;
				if(max(1, x - ((w + 1) / 2 - 1)) <= i && i <= min(n, x))
				{
					color(max(1, y - abs(i - x)), min(m, y + abs(i - x)), c);
				}
			}
		}
		for(int j = 1; j <= m; j++) cnt[ans[j]]++;
	}
		
	for(int i = 1; i <= 9; i++) printf("%d%c", cnt[i], " \n"[i == 9]);
}
int main()
{
	while(scanf("%d%d%d", &n, &m, &q) == 3)
	{
		if(n == 0 && m == 0 && q == 0) break;
		solve();
	}
	return 0;
}
