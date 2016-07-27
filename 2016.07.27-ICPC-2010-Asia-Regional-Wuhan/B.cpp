#include <bits/stdc++.h>

const int N = 1e3 + 100;

int n, m;
std::vector<int> edge[3][N << 1];

void init() {
	for (int i = 0; i < 3; i ++) {
		for (int j = 1; j <= 2 * n; j ++) {
			edge[i][j].clear();
		}
		for (int j = 1; j <= n; j ++) {
			edge[i][2 * j - 1].push_back(2 * j);
		}
	}
	
	for (int i = 1; i <= m; i ++) {
		char cc[10];
		int x, y;
		
		scanf("%s%d%d", cc, &x, &y);
		
		if (cc[0] == 'I') {
			for (int t = 0; t < 3; t ++) {
				edge[t][2 * x - 1].push_back(2 * y);
				edge[t][2 * y - 1].push_back(2 * x);
			}
		} else {
			int t;
			if (cc[0] == 'X') {
				t = 0;
			} else if (cc[0] == 'Y') {
				t = 1;
			} else {
				t = 2;
			}
			
			edge[t][2 * x].push_back(2 * y - 1);
		}
	}
}

void work() {
	static int answer[N << 1][3];

	for (int t = 0; t < 3; t ++) {
		static int degree[N << 1];
		
		std::vector<int> queue;
		
		std::fill(degree + 1, degree + 2 * n + 1, 0);
		for (int i = 1; i <= 2 * n; i ++) {
			for (int j = 0; j < (int)edge[t][i].size(); j ++) {
				degree[edge[t][i][j]] ++;
			}
		}
		for (int i = 1; i <= 2 * n; i ++) {
			if (degree[i] == 0) {
				queue.push_back(i);
			}
		}
		for (int l = 0; l < (int)queue.size(); l ++) {
			int u = queue[l];
			for (int i = 0; i < (int)edge[t][u].size(); i ++) {
				int v = edge[t][u][i];
				degree[v] --;
				if (degree[v] == 0) {
					queue.push_back(v);
				}
			}
		}
		if ((int)queue.size() != 2 * n) {
			printf("IMPOSSIBLE\n");
			return ;
		}
		for (int i = 0; i < (int)queue.size(); i ++) {
			answer[queue[i]][t] = i;
		}
	}
	printf("POSSIBLE\n");
	for (int i = 1; i <= n; i ++) {
		for (int t = 1; t >= 0; t --) {
			for (int c = 0; c < 3; c ++) {
				printf("%d", answer[2 * i - t][c]);
				if (c < 2) {
					printf(" ");
				}
			}
			if (t == 1) {
				printf(" ");
			} else {
				printf("\n");
			}
		}
	}
}

int main() {
	freopen("b.in", "r", stdin);
	
	int testCnt = 0;
	while (std::cin >> n >> m && !(n == 0 && m == 0)) {
		printf("Case %d: ", ++testCnt);
		init();
		work();
		printf("\n");
	}
	
	return 0;
}
