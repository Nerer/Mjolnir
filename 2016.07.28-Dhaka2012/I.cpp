#include <bits/stdc++.h>

const int N = 60;
const int RANGE = 60;

int n, m;
std::pair<int, int> a[N];
int f[N][N][RANGE * N];

void init() {
	std::cin >> n >> m;
	for (int i = 1; i <= n; i ++) {
		scanf("%d%d", &a[i].first, &a[i].second);
	}
}

bool cmp(std::pair<int, int> a, std::pair<int, int> b) {
	return a.second * b.first > b.second * a.first;
}

void update(int &x, int y) {
	x = std::max(x, y);
}

void work() {
	std::sort(a + 1, a + n + 1, cmp);
	
	/*
	f[0][0][0] = 0;
	for (int i = 0; i < n; i ++) {
		for (int j = 0; j < m; j ++) {
			for (int k = 0; k <= RANGE * n; k ++) {
				if (f[i][j][k] == -1) {
					continue;
				}
				update(f[i + 1][j][k], f[i][j][k]);
				update(f[i + 1][j + 1][k + a[i + 1].second], f[i][j][k] + a[i + 1].first * a[i + 1].second + 2 * a[i + 1].first * k);
			}
		}
	}
	*/
	
	std::vector<std::pair<std::pair<int, int>, int> > queue;
	queue.push_back(std::make_pair(std::make_pair(0, 0), 0));
	f[0][0][0] = 0;
	for (int l = 0; l < (int)queue.size(); l ++) {
		int i = queue[l].first.first, j = queue[l].first.second, k = queue[l].second;
		if (i == n) {
			continue;
		}
		if (f[i][j][k] > f[i + 1][j][k]) {
			f[i + 1][j][k] = f[i][j][k];
			queue.push_back(std::make_pair(std::make_pair(i + 1, j), k));
		}
		if (f[i + 1][j + 1][k + a[i + 1].second] < f[i][j][k] + a[i + 1].first * a[i + 1].second + 2 * a[i + 1].first * k) {
			f[i + 1][j + 1][k + a[i + 1].second] = f[i][j][k] + a[i + 1].first * a[i + 1].second + 2 * a[i + 1].first * k;
			queue.push_back(std::make_pair(std::make_pair(i + 1, j + 1), k + a[i + 1].second));
		}
	}
	
	int answer = 0;
	for (int k = 0; k <= RANGE * n; k ++) {
		answer = std::max(answer, f[n][m][k]);
	}
	
	for (int l = 0; l < (int)queue.size(); l ++) {
		int i = queue[l].first.first, j = queue[l].first.second, k = queue[l].second;
		f[i][j][k] = -1;
	}
	
	std::cout << answer << std::endl;
}

int main() {
	freopen("i.in", "r", stdin);
	
	memset(f, -1, sizeof(f));
	
	int testCount;
	std::cin >> testCount;
	for (int i = 1; i <= testCount; i ++) {
		printf("Case %d: ", i);
		init();
		work();
	}
	
	return 0;
}
