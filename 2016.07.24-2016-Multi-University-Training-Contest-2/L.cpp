#include <bits/stdc++.h>

const int N = 1e5 + 100;
const int M = 5e3 + 100;

int n, m;
char str[2][N];
std::bitset<N> occur[30];
std::bitset<N> f[3];

void init() {
	std::cin >> n >> m;
	scanf("%s%s", str[0] + 1, str[1] + 1);
}

void work() {
	for (int i = 0; i < 26; i ++) {
		occur[i].reset();
	}
	for (int i = 1; i <= n; i ++) {
		occur[str[0][i] - 'a'][i] = 1;
	}
	
	for (int i = 0; i < 3; i ++) {
		f[i].reset();
	}
	f[0].set();
	for (int i = 0; i < m; i ++) {
		f[(i + 1) % 3] |= (f[i % 3] << 1) & occur[str[1][i + 1] - 'a'];
		if (i + 2 <= m) {
			f[(i + 2) % 3] |= (f[i % 3] << 2) & (occur[str[1][i + 2] - 'a'] << 1) & occur[str[1][i + 1] - 'a'];
		}
		f[i % 3].reset();
	}
	
	static char answer[N];
	for (int i = 1; i <= n; i ++) {
		if (i + m - 1 <= n && f[m % 3][i + m - 1]) {
			answer[i] = '1';
		} else {
			answer[i] = '0';
		}
	}
	answer[n + 1] = '\0';
	puts(answer + 1);
}

int main() {
	freopen("l.in", "r", stdin);
	
	int testCnt;
	std::cin >> testCnt;
	while (testCnt --) {
		init();
		work();
	}
	
	return 0;
}
