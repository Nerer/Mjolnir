#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <iostream>
using namespace std;
int n, k, Case;
char s[1111];
int cnt[1111];
void solve()
{
	memset(cnt, 0, sizeof cnt);
	int ans = 0;
	scanf("%d%d", &n, &k);
	scanf("%s", s + 1);
	for(int i = 1; i <= k + 1; i++)
	{
		ans += (cnt[s[i]] > 0);
		cnt[s[i]]++;
	}
	for(int i = k + 2; i <= n; i++)
	{
		cnt[s[i - k - 1]]--;
		ans += (cnt[s[i]] > 0);
		cnt[s[i]]++;
	}
	printf("Case %d: %d\n", ++Case, ans);
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
