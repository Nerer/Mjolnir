#include <bits/stdc++.h>

const int N = 350;
const int mod = 1e9 + 7;

int n, m;
int prime[N];

std::bitset<N> a[N];
std::bitset<N> matrix[N];

void getPrime() {
	static bool visit[2050];
	
	for (int i = 2; i <= 2000; i ++) {
		if (visit[i] == false) {
			prime[++m] = i;
		}
		for (int j = 1; j <= m && i * prime[j] <= 2000; j ++) {
			visit[i * prime[j]] = true;
			if (i % prime[j] == 0) {
				break;
			}
		}
	}
	//std::cout << m << std::endl;
}

void init() {
	std::cin >> n;
	for (int i = 1; i <= n; i ++) {
		a[i].reset();
		
		long long t;
		scanf("%I64d", &t);
		
		for (int j = 1; j <= m; j ++) {
			while (t % prime[j] == 0) {
				a[i][j] = 1 ^ a[i][j];
				t /= prime[j];
			}
		}
	}
}

void gauss(int &cntBase) {
	int cur = 0;
	for (int i = 1; i <= n; i ++) {
		if (matrix[cur + 1][i] == 0) {
			for (int j = cur + 2; j <= m; j ++) {
				if (matrix[j][i] == 1) {
					std::swap(matrix[cur + 1], matrix[j]);
					break;
				}
			}
		}
		if (matrix[cur + 1][i] == 0) {
			continue;
		}
		cur ++;
		for (int j = 1; j <= m; j ++) {
			if (j != cur && matrix[j][i] == 1) {
				matrix[j] ^= matrix[cur];
			}
		}
	}
	cntBase = n - cur;
}

void work() {
	for (int i = 1; i <= m; i ++) {
		matrix[i].reset();
		
		for (int j = 1; j <= n; j ++) {
			matrix[i][j] = a[j][i];
		}
	}
	
	int cntBase;
	gauss(cntBase);
	
	int answer = 1;
	for (int i = 1; i <= cntBase; i ++) {
		answer = answer * 2 % mod;
	}
	answer = (answer + mod - 1) % mod;
	
	std::cout << answer << std::endl;
}

int main() {
	freopen("b.in", "r", stdin);
	
	getPrime();
	
	int testCount;
	std::cin >> testCount;
	for (int i = 1; i <= testCount; i ++) {
		printf("Case #%d:\n", i);
		init();
		work();
	}
	
	return 0;
}
