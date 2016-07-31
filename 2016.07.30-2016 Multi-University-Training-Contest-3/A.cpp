#include <bits/stdc++.h>

std::string str;

void solve() {
	std::stringstream ss[2];
	
	ss[0] << str;
	ss[1] << str;
	
	double x;
	long long y;
	
	ss[0] >> x;
	ss[1] >> y;
	/*
	if (x > 1e12) {
		printf("TAT\n");
		return ;
	}
	*/
	int len = (int)str.length();
	for (int i = 0; i < (int)str.length(); i ++) {
		if (str[i] == 0) {
			len --;
		} else {
			break;
		}
	}
	if (len > 12) {
		printf("TAT\n");
		return ;
	}
	if (y == 0) {
		printf("TAT\n");
		return ;
	}
	
	long long t = 2;
	for (int i = 0; i <= 5; i ++) {
		if (t > y) {
			printf("%d\n", i);
			return ;
		}
		t = t * t;
	}
	printf("TAT\n");
}

int main() {
	freopen("a.in", "r", stdin);
	
	while (std::cin >> str) {
		solve();
	}
	
	return 0;
}
