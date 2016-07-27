#include <bits/stdc++.h>

const int N = 5e4 + 100;

int n;
int q;
int father[N];
int d[N];
std::string str[N];

void init() {
	scanf("\n");
	
	for (int i = 1; i <= q; i ++) {
		std::getline(std::cin, str[i]);
		//std::cout << str[i] << std::endl;
	}
	
}

int find(int u) {
	if (father[u] == u) {
		return u;
	}
	int t = father[u];
	father[u] = find(father[u]);
	d[u] ^= d[t];
	return father[u];
}

bool merge(int u, int v, int w) {
	if (find(u) == find(v)) {
		if ((d[u] ^ d[v]) != w) {
			return false;
		}
	} else {
		int uu = find(u), vv = find(v);
		if (uu < vv) {
			std::swap(u, v);
			std::swap(uu, vv);
		}
		father[uu] = v;
		d[uu] = w ^ d[u];
	}
	return true;
}

void work() {
	for (int i = 0; i <= n; i ++) {
		father[i] = i;
		d[i] = 0;
	}
	int cntI = 0;
	for (int t = 1; t <= q; t ++) {
		std::stringstream ss;
		ss << str[t];

		char cc[10];
		ss >> cc;
		
		std::vector<int> vec;
		int tt;
		while (ss >> tt) {
			vec.push_back(tt);
		}

		if (cc[0] == 'I') {
			cntI ++;
			int u, v, w;
			if ((int)vec.size() == 2) {
				u = vec[0] + 1;
				v = 0;
				w = vec[1];
			} else {
				u = vec[0] + 1;
				v = vec[1] + 1;
				w = vec[2];
			}
			
			if (merge(u, v, w) == false) {
				printf("The first %d facts are conflicting.\n", cntI);
				return ;
			}
		} else {
			std::map<int, int> cnt;
			for (int i = 1; i < (int)vec.size(); i ++) {
				cnt[find(vec[i] + 1)] ++;
			}
			bool flag = true;
			for (std::map<int, int>::iterator it = cnt.begin(); it != cnt.end(); it ++) {
				if (it->first != 0 && it->second % 2 == 1) {
					printf("I don't know.\n");
					flag = false;
					break;
				}
			}
			if (flag == false) {
				continue;
			}
			int answer = 0;
			for (int i = 1; i < (int)vec.size(); i ++) {
				answer ^= d[vec[i] + 1];
			}
			printf("%d\n", answer);
		}
	}
}

int main() {
	freopen("e.in", "r", stdin);

	int testCnt = 0;
	while (std::cin >> n >> q && !(n == 0 && q == 0)) {
		printf("Case %d:\n", ++testCnt);
		init();
		work();
		printf("\n");
	}
	
	return 0;
}
