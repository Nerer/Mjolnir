#include <bits/stdc++.h>

const int N = 20;

int n, m;
std::pair<int, int> a[N * N];
int edge[N];

int lowbit(int state) {
	return state & (-state);
}

int bit(int state, int y) {
	return (state >> y) & 1;
}

void init() {
	std::cin >> n >> m;
	memset(edge, 0, sizeof(edge));
	for (int i = 1; i <= m; i ++) {
		int u, v;
		scanf("%d%d", &u, &v);
		a[i] = std::make_pair(u, v);
		edge[u] |= (1 << v);
		edge[v] |= (1 << u);
	}
}

void work() {
	static int f[1 << N];

	memset(f, 0, sizeof(f));

	f[0] = 0;
	for (int i = 0; i < n; i ++) {
		f[1 << i] = 1;
	}
	for (int state = 0; state < (1 << n); state ++) {
		for (int i = 0; i < n; i ++) {
			if (bit(state, i) && (edge[i] & (state ^ (1 << i))) > 0) {
				f[state] |= f[state ^ (1 << i)];
			}
		}
	}
	/*
	for (int state = 0; state < (1 << n); state ++) {
		if (f[state]) {
			printf("f[");
			std::cout << std::bitset<6>(state);
			printf("] = %d\n", f[state]);
		}
	}
	*/
	for (int state = 0; state < (1 << n); state ++) {
		if (!f[state] || !f[((1 << n) - 1) ^ state]) {
			f[state] = f[((1 << n) - 1) ^ state] = 0;
		}
	}
	for (int i = 0; i < n; i ++) {
		for (int state = 0; state < (1 << n); state ++) {
			if (bit(state, i) == 0) {
				f[state] += f[state | (1 << i)];
			}
		}
	}
	
	for (int i = 1; i <= m; i ++) {
		int u = a[i].first, v = a[i].second;
		printf("%d%c", (f[1 << u] + f[1 << v] - 2 * f[(1 << u) + (1 << v)]) / 2, " \n"[i == m]);
	}
}

int main() {
	//freopen("c.in", "r", stdin);
	
	int testCount;
	std::cin >> testCount;
	for (int i = 1; i <= testCount; i ++) {
		printf("Case #%d: ", i);
		init();
		work();
	}
	
	return 0;
}
