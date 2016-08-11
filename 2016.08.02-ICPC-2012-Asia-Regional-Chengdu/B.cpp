#include <bits/stdc++.h>

using namespace std;
const double eps = 1e-8;

int n;
double p;
double logfac[200010];

double C(int n, int k)
{
	if(k < 0 || k > n) return 0.;
	if(k == 0 || k == n) return 1.;
	double a = 1, b = 1;
	for(int i = n - k + 1; i <= n; i++) a = a * i;
	for(int i = 1; i <= k; i++) b = b * i;
	return a / b;
}
void solve()
{
	double ans = 0;
	
	if(p < eps || p + eps > 1)
	{
		printf("%.10f\n", (double) n);
		return;
	}
	/*for(int i = 1; i <= n; i++)
	{
		double tmp = 0, tmp1, tmp2;
		tmp = logfac[n - 1  + n - i] - logfac[n - 1] - logfac[n - i];
		tmp1 = log(p) + log(i) + tmp + (n - 1) * log(p) + (n - i) * log(q);
		tmp2 = log(q) + log(i) + tmp + (n - 1) * log(q) + (n - i) * log(p);
		ans += exp(tmp1) + exp(tmp2);
	}*/
	
	for(int i = 0; i <= n - 1; i++)
	{
		double tmp1, tmp2;
		tmp1 = (n + 1) * log(p) + i * log(1 - p) + logfac[n + i] - logfac[i] - logfac[n] + log(n - i);
		tmp2 = (n + 1) * log(1 - p) + i * log(p) + logfac[n + i] - logfac[i] - logfac[n] + log(n - i);
		ans += exp(tmp1) + exp(tmp2);
	}
	printf("%.10f\n", ans);
}
int main()
{
	logfac[0] = 0;
	for(int i = 1; i <= 200000; i++) logfac[i] = logfac[i - 1] + log(i);

	int T = 0;
	while(~scanf("%d%lf", &n, &p))
	{
		printf("Case %d: ", ++T);
		solve();
	}
	return 0;
}
