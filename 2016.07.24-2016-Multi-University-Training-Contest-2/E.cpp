#include <bits/stdc++.h>

const int N = 1e3 + 100;
const int mod = 1e9 + 7;

int n;
std::pair<int, int> point[N];
int pw2[N];

void init() {
	std::cin >> n;
	for (int i = 1; i <= n; i ++) {
		int x, y;
		scanf("%d%d", &x, &y);
		point[i] = std::make_pair(x, y);
	}
}

void work() {
	pw2[0] = 1;
	for (int i = 1; i <= n; i ++) {
		pw2[i] = pw2[i - 1] * 2 % mod;
	}

	std::map<std::pair<int, int>, int> p;
	
	for (int i = 1; i <= n; i ++) {
		p[point[i]] ++;
	}
	
	int answer = 0;
	for (std::map<std::pair<int, int>, int>::iterator it = p.begin(); it != p.end(); it ++) {
		std::pair<int, int> pivot = it->first;
		
		std::map<std::pair<int, int>, int> cnt;
		for (int i = 1; i <= n; i ++) {
			if (point[i].first < pivot.first || (point[i].first == pivot.first && point[i].second <= pivot.second)) {
				continue;
			}
			int dx = point[i].first - pivot.first, dy = point[i].second - pivot.second;
			int g = std::__gcd(std::abs(dx), std::abs(dy));
			dx /= g;
			dy /= g;
			cnt[std::make_pair(dx, dy)] ++;
		}
		int tmp = 1;
		for (std::map<std::pair<int, int>, int>::iterator it1 = cnt.begin(); it1 != cnt.end(); it1 ++) {
			tmp += pw2[it1->second] - 1;
			tmp %= mod;
		}
		answer += (long long)tmp * (pw2[it->second] + mod - 1) % mod;
		answer %= mod;
	}
	std::cout << (answer + mod - n) % mod << std::endl;
}

int main() {
	freopen("e.in", "r", stdin);
	
	int testCnt;
	std::cin >> testCnt;
	while (testCnt --) {
		init();
		work();
	}
	
	return 0;
}
