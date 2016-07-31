#include <bits/stdc++.h>
using namespace std;
int n, a[1111];
void solve()
{
	if(n == 1)
	{
		printf("%.10f\n", (double)a[1]);
		return;
	}

	double ans = 0;
	for(int i = 2; i <= n - 1; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			ans += (double) (j - 1) * (j - 2) / (n - 1) / (n - 2) * a[i];
		}
	}
	for(int i = 1; i <= n; i++)
	{
		ans += (double) (i - 1) / (n - 1) * (a[1] + a[n]);
	}
	ans /= n;
	printf("%.6f\n", ans);
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		if(n == 0) break;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		solve();
	}
}
