#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n, m, k;
int gxx;
int base, avg;
int number[10], dependent[111];
double prob[11][1111];
int vis[33][8 * 8 * 8 * 8 * 8][2];
double f[33][8 * 8 * 8 * 8 * 8][2];
int getState(int a[]) {
	int ret = 0;
	for (int i = n; i >= 1; i--) {
		ret = ret * base + a[i];
	}
	return ret;
}
double dfs(int pos, int state, int pre) {
	//cout << pos << " " << state << " " << pre << endl;
	if (pos > m) {
		return 0;
	}

	double &result = f[pos][state][pre];
	int &tts = vis[pos][state][pre];
	if (tts == gxx) {
		return result;
	}
	//cout << " ok " << endl;
	tts = gxx;
	result = 0;
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		number[i] = state % base;
		state /= base;
		if (number[i] < (m / n)) {
			sum += avg;
		} else {
			sum += number[i];
		}
	}
	int rest = m - sum;
	int backup[10];
	for (int i = 1; i <= n; i++) {
		backup[i] = number[i];
	}
	/*for (int i = 1; i <= n; i++) {	
		cout << backup[i] << " " ;
	}*/

	if ((dependent[pos] && pre) || dependent[pos] == 0) {
		for (int i = 1; i <= n; i++) {
			if (backup[i] == avg + 1 || (backup[i] == avg && rest == 0)) {
				continue;
			}
			backup[i]++;
			int nextState = getState(backup);
			double tmp = prob[i][pos] * (1 + dfs(pos + 1, nextState, 1)) + (1 - prob[i][pos]) * dfs(pos + 1, nextState, 0);
			result = max(tmp, result);
			backup[i]--;
		}	
	} else {
		for (int i = 1; i <= n; i++) {
			if (backup[i] == avg + 1 || (backup[i] == avg && rest == 0)) {
				continue;
			}
			backup[i]++;
			int nextState = getState(backup);
			result = max(result, dfs(pos + 1, nextState, 0));
			backup[i]--;
		}
	}
		
	/*cout << pos;
	for (int i = 1; i <= n; i++) {
		cout << " " << backup[i];
	}
	cout << " " << pre << " " << result << endl;*/
	return result;
}

void solve() {
	scanf("%d%d", &n, &m);
	scanf("%d", &k);
	memset(dependent, 0, sizeof dependent);
	base = m / n + 2;
	avg = m / n;
	gxx++;
	int rest = m % avg;
	for (int i = 1; i <= k; i++) {
		int x;
		scanf("%d", &x);
		dependent[x] = 1;
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%lf", &prob[i][j]);
		}
	}
	printf("%.4f\n", dfs(1, 0, 0));
	
}
int main() {
	freopen("H.in", "r", stdin);

	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		printf("Case %d: ", i);
		solve();
	}	
	return 0;
}
/*
Case 1: 4 2 1 0 0
4 2 1 1 0.9
3 2 1 0 0.95
4 1 2 0 0
4 1 2 1 0.1
3 1 2 0 0.95
2 1 2 0 0.95
3 2 0 1 0.95
3 1 1 1 0.95
2 1 1 1 1.755
3 0 2 0 0.55
2 0 2 0 0.95
3 0 2 1 0.55
2 0 2 1 1.395
1 0 2 0 1.3775
1.3775
*/

