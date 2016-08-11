#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
const int N = 111111;
int n, m;
int a[111], b[111], c[111];
struct Point {
	int x, y;
}p[N];

bool cross(int i, int j) {
	return (1LL * b[i] * a[j] - 1LL * b[j] * a[i]) != 0;
}

void solve() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", &a[i], &b[i], &c[i]);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &p[i].x, &p[i].y);
	}
	vector<string> vec;
	for (int i = 1; i <= m; i++) {
		string state = "";
		for (int j = 1; j <= n; j++) {
			 if (1LL * p[i].x * a[j] + 1LL * b[j] * p[i].y + c[j] > 0) {
			 	state += '1';
			 } else {
			 	state += '0';
			 }
		}
		vec.push_back(state);
	}
	sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
	int area = 1;
	for (int i = 1; i <= n; i++) {
		++area;
		for (int j = i - 1; j >= 1; j--) {
			if (cross(i, j)) {
				++area;
			}
		}
	}
	if (area == (int)vec.size()) {
		printf("PROTECTED\n");
	} else {
		printf("VULNERABLE\n");
	}
}

int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		solve();
	}	
}

