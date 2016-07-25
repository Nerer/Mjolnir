#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL l, r;
int bit[20], len;
LL _dp[20][3000][20];
#define dp(i, j, k) _dp[i][(j) + 1500][k]
LL dfs(int pos, int sub, const int mid, bool limit)
{
	if(pos == 0)
	{
		return sub == 0;
	}
	if(!limit && ~dp(pos, sub, mid)) return dp(pos, sub, mid);
	LL res = 0;
	int high = limit ? bit[pos] : 9;
	for(int i = 0 ; i <= high; i++)
	{
		int nsub = sub;
		if(pos < mid)
		{
			nsub += i * abs(pos - mid);
		}
		else if(pos > mid)
		{
			nsub -= i * abs(pos - mid);
		}
		res += dfs(pos - 1, nsub, mid, limit && i == high);
	}
	if(!limit) dp(pos, sub, mid) = res;
	return res;
}
LL cal(LL n)
{
	if(n == 0) return 1;
	if(n == -1) return 0;
	len = 0;
	for(LL t = n; t; t /= 10) bit[++len] = t % 10;
	LL res = 0;
	for(int i = 1; i <= len; i++)
	{
		res += dfs(len, 0, i, 1);
		if(i > 1) res--;
	}
	return res;
}
void solve()
{
	cin >> l >> r;
	cout << cal(r) - cal(l - 1) << endl;
}
int main()
{
	memset(_dp, -1, sizeof _dp);
	int t;
	cin >> t;
	while(t--)
	{
		solve();
	}
	return 0;
}
