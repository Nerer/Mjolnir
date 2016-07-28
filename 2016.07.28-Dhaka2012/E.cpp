#include <bits/stdc++.h>

const int N = 160;

int a, b;

void init() {
	std::cin >> a >> b;
}

void dfs(int t, int a, int b, std::pair<double, double> &answer) {
	if (t >= 60) {
		return ;
	}
	if (a == 0 || b == 0) {
		answer.first += t / (double)(1LL << t);
		if (b == 0) {
			answer.second += 1.0 / (double)(1LL << t);
		}
		return ;
	}
	int c = std::min(a, b);
	dfs(t + 1, a - c, b + c, answer);
	dfs(t + 1, a + c, b - c, answer);
}

void work() {
	std::pair<double, double> answer = std::make_pair(0, 0);
	
	dfs(0, a, b, answer);
	
	printf("%.6f %.6f\n", answer.first, answer.second);
}

int main() {
	freopen("e.in", "r", stdin);
	
	int testCount;
	std::cin >> testCount;
	for (int i = 1; i <= testCount; i ++) {
		printf("Case %d: ", i);
		init();
		work();
	}
	
	return 0;
}
