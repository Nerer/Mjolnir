#include <bits/stdc++.h>

const int N = 1e3 + 100;
const int mod = 1e9 + 7;

int n, m;
int a[N], b[N];

void init() {
	for (int i = 1; i <= n; i ++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= m; i ++) {
		scanf("%d", &b[i]);
	}
}

void work() {
	static int f[N][N];
	static int sum[N];
	
	f[0][0] = 1;
	sum[0] = 1;
	for (int i = 1; i <= m; i ++) {
		sum[i] = 1;
	}
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			if (a[i] == b[j]) {
				f[i][j] = sum[j - 1];
			} else {
				f[i][j] = 0;
			}
		}
		int tmp = 0;
		for (int j = 1; j <= m; j ++) {
			tmp += f[i][j];
			tmp %= mod;
			sum[j] += tmp;
			sum[j] %= mod;
		}
	}
	int answer = 0;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			//printf("f[%d][%d] = %d\n", i, j, f[i][j]);
			answer += f[i][j];
			answer %= mod;
		}
	}
	printf("%d\n", answer);
}

int main() {
	freopen("k.in", "r", stdin);
	
	while (std::cin >> n >> m) {
		init();
		work();
	}
	
	return 0;
}
