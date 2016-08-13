#include <bits/stdc++.h>

using namespace std;
const int N = 1e6 + 10;

int n;
long long a[N];

int main()
{
	while(~scanf("%d", &n))
	{
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);

		long long cur = 0;
		int ans = 0;
		for(int i = n; i >= 1; i--)
		{
			cur += a[i];
			if(cur >= 0)
			{
				cur = 0;
				ans++;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
