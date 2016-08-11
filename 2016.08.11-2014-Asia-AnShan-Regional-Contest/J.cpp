#include <bits/stdc++.h>

const int N = 10;
const int mod = 1e9 + 7;

int n;
char matrix[N][N];

int bit(int state, int y) {
	return (state >> (y - 1)) & 1;
}

struct State {
	int f[N];
	
	State() {
		memset(f, 0, sizeof(f));
	}
	
	friend bool operator < (const State &a, const State &b) {
		for (int i = 1; i <= n; i ++) {
			if (a.f[i] < b.f[i]) {
				return true;
			} else if (a.f[i] > b.f[i]) {
				return false;
			}
		}
		return false;
	}
	
	State trans(int s) const {
		State result;
		
		for (int j = 1; j <= n; j ++) {
			if (bit(s, j) == 1) {
				result.f[j] = 0;
				continue;
			}
			if (j == 1) {
				result.f[j] = 1;
				continue;
			}
			if (f[j] >= f[j - 1] && result.f[j - 1] >= f[j - 1]) {
				result.f[j] = f[j - 1] + 1;
			} else {
				result.f[j] = std::min(f[j], result.f[j - 1]) + 1 ;
			}
		}
		return result;
	}
};

std::map<State, int> f[2][N];

void init() {
	std::cin >> n;
	for (int i = 1; i <= n; i ++) {
		scanf("%s", matrix[i] + 1);
	}
}

void work() {
	for (int i = 0; i <= 1; i ++) {
		for (int j = 0; j <= n + 1; j ++) {
			f[i][j].clear();
		}
	}

	f[0][0][State()] = 1;
	for (int i = 0; i < n; i ++) {
		for (int j = 0; j <= n; j ++) {
			f[(i + 1) & 1][j].clear();
		}
		for (int j = 0; j <= n; j ++) {
			for (std::map<State, int>::iterator it = f[i & 1][j].begin(); it != f[i & 1][j].end(); it ++) {
				for (int s = 0; s < (1 << n); s ++) {
					bool flag = true;
					for (int k = 1; k <= n; k ++) {
						if (matrix[i + 1][k] == '*' && bit(s, k) == 0) {
							flag = false;
							break;
						}
					}
					if (flag == false) {
						continue;
					}
					State ss = (it->first).trans(s);
					int jj = j;
					for (int k = 1; k <= n; k ++) {
						jj = std::max(jj, ss.f[k]);
					}
					(f[(i + 1) & 1][jj][ss] += it->second) %= mod;
				}
			}
		}
	}
	/*
	for (int i = 0; i <= n; i ++) {
		for (int j = 0; j <= n; j ++) {
			for (std::map<State, int>::iterator it = f[i][j].begin(); it != f[i][j].end(); it ++) {
				printf("f[%d][%d][{", i, j);
				for (int k = 1; k <= n; k ++) {
					printf("%d", (it->first).f[k]);
					if (k != n) {
						printf(", ");
					}
				}
				printf("}] = %d\n", it->second);
			}
		}
	}
	*/
	int answer[N];
	
	std::memset(answer, 0, sizeof(answer));
	for (int j = 0; j <= n; j ++) {
		//std::cout << "---" << f[n & 1][j].size() << std::endl;
		for (std::map<State, int>::iterator it = f[n & 1][j].begin(); it != f[n & 1][j].end(); it ++) {
			answer[j] += it->second;
			answer[j] %= mod;
		}
	}
	for (int i = 0; i <= n; i ++) {
		printf("%d\n", answer[i]);
	}
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
