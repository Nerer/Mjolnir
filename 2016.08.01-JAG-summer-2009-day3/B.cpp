#include <bits/stdc++.h>

const int N = 150;

int n, m;
int a[N], bound[N];

void init() {
	for (int i = 0; i < n; i ++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= 101; i ++) {
		bound[i] = 23;
	}
	std::cin >> m;
	for (int i = 1; i <= m; i ++) {
		int x, y;
		scanf("%d%d", &x, &y);
		bound[x] = std::min(bound[x], y);
	}
}

void work() {
	static int f[N];
	
	memset(f, 0, sizeof(f));
	
	f[0] = 0;
	for (int i = 100; i >= 1; i --) {
		f[i] = 1e9;
		for (int j = i; j <= 100; j ++) {
			if (a[(j - i) % n] <= bound[j]) {
				f[i] = std::min(f[i], f[j + 1] + 1);
			} else {
				break;
			}
		}
	}
	printf("%d\n", f[1] - 1);
}

int main() {
	freopen("b.in", "r", stdin);
	
	while (std::cin >> n && n != 0) {
		init();
		work();
	}
	
	return 0;
}
