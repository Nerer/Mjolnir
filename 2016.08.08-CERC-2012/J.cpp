#include <bits/stdc++.h>

const int N = 1e5 + 100;

int n, m;
int belong[N];
std::vector<int> edge[N];

void init() {
	std::cin >> n >> m;
	for (int i = 1; i <= n; i ++) {
		scanf("%d", &belong[i]);
		belong[i] --;
	}
	std::fill(edge + 1, edge + n + 1, std::vector<int>());
	for (int i = 1; i <= m; i ++) {
		int u, v;
		scanf("%d%d", &u, &v);
		edge[u].push_back(v);
	}
}

void work() {
	int answer = n + 1;
	for (int begin = 0; begin <= 1; begin ++) {
		static int degree[N];
		
		std::fill(degree + 1, degree + n + 1, 0);
		
		for (int i = 1; i <= n; i ++) {
			for (int j = 0; j < (int)edge[i].size(); j ++) {
				degree[edge[i][j]] ++;
			}
		}
		
		std::queue<int> queue[2];
		
		for (int i = 1; i <= n; i ++) {
			if (degree[i] == 0) {
				queue[belong[i]].push(i);
			}
		}
		
		int cur = begin, cntTrans = 0;
		
		while (!queue[0].empty() || !queue[1].empty()) {
			if (queue[cur].empty()) {
				cntTrans ++;
				cur ^= 1;
			}
			
			int u = queue[cur].front();
			queue[cur].pop();
			
			for (int i = 0; i < (int)edge[u].size(); i ++) {
				int v = edge[u][i];
				degree[v] --;
				if (degree[v] == 0) {
					queue[belong[v]].push(v);
				}
			}
		}
		answer = std::min(answer, cntTrans);
	}
	std::cout << answer << std::endl;
}

int main() {
	freopen("j.in", "r", stdin);
	
	int testCount;
	std::cin >> testCount;
	while (testCount --) {
		init();
		work();
	}
	
	return 0;
}
