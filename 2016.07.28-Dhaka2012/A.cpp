#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;
LL a[10], b[10];
LL ans[10];
void input()
{
	int n, p;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	for(int i = 1; i <= n; i++)
	{
		cin >> b[i];
	}
}
void solve()
{
	for(int i = 0; i < (1 << n); i++)
	{

	}
}
int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		input();
		solve();
	}
	return 0;
}
