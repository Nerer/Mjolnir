#include <bits/stdc++.h>

const int N = 25;

int n;
int matrix[N][N];

int bit(int state, int y) {
	return (state >> y) & 1;
}

void init() {
	std::cin >> n;
	for (int i = 0; i < n; i ++) {
		for (int j = 0; j < n; j ++) {
			scanf("%d", &matrix[i][j]);
		}
	}
}

void work() {
	static bool visit[1 << 20];

	std::fill(visit, visit + (1 << n), false);

	std::vector<int> queue;
	
	queue.push_back(0);
	visit[0] = true;
	
	for (int l = 0; l < (int)queue.size(); l ++) {
		int state = queue[l];
		
		std::vector<int> vec;
		for (int i = 0; i < n; i ++) {
			if (bit(state, i) == 0) {
				vec.push_back(i);
			}
		}
		for (int i = 0; i < (int)vec.size(); i ++) {
			int v = vec[i], cntMoney = 0;
			if (visit[state | (1 << v)]) {
				continue;
			}
			for (int j = 0; j < (int)vec.size(); j ++) {
				cntMoney += matrix[vec[j]][v];
			}
			if (cntMoney < 0) {
				visit[state | (1 << v)] = true;
				queue.push_back(state | (1 << v));
			}
		}
	}
	std::vector<int> answer;
	for (int i = 0; i < n; i ++) {
		if (visit[((1 << n) - 1) ^ (1 << i)]) {
			answer.push_back(i + 1);
		}
	}
	if (answer.empty()) {
		printf("0\n");
	} else {
		for (int i = 0; i < (int)answer.size(); i ++) {
			printf("%d%c", answer[i], " \n"[i + 1 == (int)answer.size()]);
		}
	}
}

int main() {
	freopen("a.in", "r", stdin);
	
	int testCount;
	std::cin >> testCount;
	while (testCount --) {
		init();
		work();
	}
	
	return 0;
}
