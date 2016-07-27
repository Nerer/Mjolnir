#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
int gxx;
double dp[20][30][55][4][2];
int mark[20][30][55][4][2];
double b[3][2], d[3][2];
void fix(double &x) {
	if (x < 0) x = 0;
	if (x > 1) x = 1;
}
double calc(int num0, int num2, int level, int top, int who) {
	double &result = dp[num0][num2][level][top][who];
	int &vis = mark[num0][num2][level][top][who];
	if (vis == gxx) {
		return result;
	}
	result = 0;
	vis = gxx;
	double p0 = b[0][who] - level * d[0][who];
	double p1 = b[1][who] - level * d[1][who];
	double p2 = b[2][who] - level * d[2][who];
	fix(p0);
	fix(p1);
	fix(p2);


	int top0 = top;
	top = (top + 1) % 3;
	if (top == 0) {
		top = 3;
	}

	if (num0 > 0) {
		if (top0 == 3) {
			result = max(result, p0 * (1 - calc(num0 - 1, num2, level + 1, top, who ^ 1)));
			result = max(result, p1 * (1 - calc(num0 - 1, num2 + 1, level + 1, top, who ^ 1)));
		}
		if (top0 == 2) {
			result = max(result, p0 * (1 - calc(num0, num2, level, top, who ^ 1)));
			result = max(result, p1 * (1 - calc(num0, num2 + 1, level, top, who ^ 1)));
		} 
		if (top0 == 1) {
			result = max(result, p0 * (1 - calc(num0 - 1, num2, level, top, who ^ 1)));
			result = max(result, p1 * (1 - calc(num0 - 1, num2 + 1, level, top, who ^ 1)));

		}
	}
	if (num2 > 0) {
		if (top0 == 3) {
			result = max(result, p2 * (1 - calc(num0, num2 - 1, level + 1, top, who ^ 1)));
		}
		if (top0 == 2) {
			result = max(result, p2 * (1 - calc(num0 + 1, num2 - 1, level, top, who ^ 1)));
		}
		if (top0 == 1) {
			result = max(result, p2 * (1 - calc(num0, num2 - 1, level, top, who ^ 1)));
		}
	}

	return result;
}
void solve() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < 3; i++) {
		scanf("%lf%lf", &b[i][0], &d[i][0]);
	}
	for (int i = 0; i < 3; i++) {
		scanf("%lf%lf", &b[i][1], &d[i][1]);
	}
	printf("%.4f\n", calc(n - 1, 0, n, 3, 0) + 1e-10);
}
int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		gxx = i;
		solve();
	}
	return 0;
}
