#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

int n;
LL dis(LL x, LL y)
{
	return x * x + y * y;
}
void solve()
{
	LL ans = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int tx, ty;
		scanf("%d%d", &tx, &ty);

		LL x = tx, y = ty;

		for(int k = 20; k <= 200; k += 20)
		{
			if(dis(x, y) <= k * k)
			{
				ans += 11 - k / 20;
				break;
			}
		}
	}
	cout << ans << endl;
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
