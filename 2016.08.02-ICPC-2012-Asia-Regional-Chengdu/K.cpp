#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;
bool ban[11];
int f[11111];
int pre[11111];
int n, m;
int testCnt;
void print(int state) {
	if (state == -1) {
		return;
	}
	print(pre[state]);
	printf("%d", f[state]);
}
void bfs() {
	vector<int> digit;
	for (int i = 0; i < 10; i++) {
		if (!ban[i]) {
			digit.push_back(i);
		}
	}
	for (int i = 0; i < n; i++) {
		f[i] = -1;
	}
	
	for (int i = 0; i < (int)digit.size(); i++) {
		if (digit[i] != 0) {
			if (digit[i] % n == 0) {
				printf("%d\n", digit[i]);
				return;
			}
			int number = digit[i] % n;
			f[digit[i] % n] = digit[i];
			pre[digit[i] % n] = -1;
		}
	}
	vector<int> queue;
	for (int i = 0; i < 10; i++) {
		if (f[i] != -1) {
			queue.push_back(i);
		}
	}
	for (int head = 0; head < (int)queue.size(); head++ ) {
		int now = queue[head];
		for (int k = 0; k < (int)digit.size(); k++) {
			if (f[(now * 10 + digit[k]) % n] == -1) {
				f[(now * 10 + digit[k]) % n] = digit[k];
				pre[(now * 10 + digit[k]) % n] = now;
				if ((now * 10 + digit[k]) % n == 0) {
					print((now * 10 + digit[k]) % n);
					puts("");
					return;
				}
				queue.push_back((now * 10 + digit[k]) % n);
			}
		}
	}
	
	puts("-1");
}
void solve() {
	memset(ban, 0, sizeof ban);
	for (int i = 1; i <= m; i++) {
		int x;
		scanf("%d", &x);
		ban[x] = 1;
	}
	++testCnt;
	printf("Case %d: ", testCnt);
	bfs();
}
int main() {
	for (; scanf("%d%d", &n, &m) == 2; solve());
}
