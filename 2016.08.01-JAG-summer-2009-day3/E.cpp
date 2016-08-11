#include <bits/stdc++.h>

struct Permutation {
	int x[8];
	
	friend bool operator < (const Permutation &a, const Permutation &b) {
		for (int i = 0; i < 8; i ++) {
			if (a.x[i] < b.x[i]) {
				return true;
			} else if (a.x[i] > b.x[i]) {
				return false;
			}
		}
		return false;
	}
	
	friend Permutation operator * (const Permutation &a, const Permutation &b) {
		Permutation result;
		for (int i = 0; i < 8; i ++) {
			result.x[i] = a.x[b.x[i]];
		}
		return result;
	}
	
	void print() {
		for (int i = 0; i < 8; i ++) {
			printf("%d ", x[i]);
		}
		printf("\n");
	}
};

const int trans[3][8] = {
{3, 4, 7, 8, 1, 2, 5, 6}, 
{5, 1, 7, 3, 6, 2, 8, 4},
{3, 1, 4, 2, 7, 5, 8, 6}
};
Permutation tr[3];

std::string str, col[10];
std::map<std::string, int> num;

void prepare() {
	for (int i = 0; i < 3; i ++) {
		for (int j = 0; j < 8; j ++) {
			tr[i].x[j] = trans[i][j] - 1;
		}
	}
}

void init() {
	for (int i = 2; i <= 8; i ++) {
		std::cin >> col[i];
	}
	int tot = 0;
	num.clear();
	for (int i = 1; i <= 8; i ++) {
		if (num.count(col[i]) == 0) {
			num[col[i]] = ++tot;
		}
	}
}

void work() {
	std::vector<Permutation> queue;
	int answer = 0;
	
	int p[9];
	for (int i = 1; i <= 8; i ++) {
		p[i] = i;
	}
	
	std::map<Permutation, bool> visit;
	
	do {
		Permutation cur;
		for (int i = 1; i <= 8; i ++) {
			cur.x[i - 1] = num[col[p[i]]];
		}
		if (visit.count(cur) == 0) {
			answer ++;
			std::vector<Permutation> queue;
			queue.push_back(cur);
			visit[cur] = true;
			for (int l = 0; l < (int)queue.size(); l ++) {
				Permutation u = queue[l];
				//u.print();
				for (int i = 0; i < 3; i ++) {
					Permutation v = u * tr[i];
					if (visit[v] == false) {
						visit[v] = true;
						queue.push_back(v);
					}
				}
			}
		}
	} while (std::next_permutation(p + 1, p + 8 + 1));
	
	std::cout << answer << std::endl;
}

int main() {
	freopen("e.in", "r", stdin);
	
	prepare();
	
	while (std::cin >> col[1]) {
		init();
		work();
	}
	
	return 0;
}
