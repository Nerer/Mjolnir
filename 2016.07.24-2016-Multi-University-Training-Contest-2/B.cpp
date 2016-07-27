#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>

typedef unsigned int UInt;

const UInt N = 1e5 + 100;
const UInt mod = 1e9 + 7;

UInt n;
UInt opt;
UInt value[N];
UInt f[N];
UInt g[1 << 8][1 << 8];
std::vector<UInt> edge[N];

//std::vector<std::pair<UInt*, UInt> > backup;
UInt backup[(1 << 16) + 10][(1 << 8) + 10];
int timeClock;

void init() {
	std::cin >> n;
	
	std::string str;
	std::cin >> str;
	if (str == "AND") {
		opt = 1;
	} else if (str == "OR") {
		opt = 2;
	} else {
		opt = 3;
	}
	
	for (UInt i = 1; i <= n; i ++) {
		scanf("%u", &value[i]);
	}
	std::fill(edge + 1, edge + n + 1, std::vector<UInt>());
	for (UInt i = 2; i <= n; i ++) {
		UInt father;
		scanf("%u", &father);
		edge[father].push_back(i);
	}
}

UInt calc(UInt x, UInt y) {
	if (opt == 1) {
		return x & y;
	} else if (opt == 2) {
		return x | y;
	} else {
		return x ^ y;
	}
}

UInt query(UInt x) {
	UInt a = x >> 8, b = x & ((1 << 8) - 1);
	UInt result = 0;
	for (UInt s = 0; s < (1 << 8); s ++) {
		if (g[a][s] != -1) {
			result = std::max(result, g[a][s] + calc(b, s));
		}
	}
	return result;
}

void add(UInt x, UInt best) {
	UInt a = x >> 8, b = x & ((1 << 8) - 1);
	for (UInt s = 0; s < (1 << 8); s ++) {
		if (g[s][b] == -1 || best + (calc(a, s) << 8) > g[s][b]) {
			g[s][b] = best + (calc(a, s) << 8);
		}
	}
}

void dfs(UInt u) {
	f[u] = query(value[u]);
	
	++timeClock;
	for (int i = 0; i < (1 << 8); i ++) {
		backup[timeClock][i] = g[i][value[u] & ((1 << 8) - 1)];
	}
	
	add(value[u], f[u]);
	for (UInt i = 0; i < (UInt)edge[u].size(); i ++) {
		UInt v = edge[u][i];
		dfs(v);
	}
	
	for (int i = 0; i < (1 << 8); i ++) {
		g[i][value[u] & ((1 << 8) - 1)] = backup[timeClock][i];
	}
	timeClock --;
}

void work() {
	memset(g, -1, sizeof(g));
	
	dfs(1);
	
	UInt answer = 0;
	for (UInt i = 1; i <= n; i ++) {
		//printf("f[%d] = %d\n", i, f[i]);
		answer += (long long)i * (f[i] + value[i]) % mod;
		answer %= mod;
	}
	std::cout << answer << std::endl;
}

int main() {
	//freopen("b.in", "r", stdin);
	//freopen("b.out", "w", stdout);
	
	UInt testCnt;
	std::cin >> testCnt;
	for (int i = 1; i <= testCnt; i ++) {
		init();
		work();
	}
	
	return 0;
}
