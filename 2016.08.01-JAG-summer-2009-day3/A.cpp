#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
const int M = 256;
const double eps = 1e-10;

int n;
int l[300];
int r[300];
int cnt[260];

double cal(int s, int a, int c)
{
	memset(cnt, 0, sizeof cnt);
	r[0] = s;
	for(int i = 1; i <= n; i++) r[i] = (a * r[i - 1] + c) % M;

	for(int i = 1; i <= n; i++) cnt[(l[i] + r[i]) % M]++;

	double res = 0;
	for(int i = 0; i <= M; i++) if(cnt[i]) res -= ((double) cnt[i] / n) * log(1. * cnt[i] /  n);
	return res;
}
void solve()
{
	double ans = 1e10;
	int anss = 0, ansa = 0, ansc = 0;

	for(int s = 0; s <= 15; s++)
		for(int a = 0; a <= 15; a++)
			for(int c = 0; c <= 15; c++)
			{
				double ret = cal(s, a, c);
				if(ret + eps < ans)
				{
					ans = ret;
					anss = s;
					ansa = a;
					ansc = c;
				}
			}
	printf("%d %d %d\n", anss, ansa, ansc);
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		if(n == 0) break;
		for(int i = 1; i <= n; i++) scanf("%d", &l[i]);
		solve();
	}
	return 0;
}
