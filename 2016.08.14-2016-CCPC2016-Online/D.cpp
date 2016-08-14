#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

int n, a[100];
LL sum;


void solve()
{
	LL ans = 0;
	for(int S = 0; S < (1 << n); S++)
	{
		LL s = 0;
		for(int i = 1; i <= n; i++) if(S >> i - 1 & 1)
		{
			s += a[i];
		}

		LL tmp = 0;
		if(s <= sum - s)
		{
			tmp = 2 * s;
		}
		else
		{
			tmp = (sum - s) * 2 + 1;
		}
		tmp = min(tmp, sum / 2);

		ans = max(ans, tmp);
	}
	cout << ans << endl;
}
int main()
{
	int t;
	cin >> t;
	for(int i = 1; i <= t; i++)
	{
		sum = 0;
		printf("Case #%d: ", i);
		cin >> n;
		for(int j = 1; j <= n; j++) cin >> a[i], sum += a[i];

		solve();
	}
}
