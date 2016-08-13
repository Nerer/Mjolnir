#include <bits/stdc++.h>

using namespace std;
const int N = 2000;

int k, w;
double dp[2020][2020];
int f[2020][2020];

inline void update(double &a, const double b)
{
	if(a > b) a = b;
}
int main()
{
	dp[0][1] = 0;


	for(int i = 1; i <= N; i++) dp[i][1] = (double) i / (i + 1) * dp[i - 1][1] + 1;

	for(int i = 1; i <= N; i++)
		for(int j = 2; j <= N; j++)
		{
			if(i > 10 && j > 10)
			{
				int k = f[i][10];
				dp[i][j] = (double) k / (i + 1) * dp[k - 1][j - 1] + (double) (i - k + 1) / (i + 1) * dp[i - k][j] + 1;
					continue;
			}

			dp[i][j] = (double) i / (i + 1) * dp[i - 1][j] + 1;
			f[i][j] = 1;
			
			for(int k = 2; k <= i; k++)
			{
				if((double) k / (i + 1) * dp[k - 1][j - 1] + (double) (i - k + 1) / (i + 1) * dp[i - k][j] + 1 < dp[i][j])
				{
					f[i][j] = k;
				}
				dp[i][j] = min(dp[i][j], (double) k / (i + 1) * dp[k - 1][j - 1] + (double) (i - k + 1) / (i + 1) * dp[i - k][j] + 1);
				
			}
		}


	while(~scanf("%d%d", &k, &w))
	{
		printf("%.6f\n", dp[k][w]);
	}
	return 0;
}
