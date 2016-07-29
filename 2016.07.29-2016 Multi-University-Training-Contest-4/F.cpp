#include <bits/stdc++.h>

const int N = 1e5 + 100;
const int ALPHA_SIZE = 30;

int n;
char key, str[N];

struct SuffixAutomation {
	struct Node {
		int trans[ALPHA_SIZE];
		int parent;
		int len;
		
		Node() {
			memset(trans, 0, sizeof(trans));
			parent = len = 0;
		}
	};
	Node node[N << 1];
	int tot;
	
	void clear() {
		for (int i = 1; i <= tot; i ++) {
			node[i] = Node();
		}
		tot = 1;
	}
	
	int extend(int p, int ch) {
		int np = ++tot;
		
		int last = np;
		node[np].len = node[p].len + 1;
		
		for ( ; p && node[p].trans[ch] == 0; p = node[p].parent) {
			node[p].trans[ch] = np;
		}
		if (p == 0) {
			node[np].parent = 1;
		} else {
			int q = node[p].trans[ch];
			if (node[q].len == node[p].len + 1) {
				node[np].parent = q;
			} else {
				int nq = ++tot;
				std::copy(node[q].trans, node[q].trans + ALPHA_SIZE, node[nq].trans);
				node[nq].parent = node[q].parent;
				node[nq].len = node[p].len + 1;
				node[q].parent = node[np].parent = nq;
				for ( ; node[p].trans[ch] == q; p = node[p].parent) {
					node[p].trans[ch] = nq;
				}
			}
		}
		return last;
	}
	
	long long countSubstr() {
		long long result = 0;
		for (int i = 2; i <= tot; i ++) {
			result += node[i].len - node[node[i].parent].len;
		}
		return result;
	}
};
SuffixAutomation sam[2];

void init() {
	char cc[10];
	scanf("%s", cc);
	
	key = cc[0];
	scanf("%s", str + 1);
	n = std::strlen(str + 1);
}

void work() {
	sam[0].clear();
	sam[1].clear();
	
	int last = 1;
	for (int i = 1; i <= n; i ++) {
		last = sam[0].extend(last, str[i] - 'a');
	}
	
	static int trie[N][ALPHA_SIZE], trieTot;
	static int pos[N];
	
	for (int i = 1; i <= trieTot; i ++) {
		for (int j = 0; j < 26; j ++) {
			trie[i][j] = 0;
		}
	}
	
	trieTot = 1;
	pos[1] = 1;
	int cur = 1;
	for (int i = 1; i <= n; i ++) {
		if (str[i] == key) {
			cur = 1;
			continue;
		}
		if (trie[cur][str[i] - 'a'] == 0) {
			pos[++trieTot] = sam[1].extend(pos[cur], str[i] - 'a');
			trie[cur][str[i] - 'a'] = trieTot;
		}
		cur = trie[cur][str[i] - 'a'];
	}
	
	std::cout << sam[0].countSubstr() - sam[1].countSubstr() << std::endl;
}

int main() {
	freopen("f.in", "r", stdin);
	
	int testCount;
	std::cin >> testCount;
	for (int i = 1; i <= testCount; i ++) {
		printf("Case #%d: ", i);
		init();
		work();
	}
	
	return 0;
}
