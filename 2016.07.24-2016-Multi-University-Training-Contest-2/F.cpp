#include <bits/stdc++.h>

const int N = 2e5 + 100;
const int mod = 1e9 + 7;

int n, m;
int weight[N];
std::vector<int> edge[N];
std::vector<int> tree[N];

int pre[N], bccNo[N], dfsClock, bccCnt;
bool isCut[N];
std::vector<int> bcc[N];
std::stack<std::pair<int, int> > s;

void clearAll() {
	for (int i = 1; i <= 2 * n; i ++) {
		edge[i].clear();
		tree[i].clear();
		pre[i] = 0;
		bccNo[i] = 0;
		bcc[i].clear();
		isCut[i] = false;
	}
	dfsClock = 0;
	bccCnt = 0;
}

void init() {
	std::cin >> n >> m;
	clearAll();
	for (int i = 1; i <= n; i ++) {
		scanf("%d", &weight[i]);
	}
	for (int i = 1; i <= m; i ++) {
		int u, v;
		scanf("%d%d", &u, &v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
}

int dfs(int u, int fa) {
	int lowu = pre[u] = ++dfsClock;
	int child = 0;
	for (int i = 0; i < (int)edge[u].size(); i ++) {
		int v = edge[u][i];
		std::pair<int, int> e = std::make_pair(u, v);
		if (pre[v] == 0) {
			s.push(e);
			child ++;
			int lowv = dfs(v, u);
			lowu = std::min(lowu, lowv);
			if (lowv >= pre[u]) {
				isCut[u] = true;
				bccCnt ++;
				bcc[bccCnt].clear();
				while (true) {
					std::pair<int, int> x = s.top();
					s.pop();
					if (bccNo[x.first] != bccCnt) {
						bcc[bccCnt].push_back(x.first);
						bccNo[x.first] = bccCnt;
					}
					if (bccNo[x.second] != bccCnt) {
						bcc[bccCnt].push_back(x.second);
						bccNo[x.second] = bccCnt;
					}
					if (x == std::make_pair(u, v)) {
						break;
					}
				}
			}
		} else if (pre[v] < pre[u] && v != fa) {
			s.push(e);
			lowu = std::min(lowu, pre[v]);
		}
	}
	if (fa < 0 && child == 1) {
		isCut[u] = false;
	}
	return lowu;
}

void dfs1(int u, int fa, int r, int root[], int pi[], int sum[]) {
	root[u] = r;
	for (int i = 0; i < (int)tree[u].size(); i ++) {
		int v = tree[u][i];
		if (v == fa) {
			continue;
		}
		dfs1(v, u, r, root, pi, sum);
		pi[u] = (long long)pi[u] * pi[v] % mod;
		sum[u] = (sum[u] + pi[v]) % mod;
	}
}

long long inverse(const long long &x, const long long &mod) {
	if (x == 1) {
		return 1;
	} else {
		return (mod - mod / x) * inverse(mod % x, mod) % mod;
	}
}

void work() {
	static int pi[N];

	for (int i = 1; i <= n; i ++) {
		if (pre[i] == 0) {
			dfs(i, -1);
		}
	}
	/*
	for (int i = 1; i <= bccCnt; i ++) {
		for (int j = 0; j < (int)bcc[i].size(); j ++) {
			printf("%d ", bcc[i][j]);
		}
		printf("\n");
	}
	*/
	for (int i = 1; i <= n; i ++) {
		pi[i] = weight[i];
	}
	for (int i = 1; i <= bccCnt; i ++) {
		pi[n + i] = 1;
		for (int j = 0; j < (int)bcc[i].size(); j ++) {
			int u = n + i, v = bcc[i][j];
			if (isCut[v]) {
				tree[u].push_back(v);
				tree[v].push_back(u);
				//printf("%d %d\n", u, v);
			} else {
				pi[n + i] = (long long)pi[n + i] * weight[v] % mod;
			}
		}
	}
	
	static int root[N], sum[N];
	
	std::vector<int> vecRoot;
	for (int i = 1; i <= 2 * n; i ++) {
		root[i] = 0;
		sum[i] = 0;
	}
	for (int i = 1; i <= bccCnt; i ++) {
		if (root[n + i] == 0) {
			vecRoot.push_back(n + i);
			dfs1(n + i, -1, n + i, root, pi, sum);
		}
	}
	
	int tmpAll = 0;
	for (int i = 1; i <= n; i ++) {
		if (edge[i].empty()) {
			tmpAll += weight[i];
			tmpAll %= mod;
		}
	}
	for (int i = 0; i < (int)vecRoot.size(); i ++) {
		tmpAll += pi[vecRoot[i]];
		tmpAll %= mod;
	}
	long long answer = 0;
	for (int i = 1; i <= n; i ++) {
		long long cur = 0;
		if (edge[i].empty()) {
			cur = (long long)tmpAll - (long long)weight[i];
			cur %= mod;
		} else {
			if (isCut[i]) {
				cur = (long long)tmpAll - (long long)pi[root[i]] + (long long)sum[i] + (long long)pi[root[i]] * inverse(pi[i], mod) % mod;
			} else {
				int u = n + bccNo[i];
				cur = (long long)tmpAll - (long long)pi[root[u]] + (long long)pi[root[u]] * inverse(weight[i], mod) % mod;
			}
		}
		//printf("w[%d] = %lld\n", i, cur);
		cur = (cur + mod) % mod;
		answer += (long long)i * cur % mod;
		answer %= mod;
		answer = (answer + mod) % mod;
	}
	std::cout << answer << std::endl;
}

int main() {
	freopen("f.in", "r", stdin);
	
	int testCnt;
	std::cin >> testCnt;
	while (testCnt --) {
		init();
		work();
	}
	
	return 0;
}
