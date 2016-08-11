#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
void solve() {
	for (int i = 1; i <= n; i++) {
		scanf("%d", &t[i]);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &d[i]);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			f[i][j] = -1;
		}
	}
	
	vector<pair<int, int> > queue;
	for (int i = 1; i <= n; i++) {
		f[i][i] = 0;
		queue.push_back(make_pair(make_pair(i, i), 0));
	}
	for (int head = 0; head < (int)queue.size(); head++) {
		int l = queue[head].first.first;
		int r = queue[head].first.second;
		int k = queue[head].second;
		int nl = l - 1, nr = r;
		
	}

}
int main() {
	for (; scanf("%d", &n) == 1; solve());
}
