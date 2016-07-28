#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;
const double eps = 1e-8;
const int N = 2221;
double c[N], v[N], r[N];
int n, m;
void solve() {
	double chps;
	scanf("%lf", &chps);
	double sumv = 0, sumr = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%lf%lf%lf", &c[i], &v[i], &r[i]);
		sumv += c[i] / v[i];
		sumr += r[i];		
	}
	int answer = 0;
	for (int i = 1; i <= n; i++) {
		if (i * chps > sumv - eps) {
			answer = i;
			break;
		}	
	}
	printf("%d\n", answer);
	for (int i = 1; i <= m; i++) {
		int k;
		scanf("%d", &k);
		if (k >= answer) {
			puts("-1.000");
			continue;
		}
		double low = 0, high = 200000;
		int rep = 0;
		while (rep < 100) {
			rep++;
			double mid = (low + high) / 2.;
			double sumcharge = chps * k * mid;
			for (int i = 1; i <= n; i++) {
				if (r[i] < mid * (c[i] / v[i])) {
					sumcharge -= (mid * c[i] / v[i] - r[i]);
				}
			}
			if (sumcharge > 0) {
				low = mid;
			} else {
				high = mid;
			}
		}
		if (low > 100000 + eps) {
			puts("-1.000");
		} else {
			printf("%.3f\n", low);
		}
	}
}
int main() {
	for (; scanf("%d%d", &n, &m) == 2 && (n != 0 || m != 0); ) {
		static int testCount = 0;
		printf("Case %d:\n", ++testCount);
		solve();
	}
	return 0;
}
