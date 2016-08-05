#include <bits/stdc++.h>

const int N = 5e6 + 100;
const int mod = 1e9 + 7;

int n;
int f[N];
int pw2[N];

void prepare() {
	f[1] = f[2] = 0;
	for (int i = 3; i <= 5000000; i ++) {
		f[i] = std::max(0, (i - 1) / 2 - (i + 2) / 3 + 1);
		f[i] += f[i - 1];
		f[i] %= mod;
		if (i % 2 == 0) {
			f[i] -= i / 2 / 2;
			f[i] = (f[i] + mod) % mod;
		}
	}
	for (int i = 1; i <= 5000000; i ++) {
		for (int j = i * 2; j <= 5000000; j += i) {
			f[j] -= f[i];
			f[j] = (f[j] + mod) % mod;
		}
	}
	
	pw2[0] = 1;
	for (int i = 1; i <= 5000000; i ++) {
		pw2[i] = pw2[i - 1] * 2 % mod;
	}
}

void work() {
	int answer = 0;
	for (int i = 1; i * i <= n; i ++) {
		if (n % i == 0) {
			answer += (long long)f[i] * pw2[n / i - 1] % mod;
			answer %= mod;
			if (i * i != n) {
				answer += (long long)f[n / i] * pw2[i - 1] % mod;
				answer %= mod;
			}
		}
	}
	std::cout << answer << std::endl;
}

int main() {
	//freopen("4466.in", "r", stdin);
	
	prepare();
	
	int testCount = 0;
	while (std::cin >> n) {
		printf("Case %d: ", ++testCount);
		work();
	}
	
	return 0;
}
