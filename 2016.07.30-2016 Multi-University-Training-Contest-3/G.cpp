#include <bits/stdc++.h>

const int N = 1e5 + 100;

int n;
std::vector<int> edge[N];
int f[N][2][3];

void init() {
	std::cin >> n;
	std::fill(edge + 1, edge + n + 1, std::vector<int>());
	for (int i = 1; i <= n - 1; i ++) {
		int u, v;
		scanf("%d%d", &u, &v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
}

void update(int &x, int y) {
	x = std::min(x, y);
}

void dfs(int u, int father) {
	f[u][0][0] = 0;
	
	for (int i = 0; i < (int)edge[u].size(); i ++) {
		int v = edge[u][i];
		if (v == father) {
			continue;
		}
		dfs(v, u);
		static int tmp[2][3];
		for (int j = 0; j <= 1; j ++) {
			for (int k = 0; k <= 2; k ++) {
				tmp[j][k] = f[u][j][k];
				f[u][j][k] = 1e9;
			}
		}
		for (int j = 0; j <= 1; j ++) {
			for (int k = 1; k <= 2; k ++) {
				for (int jj = 0; jj <= 1; jj ++) {
					for (int kk = 0; kk <= 2; kk ++) {
						if (j + jj <= 1) {
							int t = k + kk;
							while (t > 2) {
								t -= 2;
							}
							f[u][j + jj][t] = std::min(f[u][j + jj][t], tmp[jj][kk] + f[v][j][k] + k);
						}
					}
				}
			}
		}
	}
	update(f[u][0][1], f[u][0][0]);
	update(f[u][1][1], f[u][1][0]);
	f[u][0][0] = f[u][1][0] = 1e9;
	f[u][1][1] = std::min(f[u][1][1], f[u][0][2]);
}

void work() {
	int cntLeaf = 0;
	for (int i = 1; i <= n; i ++) {
		cntLeaf += ((int)edge[i].size() == 1);
	}

	for (int i = 1; i <= n; i ++) {
		for (int j = 0; j <= 1; j ++) {
			for (int k = 0; k <= 2; k ++) {
				f[i][j][k] = 1e9;
			}
		}
	}
	dfs(1, -1);
	
	for (int i = 1; i <= n; i ++) {
		for (int j = 0; j <= 1; j ++) {
			for (int k = 0; k <= 2; k ++) {
				if (f[i][j][k] < 1e9) {
					//printf("f[%d][%d][%d] = %d\n", i, j, k, f[i][j][k]);
				}
			}
		}
	}
	int answer = 1e9;
	for (int j = 0; j <= cntLeaf % 2; j ++) {
		for (int k = 1; k <= 2; k ++) {
			answer = std::min(answer, f[1][j][k]);
		}
	}
	std::cout << answer << std::endl;
}

int main() {
	freopen("g.in", "r", stdin);
	
	int testCount;
	std::cin >> testCount;
	while (testCount --) {
		init();
		work();
	}
	
	return 0;
}
