#include <bits/stdc++.h>

const int N = 12;

int n;
int targetLen;
std::string str[N];
int value[N];

int trie[1500][5], tot;
int fail[1500];
int st[1500];

void init() {
	for (int i = 1; i <= tot; i ++) {
		std::memset(trie[i], 0, sizeof(trie[i]));
		st[i] = fail[i] = 0;
	}
	tot = 1;
	
	for (int i = 1; i <= n; i ++) {
		std::cin >> str[i] >> value[i];
		for (int j = 0; j < (int)str[i].length(); j ++) {
			if (str[i][j] == 'A') {
				str[i][j] = '0';
			} else if (str[i][j] == 'T') {
				str[i][j] = '1';
			} else if (str[i][j] == 'C') {
				str[i][j] = '2';
			} else {
				str[i][j] = '3';
			}
		}
	}
}

void add(std::string s, int num) {
	int cur = 1;
	for (int i = 0; i < (int)s.length(); i ++) {
		if (trie[cur][s[i] - '0'] == 0) {
			trie[cur][s[i] - '0'] = ++tot;
		}
		cur = trie[cur][s[i] - '0'];
	}
	st[cur] |= 1 << num;
}

void getFail() {
	std::vector<int> queue;
	
	fail[1] = 1;
	for (int i = 0; i < 4; i ++) {
		if (trie[1][i] == 0) {
			trie[1][i] = 1;
		} else {
			int v = trie[1][i];
			fail[v] = 1;
			queue.push_back(v);
			st[v] |= st[1];
		}
	}
	
	for (int l = 0; l < (int)queue.size(); l ++) {
		int u = queue[l];
		for (int i = 0; i < 4; i ++) {
			if (trie[u][i] == 0) {
				trie[u][i] = trie[fail[u]][i];
			} else {
				int v = trie[u][i];
				fail[v] = trie[fail[u]][i];
				st[v] |= st[fail[v]];
				queue.push_back(v);
			}
		}
	}
}

int bit(int state, int y) {
	return (state >> y) & 1;
}

int getValue(int state) {
	int result = 0;
	for (int i = 1; i <= n; i ++) {
		if (bit(state, i)) {
			result += value[i];
		}
	}
	return result;
}

void work() {
	for (int i = 1; i <= n; i ++) {
		if ((int)str[i].length() <= targetLen) {
			add(str[i], i);
		}
	}
	getFail();

	std::vector<std::pair<int, int> > queue[120];
	
	static int visit[2][1500][1 << N];
	static int timeClock = 1;
	
	queue[0].push_back(std::make_pair(1, 0));
	visit[0][1][0] = timeClock;
	
	for (int t = 0; t < targetLen; t ++) {
		for (int l = 0; l < (int)queue[t].size(); l ++) {
			int u = queue[t][l].first, state = queue[t][l].second;
			for (int i = 0; i < 4; i ++) {
				int v = trie[u][i];
				int ss = state | st[v];
				if (visit[(t + 1) & 1][v][ss] != timeClock + 1) {
					visit[(t + 1) & 1][v][ss] = timeClock + 1;
					queue[t + 1].push_back(std::make_pair(v, ss));
				}
			}
		}
		timeClock ++;
	}
	
	int answer = -1e9;
	for (int i = 0; i < (int)queue[targetLen].size(); i ++) {
		answer = std::max(answer, getValue(queue[targetLen][i].second));
	}
	if (answer >= 0) {
		std::cout << answer << std::endl;
	} else {
		printf("No Rabbit after 2012!\n");
	}
}

int main() {
	freopen("g.in", "r", stdin);
	
	while (std::cin >> n >> targetLen) {
		init();
		work();
	}
	
	return 0;
}
