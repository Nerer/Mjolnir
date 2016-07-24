#include <bits/stdc++.h>

const int N = 150;

int n, m;
std::pair<int, int> p[N];

void init() {
	std::cin >> n >> m;
	for (int i = 1; i <= m; i ++) {
		int x, y;
		scanf("%d%d", &x, &y);
		p[i] = std::make_pair(x, y);
	}
}

void work() {
	static std::pair<int, int> range[N];
	
	std::fill(range + 1, range + n + 1, std::make_pair(0, 100));
	
	for (int i = 1; i <= m; i ++) {
		range[p[i].first] = std::make_pair(p[i].second, p[i].second);
	}
	for (int i = 2; i <= n; i ++) {
		range[i].second = std::min(range[i].second, range[i - 1].second);
	}
	for (int i = n - 1; i >= 1; i --) {
		range[i].first = std::max(range[i].first, range[i + 1].first);
	}
	
	int s[2] = {0, 0};
	s[0] = range[1].second + range[2].second;
	s[1] = s[0];
	for (int i = 3; i <= n; i ++) {
		s[1] += range[i].first;
	}
	
	int g = std::__gcd(s[0], s[1]);
	s[0] /= g;
	s[1] /= g;
	std::cout << s[0] << '/' << s[1] << std::endl;
}

int main() {
	freopen("i.in", "r", stdin);
	
	int testCnt;
	std::cin >> testCnt;
	while (testCnt --) {
		init();
		work();
	}
	
	return 0;
}
