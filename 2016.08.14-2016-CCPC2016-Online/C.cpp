#include <bits/stdc++.h>

using namespace std;
const int N = 100010;

int n, a[N];
struct edge
{
	int v, w, next;
}e[N * 2];
int head[N], k;

int fa[N];
int f[N], g[N], ff[N], gg[N], ans[N];

vector <int> f1[N], f2[N];
vector <int> g1[N], g2[N];

int dis[N];

void adde(int u, int v, int w)
{
	e[k].v = v;
	e[k].w = w;
	e[k].next = head[u];
	head[u] = k++;
}
inline int fix(int x)
{
	if(x < 0) return 0;
	return x;
}
void dfs1(int u)
{
	for(int i = head[u]; ~i; i = e[i].next)
	{
		int v = e[i].v;
		if(v == fa[u]) continue;
		fa[v] = u;
		dfs1(v);
		dis[v] = e[i].w;
	}

	vector <int> son;
	for(int i = head[u]; ~i; i = e[i].next)
	{
		int v = e[i].v;
		if(v == fa[u]) continue;
		son.push_back(v);
	}

	f1[u].resize(son.size());
	f2[u].resize(son.size());
	g1[u].resize(son.size());
	g2[u].resize(son.size());

	int mx1 = 0, mx2 = 0;

	f[u] = a[u];
	g[u] = a[u];

	for(int i = 0; i < (int) son.size(); i++)
	{
		int v = son[i];

		if(f[v] - 2 * dis[v] >= 0)
		{
			f[u] += f[v] - 2 * dis[v];
			mx1 = max(mx1, (g[v] - dis[v]) - (f[v] - 2 * dis[v]));
		}
		else
		{
			mx2 = max(mx2, g[v] - dis[v]);
		}

		g[u] = max(f[u] + mx1, f[u] + mx2);
		f1[u][i] = f[u];
		g1[u][i] = g[u];
	}

	mx1 = mx2 = 0;

	f[u] = a[u];
	g[u] = a[u];

	for(int i = (int) son.size() - 1; i >= 0; i--)
	{
		int v = son[i];

		if(f[v] - 2 * dis[v] >= 0)
		{
			f[u] += f[v] - 2 * dis[v];
			mx1 = max(mx1, (g[v] - dis[v]) - (f[v] - 2 * dis[v]));
		}
		else
		{
			mx2 = max(mx2, g[v] - dis[v]);
		}

		g[u] = max(f[u] + mx1, f[u] + mx2);
		f2[u][i] = f[u];
		g2[u][i] = g[u];
	}
}
void dfs2(int u)
{
	vector <int> son;

	for(int i = head[u]; ~i; i = e[i].next)
	{
		int v = e[i].v;
		if(v == fa[u]) continue;
		son.push_back(v);
	}

	for(int i = 0; i < (int) son.size(); i++)
	{
		int v = son[i];

		ff[v] = ff[u] + f[u];
		if(f[v] - 2 * dis[v] >= 0) ff[v] -= f[v] - 2 * dis[v];
		ff[v] -= 2 * dis[v];
		if(ff[v] < 0) ff[v] = 0;

		gg[v] = (i == 0 ? 0 : fix(f1[u][i - 1] - a[u])) + ((i == (int) son.size() - 1) ? 0: fix(f2[u][i + 1] - a[u])) + a[u] + gg[u] - dis[v];

		gg[v] = max(gg[v], ff[u] + (i == 0 ? 0 : fix(f1[u][i - 1] - a[u])) + ((i == (int) son.size() - 1) ? 0 : fix(g2[u][i + 1] - a[u])) + a[u] - dis[v]);
		gg[v] = max(gg[v], ff[u] + (i == 0 ? 0 : fix(g1[u][i - 1] - a[u])) + ((i == (int) son.size() - 1) ? 0 : fix(f2[u][i + 1] - a[u])) + a[u] - dis[v]);
		if(gg[v] < 0) gg[v] = 0;
	}

	son.clear();
	
	for(int i = head[u]; ~i; i = e[i].next)
	{
		int v = e[i].v;
		if(v == fa[u]) continue;
		dfs2(v);
	}
}
void solve()
{
	dfs1(1);
	dfs2(1);

	for(int u = 1; u <= n; u++)
	{
		ans[u] = max(f[u] + gg[u], ff[u] + g[u]);
	}

	for(int i = 1; i <= n; i++)
	{
		printf("%d\n", ans[i]);
	}
}
int main()
{
	int t;
	cin >> t;
	for(int i = 1; i <= t; i++)
	{
		printf("Case #%d:\n", i);
		scanf("%d", &n);

		for(int j = 1; j <= n; j++) head[j] = -1;
		k = 0;
		for(int j = 1; j <= n; j++)
		{
			f1[j].clear();
			f2[j].clear();
			g1[j].clear();
			g2[j].clear();
			f[j] = g[j] = ff[j] = gg[j] = fa[j] = 0;
		}

		for(int j = 1; j <= n; j++) scanf("%d", &a[j]);
		for(int j = 2; j <= n; j++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			adde(u, v, w);
			adde(v, u, w);
		}
		solve();
	}
	return 0;
}
/*
Case #1: 
99
95 99 0 0
100
98 100 0 0
100
100 100 0 0
97
1 1 94 96
97
1 1 94 96

*/
