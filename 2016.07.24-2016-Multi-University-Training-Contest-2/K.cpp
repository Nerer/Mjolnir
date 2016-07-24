#include <bits/stdc++.h>

const int N = 1e5 + 100;

int n;
int a[N];

void init() {
	std::cin >> n;
	for (int i = 1; i <= n; i ++) {
		scanf("%d", &a[i]);
	}
}

void work() {
	int t = 0, sum = 0;
	for (int i = 1; i <= n; i ++) {
		t += (a[i] & 1);
		sum += a[i] - (a[i] & 1);
	}
	if (t == 0) {
		printf("%d\n", sum);
	} else {
		printf("%d\n", (sum / 2) / t * 2 + 1);
	}
}

int main() {
	freopen("k.in", "r", stdin);
	
	int testCnt;
	std::cin >> testCnt;
	while (testCnt --) {
		init();
		work();
	}
	
	return 0;
}
