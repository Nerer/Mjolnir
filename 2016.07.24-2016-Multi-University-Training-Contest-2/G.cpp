#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <cassert>

const int N = 550;
const int INF = 1e9;
const int INF_DIST = 1e9;

int n, m;
bool color[N];
int dist[N][N];
std::vector<int> edge[N];

struct KMSolver {
	int n, m;
	int a[N][N];
	int u[N], v[N], p[N], fa[N], minv[N];
	bool used[N];
	
	KMSolver(int n, int m):n(n), m(m) {
		for (int i = 0; i <= n; i ++) {
			for (int j = 0; j <= m; j ++) {
				a[i][j] = 0;
			}
		}
		for (int i = 0; i <= std::max(n, m); i ++) {
			u[i] = v[i] = p[i] = fa[i] = minv[i] = 0;
			used[i] = false;
		}
	}
	
	int km() {
		std::fill(u, u + n, 0);
		for (int i = 0; i <= m; i ++) {
			v[i] = 0;
			p[i] = n;
		}
		for (int i = 0; i < n; i ++) {
			p[m] = i;
			int j0 = m;
			for (int j = 0; j <= m; j ++) {
				minv[j] = INF;
				used[j] = false;
			}
			do {
				used[j0] = true;
				int i0 = p[j0], delta = INF, j1;
				for (int j = 0; j < m; j ++) {
					if (!used[j]) {
						int cur = a[i0][j] - u[i0] - v[j];
						if (cur < minv[j]) {
							minv[j] = cur;
							fa[j] = j0;
						}
						if (minv[j] < delta) {
							delta = minv[j];
							j1 = j;
						}
					}
				}
				for (int j = 0; j <= m; j ++) {
					if (used[j]) {
						u[p[j]] += delta;
						v[j] -= delta;
					} else {
						minv[j] -= delta;
					}
				}
				j0 = j1;
			} while (p[j0] != n);
			do {
				int j1 = fa[j0];
				p[j0] = p[j1];
				j0 = j1;
			} while (j0 != m);
		}
		return -v[m];
	}
};
KMSolver kmSolver(0, 0);

inline void read(int&a){char c;while(!(((c=getchar())>='0')&&(c<='9')));a=c-'0';while(((c=getchar())>='0')&&(c<='9'))(a*=10)+=c-'0';}

void init(int cnt) {
	std::cin >> n >> m;
	
	static char str[N];
	//std::cin >> (str + 1);
	scanf("%s", str + 1);
	
	for (int i = 1; i <= n; i ++) {
		if (str[i] == '1') {
			color[i] = true;
		} else {
			color[i] = false;
		}
	}
	
	std::fill(edge + 1, edge + n + 1, std::vector<int>());
	for (int i = 1; i <= m; i ++) {
		int u, v;
		scanf("%d%d", &u, &v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
}

void floyd() {
	for (int k = 1; k <= n; k ++) {
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= n; j ++) {
				dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
}

bool dfs(int u, int cur, int tag[], int cnt[], std::vector<int> vec[]) {
	vec[cur].push_back(u);
	cnt[(int)color[u]] ++;
	tag[u] = cur;
	for (int i = 0; i < (int)edge[u].size(); i ++) {
		int v = edge[u][i];
		if (tag[v] != -1) {
			if (tag[v] != 1 - cur) {
				return false;
			}
		} else if (dfs(v, 1 - cur, tag, cnt, vec) == false) {
			return false;
		}
	}
	return true;
}

void getPath(int u, int target, std::vector<int> &path) {
	path.push_back(u);
	for (int i = 0; i < (int)edge[u].size(); i ++) {
		int v = edge[u][i];
		if (dist[u][v] + dist[v][target] == dist[u][target]) {
			getPath(v, target, path);
			return ;
		}
	}
}

void getDist() {
	for (int source = 1; source <= n; source ++) {
		std::vector<int> queue;
		
		for (int i = 1; i <= n; i ++) {
			dist[source][i] = INF_DIST;
		}
		
		queue.push_back(source);
		dist[source][source] = 0;

		for (int l = 0; l < (int)queue.size(); l ++) {
			int u = queue[l];
			for (int i = 0; i < (int)edge[u].size(); i ++) {
				int v = edge[u][i];
				if (dist[source][u] + 1 < dist[source][v]) {
					dist[source][v] = dist[source][u] + 1;
					queue.push_back(v);
				}
			}
		}
	}
}

void work() {
	//floyd();
	getDist();
	
	int answer = 0;
	std::vector<std::pair<int, int> > pairs;
	
	static int tag[N];
	std::fill(tag + 1, tag + n + 1, -1);
	for (int i = 1; i <= n; i ++) {
		if (tag[i] == -1) {
			std::vector<int> vec[2];
			int cnt[2] = {0, 0};
			if (dfs(i, 1, tag, cnt, vec) == false) {
				printf("-1\n");
				return ;
			}
			int minCost = INF;
			std::vector<std::pair<int, int> > tmp;
			for (int t = 0; t <= 1; t ++) {
				if ((int)vec[0].size() == cnt[t] && (int)vec[1].size() == cnt[t ^ 1]) {
					std::vector<int> bad[2];
					for (int j = 0; j < (int)vec[0].size(); j ++) {
						if (color[vec[0][j]] != t) {
							bad[0].push_back(vec[0][j]);
						}
					}
					for (int j = 0; j < (int)vec[1].size(); j ++) {
						if (color[vec[1][j]] != (t ^ 1)) {
							bad[1].push_back(vec[1][j]);
						}
					}
					assert(bad[0].size() == bad[1].size());
					kmSolver = KMSolver((int)bad[0].size(), (int)bad[1].size());
					for (int j = 0; j < (int)bad[0].size(); j ++) {
						for (int k = 0; k < (int)bad[1].size(); k ++) {
							kmSolver.a[j][k] = dist[bad[0][j]][bad[1][k]];
						}
					}
					int cc = kmSolver.km();
					if (cc < minCost) {
						minCost = cc;
						tmp.clear();
						for (int j = 0; j < (int)bad[1].size(); j ++) {
							tmp.push_back(std::make_pair(bad[1][j], bad[0][kmSolver.p[j]]));
						}
					}
				}
			}
			if (minCost == INF) {
				printf("-1\n");
				return ;
			} else {
				answer += minCost;
				for (int j = 0; j < (int)tmp.size(); j ++) {
					pairs.push_back(tmp[j]);
				}
			}
		}
	}
	std::cout << answer << std::endl;
	for (int i = 0; i < (int)pairs.size(); i ++) {
		//printf("%d %d\n", pairs[i].first, pairs[i].second);
		
		int source = pairs[i].first, target = pairs[i].second;
		std::vector<int> path;
		getPath(source, target, path);

		int u = source;
		for (int j = 0; j < (int)path.size(); j ++) {
			if (color[path[j]] != color[source]) {
				for (int k = j; path[k] != u; k --) {
					printf("%d %d\n", path[k], path[k - 1]);
				}
				u = path[j];
			}
		}
		std::swap(color[pairs[i].first], color[pairs[i].second]);
	}
}

int main() {
	//freopen("g.in", "r", stdin);
	
	int testCnt;
	std::cin >> testCnt;
	for (int i = 1; i <= testCnt; i ++) {
		init(i);
		work();
	}
	
	return 0;
}
