#include <bits/stdc++.h>

using namespace std;

int n, s, t;
int q[111], w[111][111], dis[111][111];

long double m[111][111];

void gauss()
{
	for(int i = 1; i <= n; i++)
	{
		int r = i;
		for(int j = i + 1; j <= n; j++)
		{
			if(fabs(m[j][i]) > fabs(m[r][i])) r = j;
		}
		if(r != i)
		{
			for(int j = 1; j <= n + 1; j++) swap(m[r][j], m[i][j]);
		}

		for(int k = i + 1; k <= n; k++)
		{
			long double f = m[k][i] / m[i][i];
			for(int j = i; j <= n + 1; j++)
			{
				m[k][j] -= f * m[i][j];
			}
		}
	}
	for(int i = n; i >= 1; i--)
	{
		for(int j = i + 1; j <= n; j++)
		{
			m[i][n + 1] -= m[j][n + 1] * m[i][j];
		}
		m[i][n + 1] /= m[i][i];
	}
}

void solve()
{
	memset(dis, 0x3f, sizeof dis);

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) if(w[i][j])
			dis[i][j] = w[i][j];

	for(int i = 1; i <= n; i++) dis[i][i] = 0;
	for(int k = 1; k <= n; k++)
		for(int i =1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);

	if(dis[s][t] > 0x2f2f2f2f)
	{
		puts("impossible");
		return;
	}

	for(int i = 1; i <= n; i++)
	{
		if(i == t)
		{
			for(int j = 1; j <= n + 1; j++) if(i ^ j) m[i][j] = 0;
			m[i][i] = 1;
		}
		else if(q[i] == 0)
		{
			int outd = 0, sum = 0;
			for(int j = 1; j <= n; j++) if(w[i][j])
			{
				outd++;
				m[i][j] = 1;
				sum += w[i][j];
			}
			m[i][i] -= outd;
			m[i][n + 1] = -sum;
		}
		else
		{
			int outd = 0, sum = 0;
			for(int j = 1; j <= n; j++) if(w[i][j]) if(dis[j][t] + w[i][j] == dis[i][t])
			{
				outd++;
				m[i][j] = 1;
				sum += w[i][j];
			}
			m[i][i] -= outd;
			m[i][n + 1] = -sum;
		}
	}

	/*for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n + 1; j++)
			printf("%.5f%c", (double)m[i][j], " \n"[j == n + 1]);*/
	gauss();

	printf("%.10f\n", (double)m[s][n + 1]);
}
int main()
{
	while(~scanf("%d%d%d", &n, &s, &t))
	{
		if(n == 0 && s == 0 && t == 0) break;

		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n + 1; j++)
				m[i][j] = 0;

		for(int i = 1; i <= n; i++) scanf("%d", &q[i]);
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				scanf("%d", &w[i][j]);

		solve();
	}
	return 0;
}
