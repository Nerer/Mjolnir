#include <bits/stdc++.h>

using namespace std;
#define ls o << 1, L, mid
#define rs o << 1 | 1, mid + 1, R
typedef pair<int, int> pii;

int n, q;
vector<int>G[100010];

pii mx[400010], lazy[400010];

int in[100010], out[100010], dfs_clock, dep[100010];

void dfs(int u)
{
	in[u] = ++dfs_clock;
	for(int i = 0; i < (int) G[u].size(); i++)
	{
		int v = G[u][i];
		dep[v] = dep[u] + 1;
		dfs(v);
	}
	out[u] = dfs_clock;
}
void build(int o, int L, int R)
{
	mx[o] = pii(0, 1);
	lazy[o] = pii(0, 1);
	if(L == R) return;
	int mid = L + R >> 1;
	build(ls);
	build(rs);
}
void down(int o)
{
	if(lazy[o].first)
	{
		mx[o << 1] = max(mx[o << 1], lazy[o]);
		mx[o << 1 | 1] = max(mx[o << 1 | 1], lazy[o]);
		lazy[o << 1] = max(lazy[o << 1], lazy[o]);
		lazy[o << 1 | 1] = max(lazy[o << 1 | 1], lazy[o]);
		lazy[o] = pii(0, 1);
	}
}
void up(int o)
{
	mx[o] = max(mx[o << 1], mx[o << 1 | 1]);
}
void modify(int l, int r, pii x, int o, int L, int R)
{
	if(l <= L && R <= r)
	{
		mx[o] = max(mx[o], x);
		lazy[o] = max(lazy[o], x);
		return;
	}
	down(o);
	int mid = L + R >> 1;
	if(r <= mid) modify(l, r, x, ls);
	else if(l > mid) modify(l, r, x, rs);
	else modify(l, mid, x, ls), modify(mid + 1, r, x, rs);
	up(o);
}
pii query(int pos, int o, int L, int R)
{
	if(L == R) return mx[o];
	down(o);
	int mid = L + R >> 1;
	if(pos <= mid) return query(pos, ls);
	else return query(pos, rs);
}
void input()
{
	dfs_clock = 0;
	for(int i = 1; i <= n; i++) G[i].clear(), dep[i] = 0;

	for(int u = 2; u <= n; u++)
	{
		int v;
		scanf("%d", &v);
		G[v].push_back(u);
	}
}
void solve()
{
	dfs(1);
	build(1, 1, n);
	long long ans = 0;
	while(q--)
	{
		char op[10];
		int x;
		scanf("%s%d", op, &x);
		if(op[0] == 'M')
		{
			modify(in[x], out[x], pii(dep[x], x), 1, 1, n);
		}
		else
		{
			ans += query(in[x], 1, 1, n).second;
		}
	}
	cout << ans << endl;
}
int main()
{
	while(~scanf("%d%d", &n, &q))
	{
		if(n == 0 && q == 0) break;
		input();
		solve();
	}
	return 0;
}
