#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

LL l, r;
int k;
LL dp[19][10005][6];
int ten[10];

int bit[20], len;

LL dfs(int pos, int state, int valid, bool limit, bool zero)
{
	if(pos == 0) return 1;
	if(!limit && !zero && ~dp[pos][state][valid]) return dp[pos][state][valid];

	int upp = limit ? bit[pos] : 9;
	LL res = 0;

	for(int i = 0; i <= upp; i++)
	{
		bool flag = 1;
		for(int j = 1; j <= valid; j++)
		{
			if(state / ten[j - 1] % 10 == i)
			{
				flag = 0;
				break;
			}
		}
		if(!flag) continue;

		int nstate = state;
		if(!zero || i != 0) nstate = state * 10 % ten[k] + i;
		
		res += dfs(pos - 1, nstate, min(k, valid + (!zero || i != 0)), limit && i == upp, zero && i == 0);
	}

	if(!limit && !zero) dp[pos][state][valid] = res;
	return res;
}
LL cal(LL n)
{
	len = 0;
	for(;n;n/=10) bit[++len] = n % 10;

	return dfs(len, 0, 0, 1, 1);
}
void solve()
{
	memset(dp, -1, sizeof dp);

	cout << cal(r) - cal(l - 1) << endl;

	//cout << cal(r) << endl;
}
int main()
{
	ten[0] = 1;
	for(int i = 1; i <= 8; i++) ten[i] = ten[i - 1] * 10;
	while(cin >> l >> r >> k)
	{
		k--;
		solve();
	}
	return 0;
}
