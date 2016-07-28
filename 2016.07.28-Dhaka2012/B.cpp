#include <bits/stdc++.h>

const int N = 300;

std::string str;

void init() {
	std::cin >> str;
}

void work() {
	static int from[N];
	static int degree[N];
	static bool state[N];
	
	memset(from, -1, sizeof(from));
	memset(degree, 0, sizeof(degree));
	memset(state, false, sizeof(state));
	
	int u = str[0];
	state[u] = true;
	from[u] = 0;
	for (int i = 1; i < (int)str.length(); i ++) {
		if (state[str[i]] == false) {
			from[str[i]] = u;
			degree[str[i]] ++;
			degree[u] ++;
			u = str[i];
			state[str[i]] = true;
		} else {
			assert(str[i] == u);
			state[str[i]] = false;
			u = from[u];
		}
	}
	for (int i = 'A'; i <= 'Z'; i ++) {
		if (from[i] != -1) {
			printf("%c = %d\n", i, degree[i]);
		}
	}
}

int main() {
	freopen("b.in", "r", stdin);
	
	int testCount;
	std::cin >> testCount;
	for (int i = 1; i <= testCount; i ++) {
		printf("Case %d\n", i);
		init();
		work();
	}
	
	return 0;
}
