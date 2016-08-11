#include <bits/stdc++.h>

const int N = 1e5 + 100;
const int MAGIC = 300;

int n, m;
std::vector<std::pair<int, long long> > edge[N];
long long sumWeight;
bool color[N];
long long sum[N][2];
long long answer[2];

void init() {
	for (int i = 1; i <= n; i ++) {
		int t;
		scanf("%d", &t);
		color[i] = t;
	}
	std::fill(edge + 1, edge + n + 1, std::vector<std::pair<int, long long> >());
	memset(answer, 0, sizeof(answer));
	sumWeight = 0;
	
	for (int i = 1; i <= m; i ++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		edge[u].push_back(std::make_pair(v, (long long)w));
		edge[v].push_back(std::make_pair(u, (long long)w));
		
		sumWeight += w;
	}
}

void work() {
	std::vector<int> big;
	
	for (int i = 1; i <= n; i ++) {
		std::sort(edge[i].begin(), edge[i].end());
		
		std::vector<std::pair<int, long long> > tmp;
		tmp = edge[i];
		edge[i].clear();
		for (int j = 0; j < (int)tmp.size(); j ++) {
			if (j == 0 || tmp[j].first != tmp[j - 1].first) {
				edge[i].push_back(tmp[j]);
			} else {
				edge[i].back().second += tmp[j].second;
			}
		}
		
		if ((int)edge[i].size() >= MAGIC) {
			big.push_back(i);
		}
	}
	for (int i = 0; i < (int)big.size(); i ++) {
		sum[i][0] = sum[i][1] = 0;
	}
	for (int i = 0; i < (int)big.size(); i ++) {
		int u = big[i];
		for (int j = 0; j < (int)edge[u].size(); j ++) {
			int v = edge[u][j].first;
			if ((int)edge[v].size() < MAGIC || v > u) {
				sum[i][color[v]] += edge[u][j].second;
			}
		}
	}
	for (int u = 1; u <= n; u ++) {
		if ((int)edge[u].size() >= MAGIC) {
			continue;
		}
		for (int i = 0; i < (int)edge[u].size(); i ++) {
			int v = edge[u][i].first;
			if ((int)edge[v].size() < MAGIC && color[u] == color[v] && u < v) {
				answer[color[u]] += edge[u][i].second;
			}
		}
	}
	
	int q;
	std::cin >> q;
	while (q --) {
		static char cc[10];
		
		scanf("%s", cc);
		
		if (cc[0] == 'C') {
			int u;
			scanf("%d", &u);
			color[u] ^= true;
			
			if ((int)edge[u].size() < MAGIC) {
				for (int i = 0; i < (int)edge[u].size(); i ++) {
					int v = edge[u][i].first;
					if ((int)edge[v].size() >= MAGIC) {
						continue;
					}
					if (color[v] == color[u]) {
						answer[color[v]] += edge[u][i].second;
					} else {
						answer[color[v]] -= edge[u][i].second;
					}
				}
			}
			for (int i = 0; i < (int)big.size(); i ++) {
				int v = big[i];
				int t = std::lower_bound(edge[v].begin(), edge[v].end(), std::make_pair(u, -1LL)) - edge[v].begin();
				if (t == (int)edge[v].size() || edge[v][t].first != u) {
					continue;
				}
				if ((int)edge[u].size() < MAGIC || u > v) {
					sum[i][color[u]] += edge[v][t].second;
					sum[i][color[u] ^ 1] -= edge[v][t].second;
				}
			}
		} else {
			int a, b;
			scanf("%d%d", &a, &b);
			
			long long tmp[2] = {0, 0};
			
			for (int i = 0; i < (int)big.size(); i ++) {
				int u = big[i];
				tmp[color[u]] += sum[i][color[u]];
			}
			
			if (a == b) {
				printf("%lld\n", answer[a] + tmp[a]);
			} else {
				printf("%lld\n", sumWeight - answer[0] - tmp[0] - answer[1] - tmp[1]);
			}
		}
	}
}

int main() {
	freopen("d.in", "r", stdin);
	
	int testCount = 0;
	while (std::cin >> n >> m) {
		printf("Case %d:\n", ++testCount);
		init();
		work();
	}
	
	return 0;
}
