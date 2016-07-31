#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>
#define next NWSSR
#define prev NSDeWQ
using namespace std;
const int mod = 1e9 + 7;
const int N = 5105;
int n;
int a[N], f[N][N], next[N][N], prev[N][N], g[N][N];
int last[N];

void update(int &maxl, int &counter, int len, int cnt) {
	if (len > maxl) {
		maxl = len;
		counter = cnt;
	} else {
		if (len == maxl) {
			counter += cnt;	
			counter %= mod;
		}
	}
}
void solve() {
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}	
	
	for (int i = 0; i <= n + 1; i++) {
		for (int j = 0; j <= n + 1; j++) {
			f[i][j] = -1;
			next[i][j] = -1;
			prev[i][j] = -1;
		}
	}
	for (int i = 1; i <= n; i++) {
		f[i][i] = 1;
		g[i][i] = 1;
	}
	vector<int> b;
	for (int i = 1; i <= n; i++) {
		b.push_back(a[i]);
	}
	sort(b.begin(), b.end());
	b.erase(unique(b.begin(), b.end()), b.end());
	for (int i = 1; i <= n; i++) {
		a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (next[j][a[i]] == -1) {
				next[j][a[i]] = i;
			}
		}
	}
	for (int i = n; i >= 1; i--) {
		for (int j = i + 1; j <= n + 1; j++) {
			if (prev[j][a[i]] == -1) {
				prev[j][a[i]] = i;
			}
		}
	}
	
	for (int i = n; i >= 1; i--) {
		int maxl = 0;
		int counter = 1;
		for (int j = 1; j <= n; j++) {
			last[j] = -1;
		}
		for (int j = i + 1; j <= n; j++) {
			if (a[j] < a[i]) {
				int lastcnt = 0, lastlen = 0;
				if (last[a[j]] != -1) {
					lastcnt = g[next[i][a[j]]][last[a[j]]];
					lastlen = f[next[i][a[j]]][last[a[j]]];
				}
				if (lastlen < f[next[i][a[j]]][j]) {
					update(maxl, counter, f[next[i][a[j]]][j], g[next[i][a[j]]][j]);
				} else {
					update(maxl, counter, f[next[i][a[j]]][j], (g[next[i][a[j]]][j] - lastcnt + mod) % mod);
				}
				last[a[j]] = j;
			} else {
				if (a[j] == a[i]) {
					f[i][j] = maxl + 2;
					g[i][j] = counter;
					int lastcnt = 0, lastlen = 0;
					if (last[a[j]] != -1) {
						lastcnt = g[next[i][a[j]]][last[a[j]]];
						lastlen = f[next[i][a[j]]][last[a[j]]];
					}
					if (lastlen < f[next[i][a[j]]][j]) {
						update(maxl, counter, f[next[i][a[j]]][j], g[next[i][a[j]]][j]);
					} else {
						update(maxl, counter, f[next[i][a[j]]][j], (g[next[i][a[j]]][j] - lastcnt + mod) % mod);
					}
					last[a[j]] = j;
				}
			}
		}
	}
	
	int answer_len = 1, answer_cnt = 0;
	for (int i = 1; i <= n; i++) {
		int l = next[0][i];
		int r = prev[n  + 1][i];
		if (l != -1 && r != -1) {
			answer_len = max(answer_len, f[l][r]);
		}
	}
	
	for (int i = 1; i <= n; i++) {
		int l = next[0][i];
		int r = prev[n  + 1][i];
		if (l != -1 && r != -1) {
			if (f[l][r] == answer_len) {
				answer_cnt += g[l][r];
				answer_cnt %= mod;
			}
		}
	}	
	
	printf("%d %d\n", answer_len, answer_cnt);
}

int main() {
	for (; scanf("%d", &n) == 1; solve());	
}
