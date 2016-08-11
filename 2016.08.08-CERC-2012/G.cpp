#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
using namespace std;
const int N = 222222;
int n, color_num;
int nn, mm;
int tree[N];

struct Jewel {
	int x, y, color;
	Jewel() {}
}p[N];


bool cmp(Jewel a, Jewel b) {
	return a.y < b.y;
}

int lowbit(int x) {
	return x & -x;
}

void add(int x) {
	for (int i = x; i <= nn; i += lowbit(i)) {
		tree[i]++;
	}
}
int getsum(int x) {
	int ret = 0;
	for (int i = x; i > 0; i -= lowbit(i)) {
		ret += tree[i];
	}
	return ret;
}
void clearAll() {
	for (int i = 1; i <= n; i++) {
		tree[i] = 0;
	}
}
void solve() {
	scanf("%d%d", &n, &color_num);
	
	clearAll();
	
	vector<int> x, y;
	
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].color);
		x.push_back(p[i].x);
		y.push_back(p[i].y);
	}
	sort(x.begin(), x.end());
	sort(y.begin(), y.end());
	
	x.erase(unique(x.begin(), x.end()), x.end());
	y.erase(unique(y.begin(), y.end()), y.end());


	for (int i = 1; i <= n; i++) {
		p[i].x = lower_bound(x.begin(), x.end(), p[i].x) - x.begin() + 1;
		p[i].y = lower_bound(y.begin(), y.end(), p[i].y) - y.begin() + 1;
	}
		
	nn = x.size();
	mm = y.size();
	
	sort(p + 1, p + n + 1, cmp);
	
	static vector<int> event[N];
	static set<int> position[N];
	
	for (int i = 1; i <= mm; i++) {
		event[i].clear();
	}
	
	for (int i = 1; i <= n; i++) {
		event[p[i].y].push_back(i);
	}
	
	for (int i = 1; i <= color_num; i++) {
		position[i].clear();
		position[i].insert(0);
		position[i].insert(nn + 1);
	}
	
	int answer = 0;
	
	for (int i = 1; i <= mm; i++) {
		for (int j = 0; j < (int)event[i].size(); j++) {
			Jewel now = p[event[i][j]];
			int color = now.color;
			set<int> :: iterator it1, it2;
			it1 = position[color].lower_bound(now.x);
			if (*it1 == now.x) {
				continue;
			}
			it2 = position[color].upper_bound(now.x);
			it1--;
			int l = *it1, r = *it2;
			l++;
			r--;
			answer = max(answer, getsum(r) - getsum(l - 1));
		}
		for (int j = 0; j < (int)event[i].size(); j++) {
			Jewel now = p[event[i][j]];
			int color = now.color;
			position[color].insert(now.x);
			add(now.x);
		}
	}
	
	for (int i = 1; i <= color_num; i++) {
		set<int> :: iterator it = position[i].begin();
		for (; it != position[i].end(); it++) {
			set<int> :: iterator it2 = it;
			it2++;
			if (it2 == position[i].end()) {
				break;
			}
			int l = *it;
			int r = *it2;
			l++;
			r--;	
			answer = max(answer, getsum(r) - getsum(l - 1));
		}
	}
	
	printf("%d\n", answer);
}
int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		solve();
	}
	return 0;
}
