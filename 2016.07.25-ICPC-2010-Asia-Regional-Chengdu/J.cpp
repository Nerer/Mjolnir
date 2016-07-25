#include <bits/stdc++.h>

const int N = 1e4 + 100;
const int ALPHA = 30;

int n, m;
int classSize;
std::vector<int> tea, stu[N];

int w[ALPHA][ALPHA];
int lx[ALPHA], ly[ALPHA];
int left[ALPHA];
bool s[ALPHA], t[ALPHA];

void readVec(std::vector<int>& vec) {
	std::string str;
	std::getline(std::cin, str);
	
	std::stringstream ss;
	
	ss << str;
	
	std::string s;
	while (ss >> s) {
		vec.push_back((int)(s[0] - 'A' + 1));
	}
}

void init() {
	std::cin >> n >> classSize >> m;
	tea.clear();
	std::fill(stu + 1, stu + m + 1, std::vector<int>());
	scanf("\n");
	readVec(tea);
	for (int i = 1; i <= m; i ++) {
		readVec(stu[i]);
	}
}

bool match(int i) {
	s[i] = true;
	for (int j = 1; j <= classSize; j ++) {
		if (lx[i] + ly[j] == w[i][j] && !t[j]) {
			t[j] = true;
			if (!left[j] || match(left[j])) {
				left[j] = i;
				return true;
			}
		}
	}
	return false;
}

void update() {
	int a = 1 << 30;
	int size = classSize;
	for (int i = 1; i <= size; i ++) {
		if (s[i]) {
			for (int j = 1; j <= size; j ++) {
				if (!t[j]) {
					a = std::min(a, lx[i] + ly[j] - w[i][j]);
				}
			}
		}
	}
	for (int i = 1; i <= size; i ++) {
		if (s[i]) {
			lx[i] -= a;
		}
		if (t[i]) {
			ly[i] += a;
		}
	}
}

int km() {
	int size = classSize;
	for (int i = 1; i <= size; i ++) {
		left[i] = lx[i] = ly[i] = 0;
		for (int j = 1; j <= size; j ++) {
			lx[i] = std::max(lx[i], w[i][j]);
		}
	}
	for (int i = 1; i <= size; i ++) {
		while (true) {
			for (int j = 1; j <= size; j ++) {
				s[j] = t[j] = false;
			}
			if (match(i)) {
				break;
			} else {
				update();
			}
		}
	}
	int result = 0;
	for (int i = 1; i <= size; i ++) {
		result += w[left[i]][i];
	}
	return result;
}

void solve(std::vector<int> vec1, std::vector<int> vec2) {
	std::map<int, int> map1, map2;
	int tot1 = 0, tot2 = 0;
	
	memset(w, 0, sizeof(w));
	for (int i = 0; i < (int)vec1.size(); i ++) {
		if (!map1.count(vec1[i])) {
			map1[vec1[i]] = ++tot1;
		}
	}
	for (int i = 0; i < (int)vec2.size(); i ++) {
		if (!map2.count(vec2[i])) {
			map2[vec2[i]] = ++tot2;
		}
	}
	
	for (int i = 0; i < (int)vec1.size(); i ++) {
		w[map2[vec2[i]]][map1[vec1[i]]] ++;
	}
	/*
	printf("tot1 = %d, tot2 = %d\n", tot1, tot2);
	for (int i = 1; i <= classSize; i ++) {
		for (int j = 1; j <= classSize; j ++) {
			printf("%d ", w[i][j]);
		}
		printf("\n");
	}
	*/
	printf("%.4f\n", (double)km() / n);
}

void work() {
	for (int i = 1; i <= m; i ++) {
		solve(tea, stu[i]);
	}
}

int main() {
	freopen("j.in", "r", stdin);
	
	int testCnt;
	std::cin >> testCnt;
	while (testCnt --) {
		init();
		work();
	}
	
	return 0;
}
