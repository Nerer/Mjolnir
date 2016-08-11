#include <bits/stdc++.h>

const int N = 1e3 + 100;
const int mod = 1e9 + 7;

int n;
int f[N];

void prepare() {
	f[1] = 1;
	for (int i = 1; i <= 1000; i ++) {
		for (int j = 1; i * j <= 1000; j ++) {
			f[i * j + 1] += f[i];
			f[i * j + 1] %= mod;
		}
	}
}

int main() {
	freopen("i.in", "r", stdin);
	
	prepare();
	
	int testCount = 0;
	while (std::cin >> n) {
		printf("Case %d: %d\n", ++testCount, f[n]);
	}
	
	return 0;
}
