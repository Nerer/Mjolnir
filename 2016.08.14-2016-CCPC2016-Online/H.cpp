#include <bits/stdc++.h>

const int N = 2e2 + 10;

int n;
struct Point {
	int x, y, z;
	
	Point() {}
	Point(int x, int y, int z):x(x), y(y), z(z) {}
	
	friend bool operator < (const Point &a, const Point &b) {
		if (a.x != b.x) {
			return a.x < b.x;
		} else if (a.y != b.y) {
			return a.y < b.y;
		}
		return a.z < b.z;
	}
	
	friend Point operator + (const Point &a, const Point &b) {
		return Point(a.x + b.x, a.y + b.y, a.z + b.z);
	}
	
	friend Point operator - (const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y, a.z - b.z);
	}
};
Point p[N];

std::map<Point, bool> exist;

void init() {
	std::cin >> n;
	exist.clear();
	for (int i = 1; i <= n; i ++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		p[i] = Point(x, y, z);
		exist[p[i]] = true;
	}
}

int sqr(int x) {
	return x * x;
}

int dist2(const Point &a, const Point &b) {
	return sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z);
}

int count_45() {
	int result = 0;
	for (int i = 1; i <= n; i ++) {
		for (int j = i + 1; j <= n; j ++) {
			std::map<int, int> cnt;
			int tmp = 0;
			for (int k = 1; k <= n; k ++) {
				if (dist2(p[i], p[k]) == dist2(p[j], p[k])) {
					cnt[dist2(p[i], p[k])] ++;
					tmp += exist[p[i] + p[j] - p[k]];
				}
			}
			for (std::map<int, int>::iterator it = cnt.begin(); it != cnt.end(); it ++) {
				result += it->second * (it->second - 1) / 2;
			}
			result -= tmp / 2;
		}
	}
	return result / 2;
}

int count_6() {
	static std::bitset<N> s[N][N];
	
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			s[i][j].reset();
			for (int k = 1; k <= n; k ++) {
				if (dist2(p[i], p[j]) == dist2(p[j], p[k]) && dist2(p[i], p[j]) == dist2(p[i], p[k])) {
					s[i][j][k] = 1;
				}
			}
		}
	}
	
	int result = 0;
	for (int i = 1; i <= n; i ++) {
		for (int j = i + 1; j <= n; j ++) {
			for (int k = j + 1; k <= n; k ++) {
				if (dist2(p[i], p[j]) == dist2(p[j], p[k]) && dist2(p[i], p[j]) == dist2(p[i], p[k])) {
					result += (s[i][j] & s[j][k]).count();
				}
			}
		}
	}
	return result / 4;
}

void work() {
	int tmp[2] = {count_45(), count_6()};
	
	std::cout << tmp[0] - 2 * tmp[1] << std::endl;
}

int main() {
	freopen("h.in", "r", stdin);
	
	int testCount;
	std::cin >> testCount;
	for (int i = 1; i <= testCount; i ++) {
		printf("Case #%d: ", i);
		init();
		work();
	}
	
	return 0;
}
