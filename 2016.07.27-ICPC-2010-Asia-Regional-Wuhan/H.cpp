#include <bits/stdc++.h>
using namespace std;
int n, k, m;
int a[111];
const int inf = 0x3f3f3f3f;
typedef pair<int, int> pii;
pii b[111];
int _dp[2][105][10][1<<8];
#define dp(i, j, k, s) _dp[(i) & 1][j][k][s]
inline void MIN(int &a, int b)
{
	if(a > b) a = b;
}
void input()
{
	m = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		a[i] -= 25;
	}
	for(int i = 1; i <= n; i++)
	{
		int j = i;
		while(j <= n && a[j] == a[i]) j++;
		j--;
		b[++m] = pii(a[i], j - i + 1);
		i = j;
	}
}

int calc(int s) {
	vector<int> col;
	for (int i = 1; i <= m; i++) {
		col.push_back(b[i].first);
	}	
	sort(col.begin(), col.end());
	col.erase(unique(col.begin(), col.end()), col.end());
	int ret = 0;
	for (int i = 0; i < (int)col.size(); i++) {
		if ((s >> col[i] & 1) == 0) {
			ret++;
		}
	}
	return ret;
}
void solve()
{
	for(int i = 0; i <= 1; i++)
		for(int j = 0; j <= k; j++)
			for(int l = 0; l <= 7; l++)
				for(int p = 0; p < (1 << 8); p++)
					dp(i, j, l, p) = inf;
	for(int i = 0; i <= 7; i++) dp(0, 0, i, 0) = 1;
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j <= k; j++)
			for(int l = 0; l <= 7; l++)
				for(int s = 0; s < (1 << 8); s++)
					dp(i + 1, j, l, s) = inf;
		for(int j = 0; j <= k; j++)
		{
			for(int l = 0; l <= 7; l++)
			{
				for(int s = 0; s < (1 << 8); s++)
				{
					if (dp(i, j, l, s) > inf / 2) {
						continue;
					}
					if(b[i + 1].first == l)
					{
						MIN(dp(i + 1, j, l, s | (1 << b[i + 1].first)), dp(i, j, l, s));
					}
					else
					{
						if(s >> b[i + 1].first & 1)
						{
							MIN(dp(i + 1, j, b[i + 1].first, s), dp(i, j, l, s) + 1);
							if(j + b[i + 1].second <= k) MIN(dp(i + 1, j + b[i + 1].second, l, s), dp(i, j, l, s));
						}
						else
						{
							MIN(dp(i + 1, j, b[i + 1].first, s | (1 << b[i + 1].first)), dp(i, j, l, s) + 1);
							if(j + b[i + 1].second <= k) MIN(dp(i + 1, j + b[i + 1].second, l, s), dp(i, j, l, s));
						}
					}
				}
			}
		}
		/*for(int j = 0; j <= k; j++)
			for(int l = 0; l <= 7; l++)
				for(int s = 0; s < (1 << 2); s++)
				{
					printf("dp(%d, %d, %d, %d) = %d\n", i + 1, j, l, s, dp(i + 1, j, l, s));
				}*/
	}
	int ans = 0x3f3f3f3f;
	for(int s = 0; s < (1 << 8); s++)
	{
	int tmp = calc(s);
	for(int j = 0; j <= k; j++)
	{
		for(int l = 0; l <= 7; l++)
		{
				MIN(ans, dp(m, j, l, s) + tmp);
		}
	}
	}
	cout << ans << endl;
}
int main()
{
	while(scanf("%d%d", &n, &k) == 2)
	{
		static int testCount = 0;
		if(n == 0 && k == 0) break;;
		input();
		printf("Case %d: ", ++testCount);
		solve();
		puts("");
	}
	return 0;
}
