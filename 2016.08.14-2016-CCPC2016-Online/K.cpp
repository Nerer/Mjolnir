#include <bits/stdc++.h>

const int N = 1e5 + 100;

int n;
char str[N];

void init() {
	scanf("%s", str + 1);
	n = std::strlen(str + 1);
}

void work() {
	static int cnt[30];
	
	memset(cnt, 0, sizeof(cnt));
	
	for (int i = 1; i <= n; i ++) {
		cnt[str[i] - 'a' + 1] ++;
	}
	
	int answer = 0;
	for (int i = 1; i <= 26; i ++) {
		answer += (cnt[i] > 0);
	}
	std::cout << answer << std::endl;
}

int main() {
	freopen("k.in", "r", stdin);
	
	int testCount;
	std::cin >> testCount;
	for (int i = 1; i <= testCount; i ++) {
		printf("Case #%d: ", i);
		init();
		work();
	}
	
	return 0;
}
