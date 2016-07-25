#include <bits/stdc++.h>
using namespace std;
int m, n;
int a[1111], b[1111];
int ans[1111];
void solve()
{
	cin >> m >> n;
	for(int i = 1; i <= m; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	sort(a + 1, a + m + 1);
	for(int i = 1; i <= n; i++)
	{
		int best = 0x3f3f3f3f;
		for(int j = 1; j <= m; j++)
		{
			if(__builtin_popcount(b[i]^a[j]) < best)
			{
				best = __builtin_popcount(b[i]^a[j]);
				ans[i] = a[j];
			}
		}
	}
	for(int i = 1; i <= n; i++) printf("%d\n", ans[i]);
}
int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		solve();
	}
	return 0;
}
