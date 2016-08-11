#include <bits/stdc++.h>

const int N = 550;

int n;
std::vector<std::string> eq[N];

std::string all;
std::string queryStr;

std::map<std::string, int> num;
std::string str[150000];
int tot;

std::pair<int, int> son[150000];

int answer[N][2500];

void init() {
	std::cin >> n;
	scanf("\n");
	
	num.clear();
	for (int i = 1; i <= n; i ++) {
		eq[i].clear();
	}
	
	for (int i = 1; i <= n; i ++) {
		std::string cur;
		std::getline(std::cin, cur);
		
		std::stringstream ss;
		ss << cur;
		
		std::string s;
		while (ss >> s) {
			eq[i].push_back(s);
		}
	}
	std::cin >> all >> queryStr;
	
	tot = 0;
	for (int i = 1; i <= n; i ++) {
		for (int j = 0; j < (int)eq[i].size(); j ++) {
			if (num.count(eq[i][j]) == 0) {
				num[eq[i][j]] = ++tot;
				str[tot] = eq[i][j];
			}
		}
		if (eq[i].size() == 3) {
			son[num[eq[i][0]]] = std::make_pair(num[eq[i][2]], 0);
		} else {
			son[num[eq[i][0]]] = std::make_pair(num[eq[i][2]], num[eq[i][4]]);
		}
	}
	
	for (int i = 0; i <= (int)queryStr.length(); i ++) {
		for (int j = 1; j <= tot; j ++) {
			answer[j][i] = -1;
		}
	}
}

int search(int x, int begin) {
	if (x == 0) {
		return begin;
	}
	if (answer[x][begin] != -1) {
		return answer[x][begin];
	}
	if (str[x][0] >= 'a' && str[x][0] <= 'z') {
		int result = begin;
		for (int i = 0; i < (int)str[x].length(); i ++) {
			if (result < (int)queryStr.length() && str[x][i] == queryStr[result]) {
				result ++;
			}
		}
		return answer[x][begin] = result;
	}
	int result = begin;
	result = search(son[x].first, result);
	result = search(son[x].second, result);
	return answer[x][begin] = result;
}

void work() {
	if (search(num[all], 0) == (int)queryStr.length()) {
		printf("YES\n");
	} else {
		printf("NO\n");
	}
}

int main() {
	freopen("e.in", "r", stdin);
	
	int testCount;
	std::cin >> testCount;
	while (testCount --) {
		init();
		work();
	}
	
	return 0;
}
