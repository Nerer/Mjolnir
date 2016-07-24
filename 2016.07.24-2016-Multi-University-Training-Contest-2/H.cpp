#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int N = 1010;
const int M = 5e5 + 10;
int n, m;
int a[N];
int sum0[N], sum1[N];
struct data
{
	int x, y1, y2, type, id;
}b[(N * N * 2 + M) * 2];
int cnt;
int t[(N * N * 2 + M) * 2], top;
int ans[M];
int c[(N * N * 2 + M) * 2];
void add(int o, int x)
{
	for(;o; o -= o & -o)
	{
		c[o] += x;
	}
}
int query(int o)
{
	int s = 0;
	for(;o <= top; o += o & -o)
	{
		s += c[o];
	}
	return s;
}
bool cmp(const data &A, const data &B)
{
	if(A.x != B.x) return A.x < B.x;
	return A.type < B.type;
}
void addrect(int x1, int y1, int x2, int y2)
{
	cnt++;
	b[cnt].x = x1;
	b[cnt].y1 = y1;
	b[cnt].y2 = y2;
	b[cnt].type = 1;

	cnt++;
	b[cnt].x = x2;
	b[cnt].y1 = y1;
	b[cnt].y2 = y2;
	b[cnt].type = 3;
}
void addpoint(int x, int y, int id)
{
	cnt++;
	b[cnt].x = x;
	b[cnt].y1 = y;
	b[cnt].type = 2;
	b[cnt].id = id;
}
void input()
{
	cnt = top = 0;

	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		sum0[i] = sum0[i - 1];
		sum1[i] = sum1[i - 1];
		if(i & 1)
		{
			sum0[i] += a[i];
		}
		else
		{
			sum1[i] += a[i];
		}
	}
	for(int i = 1; i <= n; i++)
		for(int j = i; j <= n; j++)
		{
			int x1, y1, x2, y2;
			if(i == j)
			{
				if(i & 1)
				{
					y1 = y2 = 0;
					x1 = 1;
					x2 = a[i];
				}
				else
				{
					x1 = x2 = 0;
					y1 = 1;
					y2 = a[i];
				}
			}
			else
			{
				x1 = x2 = sum0[j - 1] - sum0[i];
				y1 = y2 = sum1[j - 1] - sum1[i];
				if(i & 1)
				{
					x2 += a[i];
				}
				else
				{
					y2 += a[i];
				}
				if(j & 1)
				{
					x2 += a[j];
				}
				else
				{
					y2 += a[j];
				}
			}
			addrect(x1, y1, x2, y2);
			t[++top] = y1;
			t[++top] = y2;
		}
	for(int i = 1; i <= m; i++)
	{
		int x, y; // x + y >= 1
		scanf("%d%d", &x, &y);
		addpoint(x, y, i);
		t[++top] = y;
	}
	sort(b + 1, b + cnt + 1, cmp);
	sort(t + 1, t + top + 1);
	top = unique(t + 1, t + top + 1) - t - 1;
	for(int i = 1; i <= cnt; i++)
	{
		b[i].y1 = lower_bound(t + 1, t + top + 1, b[i].y1) - t;
		if(b[i].type == 1 || b[i].type == 3)
		{
			b[i].y2 = lower_bound(t + 1, t + top + 1, b[i].y2) - t;
		}
	}
}
void solve()
{
	for(int i = 1; i <= cnt; i++)
	{
		if(b[i].type == 1)
		{
			//printf("add %d %d\n", b[i].y1, b[i].y2);
			add(b[i].y2, 1);
			add(b[i].y1 - 1, -1);
		}
		else if(b[i].type == 2)
		{
			//printf("query %d %d\n", b[i].y1, b[i].id);
			ans[b[i].id] = query(b[i].y1) ? 1 : 0;
		}
		else
		{
			//printf("delete %d %d\n", b[i].y1, b[i].y2);
			add(b[i].y2, -1);
			add(b[i].y1 - 1, 1);
		}
	}
	for(int i = 1; i <= m; i++) printf("%d", ans[i]);
	puts("");
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
