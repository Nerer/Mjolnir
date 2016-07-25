#include <bits/stdc++.h>

const int N = 1e4 + 100;

int n;
struct Function {
	double a, b, c;
	
	long double value(long double x) {
		return a * x * x + b * x + c;
	}
};
Function f[N];

void init() {
	std::cin >> n;
	for (int i = 1; i <= n; i ++) {
		scanf("%lf%lf%lf", &f[i].a, &f[i].b, &f[i].c);
	}
}

long double getMax(long double x) {
	long double result = -1e20;
	for (int i = 1; i <= n; i ++) {
		result = std::max(result, f[i].value(x));
	}
	return result;
}

void work() {
	long double low = 0, high = 1000.0;
	int repeats = 0;
	while (repeats < 100) {
		repeats++;
		long double mid1 = (2.0 * low + high) / 3.0, mid2 = (low + 2 * high) / 3.0;
		if (getMax(mid1) > getMax(mid2) + 1e-8) {
			low = mid1;
		} else {
			high = mid2;
		}
	}
	printf("%.4f\n", (double)getMax((low + high) / 2.0) + 1e-8);
}

int main() {
	freopen("f.in", "r", stdin);
	
	int testCnt;
	std::cin >> testCnt;
	while (testCnt --) {
		init();
		work();
	}
	
	return 0;
}
