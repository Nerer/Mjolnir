#include <bits/stdc++.h>

using namespace std;
const int N = 1010;
const int M = 10010;

int n, m;
struct edge
{
	int u, v, w;
	bool operator<(const edge &b) const
	{
		return w < b.w;
	}
}e[M];
int fa[N];
int w[N], cnt;

int find(int x){return x == fa[x] ? x : fa[x] = find(fa[x]);}
int main()
{
	while(~scanf("%d%d", &n, &m))
	{
		cnt = 0;
		if(n == 0 && m == 0) break;
		for(int i = 1; i <= m; i++)
		{
			scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
		}
		for(int i = 1; i <= n; i++) fa[i] = i;
		sort(e + 1, e + m + 1);
		int cnt = 0;
		for(int i = 1; i <= m; i++)
		{
			int x = find(e[i].u), y = find(e[i].v);
			if(x != y)
			{
				fa[x] = y;
				w[++cnt] = e[i].w;
			}
		}
		if(n - 1 & 1)
		{
			printf("%d\n", w[n + 1 >> 1]);
		}
		else
		{
			printf("%.5f\n", (double) (w[n / 2] + w[n / 2 + 1]) / 2.);
		}
	}
	return 0;
}
