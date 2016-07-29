#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
const int N = 111111;
vector<int> adj[N];
vector<int> trial;
bool haveAns;
int n;
int vis[N], maxval[N], value[N], choose[N], b[N], mark[N];
int root;
void dfs(int x) {
	vis[x] = 1;
	maxval[x] = value[x];
	int tmp = 0;
	for (int i = 0; i < (int)adj[x].size(); i++) {
		int y = adj[x][i];
		if (!vis[y]) { 
			dfs(y);
			tmp = max(maxval[y], tmp);
		}	
	}
	if (tmp < value[x]) {
		choose[x] = value[x];
		if (mark[choose[x]] == 0) {
			mark[choose[x]] = 1;
		} else {
			haveAns = 0;
		}
	}
	if (tmp > value[x]) {
		haveAns = 0;
	}
	maxval[x] = max(tmp, value[x]);
}


void go(int x, int from) {
	bool haveNext = 0;
	for (int i = 0; i < (int)adj[x].size(); i++) {
		if (adj[x][i] != from && value[adj[x][i]] == n) {
			haveNext = 1;
			go(adj[x][i], x);
		}
	}
	if (!haveNext) {
		trial.push_back(x);
	}
}
void add(int x, int y) {
	adj[x].push_back(y);
}
bool cmp(int x, int y) {
	return value[x] < value[y];
}
void solve() {
	scanf("%d", &n);	
	
	int cntN = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &value[i]);
		if (value[i] == n) {
			++cntN;
		}
		
		adj[i].clear();
	}		

	for (int i = 1; i < n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
		add(y, x);
	}
	for (int i = 1; i <= n; i++) {
		vis[i] = 0;
		choose[i] = 0;
		mark[i] = 0;
	}	
	int root = -1;
	trial.clear();
	for (int i = 1; i <= n; i++) {
		if (value[i] == n) {
			go(i, 0);
			if (cntN > 1) {
				if (trial.size() == 1) {
					trial.push_back(i);
				}
				if (trial.size() > 2) {
					puts("Impossible");
					return; 	
				}
				root = min(trial[0], trial[1]);
			} else {
				root = trial[0];
			}
			break;
		}
	}

	if (root == -1) {
		puts("Impossible");
		return;
	}
	haveAns = 1;
	dfs(root);
	if (!haveAns) {
		puts("Impossible");
		return;
	}
	for (int i = 1; i <= n; i++) {
		b[i] = i;
	}
	sort(b + 1, b + n + 1, cmp);
	int last = n;
	priority_queue<int> heap;
	bool flag = 1;
	for (int i = n - 1; i >= 1; i--) {
		if (mark[i]) {
			continue;			
		}
		for (; value[b[last]] - 1 >= i && last >= 1; last--) {
			if (!choose[b[last]]) {
				heap.push(b[last]);
			}
		}
		if (!heap.empty()) {
			choose[heap.top()] = i;
			heap.pop();
		} else {
			flag = 0;
			break;
		}
	}
	
	if (!flag) {
		puts("Impossible");
	} else {
		vector<int> tmp;
		for (int i = 1; i <= n; i++) {
			tmp.push_back(choose[i]);
		}
		sort(tmp.begin(), tmp.end());
		tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
		if ((int)tmp.size() != n) {
			puts("Impossible");
			return;
		}
		for (int i = 1; i <= n; i++) {
			printf("%d%c", choose[i], i == n ? '\n' : ' ');
		}
	}
}

int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		printf("Case #%d: ", i);
		solve();
	}
}
