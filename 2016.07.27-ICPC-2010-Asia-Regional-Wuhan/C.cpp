#include <bits/stdc++.h>
using namespace std;
int n, d;
int main()
{
	int Case = 0;
	while(scanf("%d%d", &n, &d) == 2)
	{
		if(n == 0 && d == 0) break;
		double ans = 0;
		int p, l, v;
		int cur = 0;
		for(int i = 1; i <= n; i++)
		{
			cin >> p >> l >> v;
			ans += p - cur;
			ans += 2.0 * l / v;
			cur = p + l;
		}
		ans += d - cur;
		printf("Case %d: %.3f\n\n", ++Case, ans);
	}
	return 0;
}
