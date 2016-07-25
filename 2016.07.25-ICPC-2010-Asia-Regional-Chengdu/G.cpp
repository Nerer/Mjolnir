#include <bits/stdc++.h>
using namespace std;
const int N = 410;
const int M = 10010;
int n, m;
int a[M], b[M], c[M];
struct edge
{
	int v, next;
}e[M * 4];
int head[N], k;
int dfn[N], low[N], dfs_clock;
int belong[N], scc;
stack<int>S;
void adde(int u, int v)
{
	e[k].v = v;
	e[k].next = head[u];
	head[u] = k++;
}
void dfs(int u)
{
	dfn[u] = low[u] = ++dfs_clock;
	S.push(u);
	for(int i = head[u]; ~i; i = e[i].next)
	{
		int v = e[i].v;
		if(!dfn[v])
		{
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
		else if(!belong[v])
		{
			low[u] = min(low[u], dfn[v]);
		}
	}
	if(low[u] == dfn[u])
	{
		scc++;
		for(;;)
		{
			int x = S.top(); S.pop();
			belong[x] = scc;
			if(x == u) break;
		}
	}
}
bool check(int mid)
{
	dfs_clock = 0;
	for(int i = 1; i <= 2 * n; i++)
	{
		head[i] = -1;
		belong[i] = dfn[i] = low[i] = 0;
	}
	k = 0;
	scc = 0;
	dfs_clock = 0;
	while(!S.empty()) S.pop();

	for(int i = 1; i <= mid; i++)
	{
		int x0 = 2 * a[i] - 1;
		int x1 = 2 * a[i];
		int y0 = 2 * b[i] - 1;
		int y1 = 2 * b[i];
		if(c[i] == 0)
		{
			adde(x0, y1);
			adde(y0, x1);
		}
		else if(c[i] == 1)
		{
			adde(x0, y0);
			adde(y0, x0);
			adde(y1, x1);
			adde(x1, y1);
		}
		else
		{
			adde(y1, x0);
			adde(x1, y0);
		}
	}
	for(int i = 1; i <= 2 * n; i++) if(!dfn[i]) dfs(i);

	for(int i = 1; i <= 2 * n; i += 2)
	{
		if(belong[i] == belong[i + 1]) return 0;
	}
	return 1;
}
void input()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &a[i], &b[i], &c[i]);
		a[i]++;
		b[i]++;
	}
}
void solve()
{
	int l = 0, r = m, mid;
	while(l < r)
	{
		mid = l + r + 1>> 1;
		if(check(mid)) l = mid;
		else r = mid - 1;
	}
	printf("%d\n", l);
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
