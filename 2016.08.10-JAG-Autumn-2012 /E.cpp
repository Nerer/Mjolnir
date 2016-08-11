#include <bits/stdc++.h>

using namespace std;
const int N = 270 * 2;

int n, m;
char A[55][55];
char alpha[N];
int id[55][55];
int cnt;
vector<int>from[N], to[N];
int dp[N][N];

int dx[] = {1, 0};
int dy[] = {0, 1};
int vis[55][55], clk;
bool is_alpha(char c)
{
	return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}
inline void update(int &a, int b)
{
	if(a < b) a = b;
}
void bfs(int x, int y, int idd)
{
	queue<pair<int, int> >q;
	q.push(make_pair(x, y));

	clk++;

	vis[x][y] = clk;
	while(!q.empty())
	{
		pair<int, int> u = q.front(); q.pop();
		int x = u.first, y = u.second;
		for(int k = 0; k < 2; k++)
		{
			int nx = x + dx[k], ny = y + dy[k];
			if(nx > n || ny > m) continue;
			if(A[nx][ny] == '#') continue;
			if(id[nx][ny])
			{
				to[idd].push_back(id[nx][ny]);
				from[id[nx][ny]].push_back(idd);
			}
			else if(vis[nx][ny] != clk)
			{
				vis[nx][ny] = clk;
				q.push(make_pair(nx, ny));
			}
		}
	}
}
void solve()
{
	for(int i = 1; i <= n; i++) scanf("%s", A[i] + 1);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
		{
			if(is_alpha(A[i][j]))
			{
				id[i][j] = ++cnt;
				alpha[cnt] = A[i][j];
			}
			else if(i == 1 && j == 1 || i == n && j == m)
			{
				id[i][j] = ++cnt;
				alpha[cnt] = '$';
			}
		}

	for(int i = 1; i <= cnt; i++)
	{
		from[i].clear();
		to[i].clear();
		for(int j = 1; j <= cnt; j++)
		{
			dp[i][j] = -1;
		}
		dp[i][i] = 0;
	}

	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(id[i][j])
			{
				bfs(i, j, id[i][j]);
			}
		}
	}

	for(int len = 2; len <= cnt; len++)
	{
		for(int l = 1; l <= cnt; l++)
		{
			int r = l + len - 1;
			if(r > cnt) break;

			char cl = alpha[l], cr = alpha[r];

			for(int i = 0; i < (int) to[l].size(); i++)
			{
				if(to[l][i] == r)
				{
					update(dp[l][r], 0);
				}
			}

			if(cl >= 'a' && cl <= 'z' && cr >= 'A' && cr <= 'Z' && (int) cl + 'A' == (int) cr + 'a')
			{
				for(int i = 0; i < (int) to[l].size(); i++)
				{
					if(to[l][i] == r)
					{
						update(dp[l][r], 1);
					}
					for(int j = 0; j < (int) from[r].size(); j++)
					{
						if(dp[to[l][i]][from[r][j]] < 0) continue;
						update(dp[l][r], dp[to[l][i]][from[r][j]] + 1);
					}
				}
			}
			for(int k = l + 1; k <= r - 1; k++)
			{
				if(dp[l][k] < 0 || dp[k][r] < 0) continue;
				update(dp[l][r], dp[l][k] + dp[k][r]);
			}
		}
	}

	if(dp[1][cnt] < 0) puts("-1");
	else printf("%d\n", dp[1][cnt]);
}
int main()
{
	while(~scanf("%d%d", &n, &m))
	{
		if(n == 0 && m == 0) break;

		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				id[i][j] = 0;
		cnt = 0;
		solve();
	}
	return 0;
}
