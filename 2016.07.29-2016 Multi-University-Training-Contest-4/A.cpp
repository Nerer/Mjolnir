#include <bits/stdc++.h>

const int N = 1e5 + 100;
const int mod = 1e9 + 7;

int n, m;
char str[2][N];

void init() {
	scanf("%s%s", str[0] + 1, str[1] + 1);
	n = std::strlen(str[0] + 1);
	m = std::strlen(str[1] + 1);
}

void buildKmp(int fail[]) {
	fail[1] = 0;
	for (int i = 2; i <= m; i ++) {
		int t = fail[i - 1];
		while (t != 0 && str[1][t + 1] != str[1][i]) {
			t = fail[t];
		}
		if (str[1][t + 1] == str[1][i]) {
			fail[i] = t + 1;
		} else {
			fail[i] = 0;
		}
	}
}

void work() {
	static int fail[N];

	buildKmp(fail);
	
	static int f[N];

	int t = 0;	
	f[0] = 1;
	for (int i = 1; i <= n; i ++) {
		f[i] = f[i - 1];
		
		while (t != 0 && (t == m || str[1][t + 1] != str[0][i])) {
			t = fail[t];
		}
		if (str[1][t + 1] == str[0][i]) {
			t ++;
		} else {
			t = 0;
		}
		
		if (t == m) {
			f[i] += f[i - m];
			f[i] %= mod;
		}
		//printf("f[%d] = %d, t = %d\n", i, f[i], t);
	}
	std::cout << f[n] << std::endl;
}

int main() {
	freopen("a.in", "r", stdin);
	
	int testCount;
	std::cin >> testCount;
	for (int i = 1; i <= testCount; i ++) {
		printf("Case #%d: ", i);
		init();
		work();
	}
	
	return 0;
}
