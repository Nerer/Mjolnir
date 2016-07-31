#include <bits/stdc++.h>

using namespace std;

int n, m, type;
int dp1[1010][1010], dp3[1010][1010], dp4[1010][1010];
int s1[1010][1010], s2[1010][1010], s3[2020][2020];

int dx[] = {-1, -2};
int dy[] = {-2, -1};

void init()
{
	dp1[1][1] = 2;
	for(int i = 1; i <= 1000; i++)
		for(int j = (i == 1 ? 2 : 1); j <= 1000; j++)
		{
			bool flag = 0;
			if(i > 1 && dp1[i - 1][j] == 2) flag = 1;
			if(j > 1 && dp1[i][j - 1] == 2) flag = 1;
			if(i > 1 && j > 1 && dp1[i - 1][j - 1] == 2) flag = 1;
			if(flag) dp1[i][j] = 1;
			else dp1[i][j] = 2;
		}

	dp4[1][1] = 2;
	s1[1][1] = s2[1][1] = s3[1 - 1 + 1000][1] = 1;
	for(int i = 1; i <= 1000; i++)
		for(int j = (i == 1 ? 2 : 1); j <= 1000; j++)
		{
			bool flag = 0;
			if(j > 1 && s1[i][j - 1]) flag = 1;
			if(i > 1 && s2[i - 1][j]) flag = 1;
			if(i > 1 && j > 1 && s3[i - j + 1000][i - 1]) flag = 1;
			dp4[i][j] = flag ? 1 : 2;
			if(dp4[i][j] == 1)
			{
				s1[i][j] = s1[i][j - 1];
				s2[i][j] = s2[i - 1][j];
				s3[i - j + 1000][i] = s3[i - j + 1000][i - 1];
			}
			else
			{
				s1[i][j] = s2[i][j] = s3[i - j + 1000][i] = 1;
			}
		}
/*
	for(int i = 1; i <= 30; i++)
	{
		for(int j = 1; j <= 30; j++)
		{
			printf("%d%c", dp4[i][j], " \n"[j == 30]);
		}
	}*/
}

int dfs(int x, int y)
{
	if(dp3[x][y] != 0) return dp3[x][y];
	if(x == 1 && y == 1) return dp3[x][y] = 2;
	if(x == 1 || y == 1) return dp3[x][y] = 3;
	if(x == 2 && y == 2) return dp3[x][y] = 3;

	bool flag1 = 0, flag2 = 0;
	for(int k = 0; k < 2; k++)
	{
		int nx = x + dx[k], ny = y + dy[k];
		if(nx < 1 || ny < 1) continue;
		int ret = dfs(nx, ny);
		if(ret == 2) flag1 = 1;
		else if(ret == 3) flag2 = 1;
	}
	if(flag1) return dp3[x][y] = 1;
	if(flag2) return dp3[x][y] = 3;
	return dp3[x][y] = 2;
}

void solve()
{
	cin >> type >> n >> m;
	if(type == 1)
	{
		if(dp1[n][m] == 1)
		{
			puts("B");
		}
		else
		{
			puts("G");
		}
	}
	else if(type == 2)
	{
		if(n != m)
		{
			puts("B");
		}
		else
		{
			puts("G");
		}
	}
	else if(type == 3)
	{
		int ret = dfs(n, m);
		if(ret == 1)
		{
			puts("B");
		}
		else if(ret == 2)
		{
			puts("G");
		}
		else
		{
			puts("D");
		}
	}
	else
	{
		if(dp4[n][m] == 1)
		{
			puts("B");
		}
		else
		{
			puts("G");
		}
	}
}

int main()
{
	int t;
	cin >> t;
	init();
	while(t--)
	{
		solve();
	}
	return 0;
}
