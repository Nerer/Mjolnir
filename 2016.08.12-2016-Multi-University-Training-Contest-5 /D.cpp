#include <bits/stdc++.h>

const int N = 2e3 + 100;

int n;
std::pair<int, int> a[N];

void init() {
	for (int i = 1; i <= n; i ++) {
		scanf("%d%d", &a[i].first, &a[i].second);
	}
}

long long dot(const std::pair<int, int> &a, const std::pair<int, int> &b) {
	return 1LL * a.first * b.first + 1LL * a.second * b.second;
}

long long cross(const std::pair<int, int> &a, const std::pair<int, int> &b) {
	return 1LL * a.first * b.second - 1LL * a.second * b.first;
}

int getPhase(const std::pair<int, int> &a) {
	if (a.first > 0 && a.second >= 0) {
		return 1;
	}
	if (a.second > 0 && a.first <= 0) {
		return 2;
	}
	if (a.first < 0 && a.second <= 0) {
		return 3;
	}
	if (a.second < 0 && a.first >= 0) {
		return 4;
	}
	assert(false);
}

bool cmpAngle(const std::pair<int, int> &a, const std::pair<int, int> &b) {	
	//return std::atan2(a.second, a.first) < std::atan2(b.second, b.first);
	//return std::atan2((double)a.second, (double)a.first) < std::atan2((double)b.second, (double)b.first);
	
	if (getPhase(a) != getPhase(b)) {
		return getPhase(a) < getPhase(b);
	} else {
		return cross(a, b) > 0;
	}
}

void work() {
	long long cnt = 0, cntLine = 0,  cnt22 = 0;
	for (int i = 1; i <= n; i ++) {
		static std::pair<int, int> vec[N << 1];
		
		int size = 0;
		
		for (int j = 1; j <= n; j ++) {
			if (i != j) {
				vec[size ++] = std::make_pair(a[j].first - a[i].first, a[j].second - a[i].second);
			}
		}
		std::sort(vec, vec + size, cmpAngle);
		
		int cc = size;
		for (int j = 0; j < cc; j ++) {
			vec[size ++] = vec[j];
		}
		
		int t[3] = {0, 0, 0};
		int tmp = 0;
		for (int j = 0; j < size; j ++) {
			t[0] = std::max(t[0], j - cc + 1);
			t[1] = std::max(t[1], j - cc + 1);
			while (t[1] < j && (cross(vec[j], vec[t[1]]) > 0 || (cross(vec[j], vec[t[1]]) == 0 && dot(vec[j], vec[t[1]]) > 0))) {
				t[1] ++;
			}
			t[0] = std::max(t[0], t[1]);
			while (t[0] < j && dot(vec[j], vec[t[0]]) <= 0) {
				t[0] ++;
			}
			t[2] = std::max(t[2], t[1]);
			while (t[2] < t[0] && cross(vec[j], vec[t[2]]) == 0) {
				t[2] ++;
			}
			if (j >= cc) {
				cnt += t[0] - t[1];
				cntLine += t[2] - t[1];
			}
		}
		//printf("(%d, %d) --> %d\n", a[i].first, a[i].second, tmp);
		/*if (i == 2) {
			for (int j = 0; j < cc; j++) {
				printf("(%d, %d)\n", vec[j].first, vec[j].second);
			}
		}
		*/
		/*static std::pair<int, int> vv[N];
		int ss = 0;
		
		for (int j = 1; j <= n; j ++) {
			if (i != j) {
				int dx = a[j].first - a[i].first, dy = a[j].second - a[i].second;
				int gg = std::__gcd(std::abs(dx), std::abs(dy));
				dx /= gg;
				dy /= gg;
				
				if (dx < 0 || (dx == 0 && dy < 0)) {
					dx *= -1;
					dy *= -1;
				}
				
				vv[ss ++] = std::make_pair(dx, dy);
			}
		}
		
		std::sort(vv, vv + ss);
		for (int j = 0, l = -1; j < ss; j ++) {
			if (j + 1 == ss || vv[j + 1] != vv[j]) {
				cnt22 += (long long)(j - l) * (j - l - 1);
				l = j;
			}
		}
		*/
	}
	std::cout << (long long)n * (n - 1) * (n - 2) / 6 - cnt + cntLine / 2 << std::endl;
	
}

int main() {
	freopen("d.in", "r", stdin);
	
	while (std::cin >> n) {
		init();
		work();
	}
	
	return 0;
}
