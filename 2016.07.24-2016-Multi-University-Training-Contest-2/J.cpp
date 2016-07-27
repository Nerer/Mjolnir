#include <bits/stdc++.h>

const int N = 50;
const int mod = 1e9 + 7;

int n, m;
std::pair<int, int> range[N];
std::pair<std::pair<int, int>, int> pro[N * N];

int father[N], d[N], size[N];

void init() {
	std::cin >> n >> m;
	for (int i = 1; i <= n; i ++) {
		scanf("%d%d", &range[i].first, &range[i].second);
	}
	for (int i = 1; i <= m; i ++) {
		scanf("%d%d%d", &pro[i].first.first, &pro[i].first.second, &pro[i].second);
	}
}

int find(int u) {
	if (father[u] == u) {
		return u;
	}
	int t = father[u];
	father[u] = find(t);
	d[u] ^= d[t];
	return father[u];
}

bool merge(int u, int v, int s) {
	//printf("%d %d %d\n", u, v, s);
	if (find(u) == find(v)) {
		if ((d[u] ^ d[v]) != s) {
			return false;
		}
	} else {
		if (find(u) < find(v)) {
			std::swap(u, v);
		}
		int vv = find(v);
		d[vv] = s ^ d[v];
		father[vv] = u;
	}
	return true;
}

int calc(int i, int s) {
	int length = range[i].second - range[i].first + 1;
	if (length & 1) {
		return length / 2 + (range[i].second % 2 == s);
	} else {
		return length / 2;
	}
}

int getMin(int i, int s) {
	for (int x = range[i].first; ; x ++) {
		if (x % 2 == s) {
			return x;
		}
	}
}

int bit(int state, int x) {
	return (state >> x) & 1;
}

bool cmp(int i, int t, std::pair<int, int> g[N][2]) {
	for ( ; i <= n; i ++) {
		if (g[i][t].first != g[i][t ^ 1].first) {
			return g[i][t].first < g[i][t ^ 1].first;
		}
		t = g[i][t].second;
	}
	return false;
}

void work() {
	for (int i = 1; i <= n + 1; i ++) {
		father[i] = i;
		d[i] = 0;
		size[i] = 0;
	}
	for (int i = 1; i <= m; i ++) {
		int l = pro[i].first.first, r = pro[i].first.second, s = pro[i].second;
		if (merge(l, r + 1, s) == false) {
			printf("0\n-1\n");
			return ;
		}
	}
	for (int i = 1; i <= n + 1; i ++) {
		size[find(i)] ++;
	}
	
	static int num[N];
	
	std::vector<int> vec;
	for (int i = n + 1; i >= 1; i --) {
		if (find(i) == i && size[i] >= 2) {
			vec.push_back(i);
			num[i] = (int)vec.size() - 1;
		}
	}
	
	int answer = 0;
	std::vector<int> bestAnswer;
	for (int state = 0; state < (1 << (int)vec.size()); state ++) {
		if (!vec.empty() && vec[0] == n + 1 && bit(state, 0) == 1) {
			continue;
		}
	
		static int f[N][2];
		static std::pair<int, int> g[N][2];
		
		memset(f, 0, sizeof(f));
		memset(g, -1, sizeof(g));
		
		f[n + 1][0] = 1;
		g[n + 1][0].first = 0;
		for (int i = n; i >= 1; i --) {
			if (size[find(i)] == 1) {
				for (int t = 0; t <= 1; t ++) {
				if (g[i + 1][t].first != -1 && calc(i, 0)) {
					if (g[i][t].first == -1 || (g[i][t].first > getMin(i, 0) || (g[i][t].first == getMin(i, 0) && cmp(i + 1, t, g)))) {
							g[i][t].first = getMin(i, 0);
							g[i][t].second = t;
						}
						f[i][t] += (long long)f[i + 1][t] * calc(i, 0) % mod;
						f[i][t] %= mod;
					}
					if (g[i + 1][t ^ 1].first != -1 && calc(i, 1)) {
						if (g[i][t].first == -1 || (g[i][t].first > getMin(i, 1) || (g[i][t].first == getMin(i, 1) && cmp(i + 1, t ^ 1, g)))) {
							g[i][t].first = getMin(i, 1);
							g[i][t].second = t ^ 1;
						}
						f[i][t] += (long long)f[i + 1][t ^ 1] * calc(i, 1) % mod;
						f[i][t] %= mod;
					}
				}
			} else {
				int t = bit(state, num[find(i)]) ^ d[i];
				if (g[i + 1][t].first != -1 && calc(i, 0)) {
					if (g[i][t].first == -1 || (g[i][t].first > getMin(i, 0) || (g[i][t].first == getMin(i, 0) && cmp(i + 1, t, g)))) {
						g[i][t].first = getMin(i, 0);
						g[i][t].second = t;
					}
					f[i][t] += (long long)f[i + 1][t] * calc(i, 0) % mod;
					f[i][t] %= mod;
				}
				if (g[i + 1][t ^ 1].first != -1 && calc(i, 1)) {
					if (g[i][t].first == -1 || (g[i][t].first > getMin(i, 1) || (g[i][t].first == getMin(i, 1) && cmp(i + 1, t ^ 1, g)))) {
						g[i][t].first = getMin(i, 1);
						g[i][t].second = t ^ 1;
					}
					f[i][t] += (long long)f[i + 1][t ^ 1] * calc(i, 1) % mod;
					f[i][t] %= mod;
				}
			}
		}
		
		/*
		printf("state = %d\n", state);
		for (int i = n; i >= 1; i --) {
			printf("f[%d] = {%d, %d}\n", i, f[i][0], f[i][1]);
		}
		*/
		answer += (f[1][0] + f[1][1]) % mod;
		answer %= mod;
		
		for (int k = 0; k <= 1; k ++) {
			if (g[1][k].first == -1) {
				continue;
			}
			std::vector<int> cur;
			for (int i = 1, t = k; i <= n; i ++) {
				cur.push_back(g[i][t].first);
				t = g[i][t].second;
			}
			if (bestAnswer.empty() || bestAnswer > cur) {
				bestAnswer = cur;
			}
		}
	}
	if (!bestAnswer.empty()) {
		std::cout << answer << std::endl;
		for (int i = 0; i < (int)bestAnswer.size(); i ++) {
			printf("%d%c", bestAnswer[i], " \n"[i + 1 == (int)bestAnswer.size()]);
		}
	} else {
		printf("0\n-1\n");
	}
}

int main() {
	//freopen("j.in", "r", stdin);
	//freopen("j.out", "w", stdout);
	
	int testCnt;
	std::cin >> testCnt;
	for (int i = 1; i <= testCnt; i ++) {
		init();
		work();
	}
	
	return 0;
}
