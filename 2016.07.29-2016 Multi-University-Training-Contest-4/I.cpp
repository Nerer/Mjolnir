#include <bits/stdc++.h>

const int N = 120;
const int INF = 1e9;
const int MAX_DIST = N * N + 1;

int n;
char str[N];
int a[N], b[N];
int w[N][N];

struct Edge {
	int u, v, w;
	int next;
};
Edge edge[1000000];
int end[N * N], begin[N * N], tot;
int cnt[MAX_DIST + 10], dist[N * N];
int pre[N * N];

int num(int x, int y) {
	return (x - 1) * n + y;
}

void init() {
	std::cin >> n;
	scanf("%s", str + 1);
	for (int i = 0; i <= 9; i ++) {
		scanf("%d%d", &a[i], &b[i]);
	}
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			scanf("%d", &w[i][j]);
		}
	}
}

void addEdge(int u, int v, int w) {
	//printf("%d %d %d\n", u, v, w);
	edge[tot] = (Edge){u, v, w, end[u]};
	end[u] = tot++;
	edge[tot] = (Edge){v, u, 0, end[v]};
	end[v] = tot++;
}

void bfs(int source, int target) {
	for (int i = source; i <= target; i ++) {
		dist[i] = MAX_DIST;
		cnt[i] = 0;
	}
	cnt[MAX_DIST] = 0;
	
	std::vector<int> queue;
	dist[target] = 0;
	queue.push_back(target);
	
	for (int l = 0; l < (int)queue.size(); l ++) {
		int u = queue[l];
		for (int i = end[u]; i != -1; i = edge[i].next) {
			int v = edge[i].v;
			if (dist[u] + 1 < dist[v]) {
				dist[v] = dist[u] + 1;
				queue.push_back(v);
			}
		}
	}
	for (int i = source; i <= target; i ++) {
		cnt[dist[i]] ++;
	}
}

int findNext(int u) {
	for (int i = begin[u]; i != -1; i = edge[i].next) {
		int v = edge[i].v;
		if (edge[i].w > 0 && dist[v] + 1 == dist[u]) {
			return begin[u] = i;
		}
	}
	return begin[u] = -1;
}

int reDist(int u) {
	int result = MAX_DIST;
	for (int i = end[u]; i != -1; i = edge[i].next) {
		int v = edge[i].v;
		if (edge[i].w > 0) {
			result = std::min(result, dist[v] + 1);
		}
	}
	return result;
}

int flow(int source, int target) {
	bfs(source, target);
	
	int result = 0;
	
	for (int i = source; i <= target; i ++) {
		begin[i] = end[i];
	}
	
	int u = source;
	while (dist[source] != MAX_DIST) {
		int i = findNext(u);
		if (i != -1) {
			int v = edge[i].v;
			pre[v] = i;
			u = v;
			if (u == target) {
				int cur = 1e9;
				for (int i = target; i != source; i = edge[pre[i]].u) {
					cur = std::min(cur, edge[pre[i]].w);
				}
				for (int i = target; i != source; i = edge[pre[i]].u) {
					edge[pre[i]].w -= cur;
					edge[pre[i] ^ 1].w += cur;
				}
				result += cur;
				u = source;
			}
		} else {
			int tmp = reDist(u);
			cnt[tmp] ++;
			cnt[dist[u]] --;
			if (cnt[dist[u]] == 0) {
				return result;
			}
			dist[u] = tmp;
			begin[u] = end[u];
			if (u != source) {
				u = edge[pre[u]].u;
			}
		}
	}
	return result;
}

void work() {
	int source = 1, target = 1 + n * n + n + 10 + 1;
	int answer = 0;
	
	for (int i = source; i <= target; i ++) {
		end[i] = -1;
	}
	tot = 0;
	
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			answer += w[i][j];
			addEdge(1, 1 + num(i, j), w[i][j]);
		}
	}
	for (int i = 1; i <= n; i ++) {
		addEdge(1 + n * n + i, target, a[str[i] - '0']);
	}
	for (int i = 0; i <= 9; i ++) {
		addEdge(1 + n * n + n + 1 + i, target, b[i] - a[i]);
	}
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			addEdge(1 + num(i, j), 1 + n * n + i, INF);
			addEdge(1 + num(i, j), 1 + n * n + j, INF);
		}
	}
	for (int i = 1; i <= n; i ++) {
		addEdge(1 + n * n + i, 1 + n * n + n + 1 + (str[i] - '0'), INF);
	}
	
	answer -= flow(source, target);
	std::cout << answer << std::endl;
}

int main() {
	freopen("i.in", "r", stdin);
	
	int testCount = 0;
	std::cin >> testCount;
	for (int i = 1; i <= testCount; i ++) {
		printf("Case #%d: ", i);
		init();
		work();
	}
	
	return 0;
}
