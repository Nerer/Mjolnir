#include <bits/stdc++.h>
using namespace std;
#define ls o << 1, L, mid
#define rs o << 1 | 1, mid + 1, R
const int N = 300010;
int n, m;
struct edge{int v,next;}e[N * 2];
int head[N], k;
int in[N], out[N], dfs_clock;
int _in[N];
int fa[N][20], dep[N];
struct data
{
	int l, r, x;
}a;
vector<data>Add[N], Del[N];

int add[N * 4], mx[N * 4];

int sum[N];

void adde(int u, int v)
{
	e[k].v = v;
	e[k].next = head[u];
	head[u] = k++;
}
void dfs(int u)
{
	in[u] = ++dfs_clock;
	for(int i = head[u]; ~i; i = e[i].next)
	{
		int v = e[i].v;
		if(v == fa[u][0]) continue;
		fa[v][0] = u; for(int i = 1; i <= 19; i++) fa[v][i] = fa[fa[v][i - 1]][i - 1];
		dep[v] = dep[u] + 1;
		dfs(v);
	}
	out[u] = dfs_clock;
}
int getlca(int x, int y)
{
	if(dep[x] < dep[y]) swap(x, y);
	int d = dep[x] - dep[y];
	for(int i = 0; i < 20; i++) if(d >> i & 1) x = fa[x][i];
	if(x == y) return x;
	for(int i = 19; i >= 0; i--) if(fa[x][i] ^ fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}
int getinc(int x, int d)
{
	for(int i = 0; i <= 19; i++) if(d >> i & 1) x = fa[x][i];
	return x;
}
void build(int o, int L, int R)
{
	add[o] = mx[o] = 0;
	if(L == R) return;
	int mid = L + R >> 1;
	build(ls);
	build(rs);
}
void down(int o)
{
	if(add[o])
	{
		add[o << 1] += add[o];
		add[o << 1 | 1] += add[o];
		mx[o << 1] += add[o];
		mx[o << 1 | 1] += add[o];
		add[o] = 0;
	}
}
void up(int o)
{
	mx[o] = max(mx[o << 1], mx[o << 1 | 1]);
}
void sgt_add(int l, int r, int x, int o, int L, int R)
{
	if(l <= L && R <= r)
	{
		mx[o] += x;
		add[o] += x;
		return;
	}
	down(o);
	int mid = L + R >> 1;
	if(r <= mid) sgt_add(l, r, x, ls);
	else if(l > mid) sgt_add(l, r, x, rs);
	else sgt_add(l, mid, x, ls), sgt_add(mid + 1, r, x, rs);
	up(o);
}
int query(int l, int r, int o, int L, int R)
{
	down(o);
	up(o);
	return mx[o];
}
void input()
{
	dfs_clock = 0;
	for(int i = 1; i <= n; i++) fa[i][0] = dep[i] = sum[i] = 0;

	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		Add[i].clear();
		Del[i].clear();
	}

	for(int i = 1; i <= n; i++) head[i] = -1;
	k = 0;

	for(int i = 2; i <= n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		adde(u, v);
		adde(v, u);
	}
}
void solve()
{
	build(1, 1, n);
	dfs(1);

	for(int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		
		int lca = getlca(u, v);
		if(u == v)
		{
			sum[u] += w;
		}
		else if(lca == u)
		{
			int tmp = getinc(v, dep[v] - dep[u] - 1);
			data x1, x2, y1, y2;
			x1.l = y1.l = 1;
			x1.r = y1.r = in[tmp] - 1;
			x1.x = w;
			y1.x = -w;

			x2.l = y2.l = out[tmp] + 1;
			x2.r = y2.r = n;
			x2.x = w;
			y2.x = -w;
			
			if(x1.l <= x1.r)
			{
				Add[in[v]].push_back(x1);
				Del[out[v]].push_back(y1);
			}
			if(x2.l <= x2.r)
			{
				Add[in[v]].push_back(x2);
				Del[out[v]].push_back(y2);
			}
		}
		else if(lca == v)
		{
			int tmp = getinc(u, dep[u] - dep[v] - 1);
			data x, y;
			x.l = y.l = in[u];
			x.r = y.r = out[u];
			x.x = w;
			y.x = -w;

			if(1 <= in[tmp] - 1)
			{
				Add[1].push_back(x);
				Del[in[tmp] - 1].push_back(y);
			}
			if(out[tmp] + 1 <= n)
			{
				Add[out[tmp] + 1].push_back(x);
				Del[n].push_back(y);
			}
		}
		else
		{
			data x, y;
			x.l = in[u];
			x.r = out[u];
			x.x = w;
			y.l = in[u];
			y.r = out[u];
			y.x = -w;
			Add[in[v]].push_back(x);
			Del[out[v]].push_back(y);
		}
	}

	for(int u = 1; u <= n; u++) if(sum[u])
	{
		for(int i = head[u]; ~i; i = e[i].next)
		{
			int v = e[i].v;
			if(v == fa[u][0])
			{
				data x, y;
				x.l = y.l = in[u];
				x.r = y.r = out[u];
				x.x = sum[u];
				y.x = -sum[u];
				
				if(1 <= in[u] - 1)
				{
					Add[1].push_back(x);
					Del[in[u] - 1].push_back(y);
				}
				if(out[u] + 1 <= n)
				{
					Add[out[u] + 1].push_back(x);
					Del[n].push_back(y);
				}
			}
			else
			{
				data x1, y1, x2, y2;
				x1.l = y1.l = 1;
				x1.r = y1.r = in[v] - 1;
				x2.l = y2.l = out[v] + 1;
				x2.r = y2.r = n;
				x1.x = x2.x = sum[u];
				y1.x = y2.x = -sum[u];
				if(x1.l <= x1.r)
				{
					Add[in[v]].push_back(x1);
					Del[out[v]].push_back(y1);
				}
				if(x2.l <= x2.r)
				{
					Add[in[v]].push_back(x2);
					Del[out[v]].push_back(y2);
				}
			}
		}
		data x, y;
		x.l = y.l = 1;
		x.r = y.r = n;
		x.x = sum[u];
		y.x = -sum[u];
		Add[in[u]].push_back(x);
		Del[in[u]].push_back(y);
	}
	for(int i = 1; i <= n; i++) _in[in[i]] = i;

	int ans = -0x3f3f3f3f;
	for(int i = 1; i <= n; i++)
	{
		int u = i;
		for(int j = 0; j < (int)Add[u].size(); j++)
		{
			int l = Add[u][j].l, r = Add[u][j].r, x = Add[u][j].x;
			sgt_add(l, r, x, 1, 1, n);
			//printf("add %d %d %d\n",l, r, x);
		}
		ans = max(ans, query(1, n, 1, 1, n));
		//printf("query %d\n",u);
		for(int j = 0; j < (int)Del[u].size(); j++)
		{
			int l = Del[u][j].l, r = Del[u][j].r, x = Del[u][j].x;
			sgt_add(l, r, x, 1, 1, n);
			//printf("del %d %d %d\n",l, r, x);
		}
	}
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
