#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
int n, m;
int score[111][111];
int a[111];
int f[111][111];
void update(int &x, int y) {
	if (x < 0 || x < y) {
		x = y;
	}
}
void solve() {
	scanf("%d%d", &n, &m);	
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &score[i][j]);
		}
	}
	
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			f[i][j] = -1;
		}
	}
	f[0][0] = 0;
	
	for (int i = 1; i <= n; i++) {
		if (a[i] > 0) {
			for (int j = 0; j <= m; j++) {
				if (f[i - 1][j] >= 0) {
					update(f[i][a[i]], f[i - 1][j] + score[j][a[i]]);
				}
			}
		} else {
			for (int j = 1; j <= m; j++) {
				for (int k = 0; k <= m; k++) {
					if (f[i - 1][k] >= 0) {
						update(f[i][j], f[i - 1][k] + score[k][j]);
					}
				}
			}
		}
	}
	int answer = -1;
	for (int i = 1; i <= m; i++) {
		update(answer, f[n][i]);
	}
	printf("%d\n", answer);
}

int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		solve();
	}
	return 0;
}
