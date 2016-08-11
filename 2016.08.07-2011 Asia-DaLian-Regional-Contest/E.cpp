#include <bits/stdc++.h>

const int N = 1e3 + 100;
const int mod = 1e9 + 7;

int n;
char str[N];

void work() {
	static int f[N][N];
	
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			f[i][j] = 0;
		}
	}
	
	n = std::strlen(str + 2) + 1;
	
	f[1][1] = 1;
	for (int i = 2; i <= n; i ++) {
		static int sum[N];
		
		sum[0] = 0;
		for (int j = 1; j <= i - 1; j ++) {
			sum[j] = (sum[j - 1] + f[i - 1][j]) % mod;
		}
		
		for (int j = 1; j <= i; j ++) {
			if (str[i] == 'I') {
				f[i][j] = sum[j - 1];
			} else if (str[i] == 'D') {
				f[i][j] = (sum[i - 1] - sum[j - 1] + mod) % mod;
			} else {
				f[i][j] = sum[i - 1];
			}
			//printf("f[%d][%d] = %d\n", i, j, f[i][j]);
		}
	}
	int answer = 0;
	for (int i = 1; i <= n; i ++) {
		answer = (answer + f[n][i]) % mod;
	}
	std::cout << answer << std::endl;
}

int main() {
	freopen("e.in", "r", stdin);
	
	while (std::cin >> (str + 2)) {
		work();
	}
	
	return 0;
}
