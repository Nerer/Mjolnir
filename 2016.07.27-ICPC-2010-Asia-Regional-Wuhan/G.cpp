#include <bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f;
int v1, v2, n, Case;
int dp[2][510][60][2];
int p[333], h[333], s[333];
void input()
{
	for(int i = 1; i <= n; i++) scanf("%d%d%d", &p[i], &h[i], &s[i]);
}
void solve()
{
	for(int j = 0; j <= v1; j++)
		for(int k = 0; k <= v2; k++)
		{
			dp[0][j][k][0] = dp[0][j][k][1] = 0xafafafaf;
		}
	dp[0][0][0][0] = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 0; j <= v1; j++)
		{
			for(int k = 0; k <= v2; k++)
			{
				dp[i&1][j][k][0] = dp[i&1][j][k][1] = 0xafafafaf;
				if(!s[i])
				{
					dp[i&1][j][k][0] = dp[i - 1&1][j][k][0];
					dp[i&1][j][k][1] = dp[i - 1&1][j][k][1];
				}
				if(j - p[i] >= 0) dp[i&1][j][k][0] = max(dp[i&1][j][k][0], dp[i - 1&1][j - p[i]][k][0] + h[i]);
				if(k - p[i] >= 0) dp[i&1][j][k][0] = max(dp[i&1][j][k][0], dp[i - 1&1][j][k - p[i]][0] + h[i]);
				if(j - p[i] >= 0) dp[i&1][j][k][1] = max(dp[i&1][j][k][1], dp[i - 1&1][j - p[i]][k][1] + h[i]);
				if(k - p[i] >= 0) dp[i&1][j][k][1] = max(dp[i&1][j][k][1], dp[i - 1&1][j][k - p[i]][1] + h[i]);
				dp[i&1][j][k][1] = max(dp[i&1][j][k][1], dp[i - 1&1][j][k][0] + h[i]);
			}
		}
	}
	int ans = 0xafafafaf;
	for(int j = 0; j <= v1; j++)
		for(int k = 0; k <= v2; k++)
		{
			ans = max(ans, dp[n&1][j][k][0]);
			ans = max(ans, dp[n&1][j][k][1]);
		}
	printf("Case %d: %d\n\n", ++Case, ans < 0 ? -1 : ans);
}
int main()
{
	while(~scanf("%d%d%d", &v1, &v2, &n))
	{
		if(v1 == 0 && v2 == 0 && n == 0) break;
		input();
		solve();
	}
	return 0;
}
