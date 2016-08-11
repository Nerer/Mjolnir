#include <bits/stdc++.h>

using namespace std;

int n;
int x[1010], y[1010], t[1010];

long long sqr(long long x){return x*x;}
double dis(long long x1, long long y1, long long x2, long long y2){return sqrt(sqr(x1-x2)+sqr(y1-y2));}
int main()
{
	int cases;
	cin >> cases;
	while(cases--)
	{
		cin >> n;
		for(int i = 1; i <= n; i++) scanf("%d%d%d", &t[i], &x[i], &y[i]);
		
		double ans = 0;
		for(int i = 1; i < n; i++)
		{
			ans = max(ans, 1. * dis(x[i], y[i], x[i + 1], y[i + 1]) / (t[i + 1] - t[i]));
		}
		printf("%.12f\n", ans);
	}
	return 0;
}
