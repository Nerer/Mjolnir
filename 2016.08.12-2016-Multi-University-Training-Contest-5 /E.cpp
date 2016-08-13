#include <bits/stdc++.h>

const int N = 1e6 + 10;
const int mod = 1e9 + 7;

int n;
char str[N];

struct PalindromeTree {
	struct Node {
		int fail;
		int len;
		std::pair<int, int> cnt;
		std::list<std::pair<int, int> > child;
	
		Node() {
			child.clear();
		}
		
		Node(int fail, int len):fail(fail), len(len) {
			cnt = std::make_pair(0, 0);
			child.clear();
		}
		
		int getChild(int token) {
			for (std::list<std::pair<int, int> >::iterator it = child.begin(); it != child.end(); it ++) {
				if (it->first == token) {
					return it->second;
				}
			}
			return 0;
		}
	};
	Node node[N];
	short text[N];
	int size;
	int tot;
	
	PalindromeTree() {
		node[1] = Node(0, -1);
		node[2] = Node(1, 0);
		tot = 2;
		size = 0;
		text[0] = -1;
	}
	
	void clear() {
		for (int i = 1; i <= tot; i ++) {
			node[i] = Node();
		}
		node[1] = Node(0, -1);
		node[2] = Node(1, 0);
		tot = 2;
		size = 0;
		text[0] = -1;
	}
	
	int match(int now) {
		while (text[size - node[now].len - 1] != text[size]) {
			now = node[now].fail;
		}
		return now;
	}
	
	bool extend(int &last, int token) {
		text[++size] = token;
		int now = last;
		now = match(now);
		int t = node[now].getChild(token);
		if (t) {
			last = t;
			return false;
		}
		last = ++tot;
		node[now].child.push_back(std::make_pair(token, tot));
		
		node[tot] = Node();
		node[tot].len = node[now].len + 2;
		if (now == 1) {
			node[last].fail = 2;
		} else {
			now = match(node[now].fail);
			node[last].fail = node[now].getChild(token);
		}
		node[last].cnt.first = node[node[last].fail].cnt.first + 1;
		node[last].cnt.second = (node[node[last].fail].cnt.second + node[last].len) % mod;
		return true;
	}
};
PalindromeTree pt;

void work() {
	n = std::strlen(str + 1);
	
	static int pos[N][2];
	static int cnt[N][2][2];
	
	pt.clear();
	pos[0][0] = 2;
	for (int i = 1; i <= n; i ++) {
		pos[i][0] = pos[i - 1][0];
		pt.extend(pos[i][0], str[i] - 'a');
		//printf("%d %d\n", pt[0].node[pos[i][0]].cnt.first, pt[0].node[pos[i][0]].cnt.second);
	}
	for (int i = 1; i <= n; i ++) {
		cnt[i][0][0] = pt.node[pos[i][0]].cnt.first;
		cnt[i][0][1] = pt.node[pos[i][0]].cnt.second;
	}
	
	pt.clear();
	pos[n + 1][1] = 2;
	for (int i = n; i >= 1; i --) {
		pos[i][1] = pos[i + 1][1];
		pt.extend(pos[i][1], str[i] - 'a');
		//printf("%d %d\n", pt[1].node[pos[i][1]].cnt.first, pt[1].node[pos[i][1]].cnt.second);
	}
	for (int i = 1; i <= n; i ++) {
		cnt[i][1][0] = pt.node[pos[i][1]].cnt.first;
		cnt[i][1][1] = pt.node[pos[i][1]].cnt.second;
	}
	
	int answer = 0;
	for (int i = 1; i < n; i ++) {
		int a[2], b[2];
		a[0] = cnt[i][0][0];
		b[0] = cnt[i][0][1];
		
		a[1] = cnt[i + 1][1][0];
		b[1] = cnt[i + 1][1][1];
		
		int t[2];
		t[0] = ((long long)a[0] * (i + 1) % mod - b[0] + mod) % mod;
		t[1] = ((long long)a[1] * i % mod + b[1] + mod) % mod;
		//answer += (a[0] * (i + 1) - b[0]) * (a[1] * i + b[1]);
		answer += (long long)t[0] * t[1] % mod;
		answer %= mod;
	}
	std::cout << answer << std::endl;
}

int main() {
	freopen("e.in", "r", stdin);
	
	while (std::cin >> (str + 1)) {
		work();
	}
	
	return 0;
}
