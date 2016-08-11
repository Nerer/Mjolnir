#include <bits/stdc++.h>

const int N = 5e4 + 100;

int n, k;
long long a[N];

long long sqr(long long x) {
	return x * x;
}

void init() {
	std::cin >> n >> k;
	k = n - k;
	for (int i = 1; i <= n; i ++) {
		int t;
		scanf("%d", &t);
		a[i] = t;
	}
}

void work() {
	std::sort(a + 1, a + n + 1);
	
	static long long sum[N][3];
	
	sum[0][1] = sum[0][2] = 0;
	for (int i = 1; i <= n; i ++) {
		sum[i][1] = sum[i - 1][1] + a[i];
		sum[i][2] = sum[i - 1][2] + a[i] * a[i];
	}

	long long answer = LONG_LONG_MAX;
	for (int i = k; i <= n; i ++) {
		long long tmp2 = (sum[i][2] - sum[i - k][2]) * k;
		long long tmp1 = sqr(sum[i][1] - sum[i - k][1]);
		
		answer = std::min(answer, tmp2 - tmp1);
	}
	if (k == 0) {
		std::cout << 0 << std::endl;
		return;
	}
	std::cout << answer / k << ".";
	for (int t = 1; t <= 30; t ++) {
		answer %= k;
		answer *= 10;
		std::cout << answer / k;
	}
	printf("\n");
}

int main() {
	freopen("d.in", "r", stdin);
	
	int testCount;
	std::cin >> testCount;
	while (testCount --) {
		init();
		work();
	}
	
	return 0;
}
