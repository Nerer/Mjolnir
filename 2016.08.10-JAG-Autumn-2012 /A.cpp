#include <bits/stdc++.h>

using namespace std;

int n;
char s[505][15];
bool dis[28][28];

void solve()
{
	memset(dis, 0, sizeof dis);
	for(int i = 1; i < n; i++)
	{
		bool flag = 0;
		int m = min(strlen(s[i]), strlen(s[i + 1]));
		for(int j = 0; j < m; j++)
		{
			if(s[i][j] != s[i + 1][j])
			{
				flag = 1;
				dis[s[i][j] - 'a'][s[i + 1][j] - 'a'] = 1;
				break;
			}
		}
		if(flag == 0 && s[i][m] != '\0')
		{
			puts("no");
			return;
		}
	}

	for(int k = 0; k < 26; k++)
		for(int i = 0; i < 26; i++)
			for(int j = 0; j < 26; j++)
				dis[i][j] |= dis[i][k] & dis[k][j];

	bool flag = 0;
	for(int i = 0; i < 26; i++) if(dis[i][i] == 1) flag = 1;
	if(flag) puts("no");
	else puts("yes");
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		if(n == 0) break;
		for(int i = 1; i <= n; i++) cin >> s[i];
		solve();
	}
	return 0;
}


