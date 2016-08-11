#include <bits/stdc++.h>

long long n;

void work() {
	long long answer = 0;
	for (long long i = 1; i * i * i <= n; i ++) {
		answer ++;
		answer += (n / (i * i) - i) * 3;
		for (int j = i + 1; i * j * j <= n; j ++) {
			answer += 3;
			answer += (n / (i * j) - j) * 6;
		}
	}
	printf("%lld\n", answer);
}

int main() {
	freopen("j.in", "r", stdin);
	
	int testCount = 0;
	while (std::cin >> n) {
		printf("Case %d: ", ++testCount);
		work();
	}
	
	return 0;
}
