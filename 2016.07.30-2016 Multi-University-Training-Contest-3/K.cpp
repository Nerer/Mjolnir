#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 211111;
pair<int, int> p[N];
int occur[N * 2];
void solve() {
	int n, m;	
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &p[i].first, &p[i].second);
	}
	for (int i = 1; i <= 2 * m + 1; i++) {
		occur[i] = 0;
	}
	bool flg = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			int d = abs(p[j].first - p[i].first) + abs(p[i].second - p[j].second);
			if (occur[d]) {
				flg = 1;
				break;
			}
			occur[d] = 1;
		}
		if (flg) break;
	}
	
	if (flg) {
		puts("YES");
	} else {
		puts("NO");		
	}
	
}

int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		solve();
	}
	return 0;
}
