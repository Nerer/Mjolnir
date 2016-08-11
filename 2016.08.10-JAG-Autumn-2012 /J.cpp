#include <bits/stdc++.h>

const int N = 1e5 + 100;

int n;
int lim;
char str[5][N];

void init() {
	scanf("%s%s%s", str[1] + 1, str[2] + 1, str[3] + 1);
}

bool check(int sum[], int left[]) {
	int t[5] = {0, 0, 0, 0, 0};
	
	t[1] += sum[4], t[2] += sum[4], t[3] += sum[4];
	t[1] += sum[1], t[2] += sum[1];
	t[1] += sum[2], t[3] += sum[2];
	t[2] += sum[3], t[3] += sum[3];
	
	if (t[1] > left[1] && t[2] > left[2]) {
		int cur = std::min(t[1] - left[1], t[2] - left[2]);
		cur = std::min(cur, sum[1]);
		t[3] += cur;
		t[1] -= cur;
		t[2] -= cur;
	}
	if (t[1] > left[1] && t[3] > left[3]) {
		int cur = std::min(t[1] - left[1], t[3] - left[3]);
		cur = std::min(cur, sum[2]);
		t[2] += cur;
		t[1] -= cur;
		t[3] -= cur;
	}
	if (t[2] > left[2] && t[3] > left[3]) {
		int cur = std::min(t[2] - left[2], t[3] - left[3]);
		cur = std::min(cur, sum[3]);
		t[1] += cur;
		t[2] -= cur;
		t[3] -= cur;
	}
	
	int tmp = 0;
	for (int i = 1; i <= 3; i ++) {
		tmp += std::max(0, left[i] - t[i]);
	}
	return tmp <= sum[0];
}

void work() {
	int left[5] = {0, n - lim, n - lim, n - lim};
	
	static int cnt[N][5];
	
	memset(cnt[n + 1], 0, sizeof(cnt[n + 1]));
	
	for (int i = n; i >= 1; i --) {
		for (int j = 0; j <= 4; j ++) {
			cnt[i][j] = cnt[i + 1][j];
		}
		if (str[1][i] == str[2][i] && str[1][i] == str[3][i]) {
			cnt[i][4] ++;
		} else if (str[1][i] == str[2][i]) {
			cnt[i][1] ++;
		} else if (str[1][i] == str[3][i]) {
			cnt[i][2] ++;
		} else if (str[2][i] == str[3][i]) {
			cnt[i][3] ++;
		} else {
			cnt[i][0] ++;
		}
	}

	if (check(cnt[1], left) == false) {
		printf("-1\n");
		return ;
	}
	
	std::string answer;
	for (int i = 1; i <= n; i ++) {
		std::vector<char> cd;
		
		cd.push_back('A');
		for (int j = 1; j <= 3; j ++) {
			cd.push_back(str[j][i]);
		}
		std::sort(cd.begin(), cd.end());

		for (int j = 0; j < (int)cd.size(); j ++) {
			for (int k = 1; k <= 3; k ++) {
				left[k] -= (cd[j] == str[k][i]);
			}
			if (check(cnt[i + 1], left)) {
				answer += cd[j];
				break;
			} else {
				for (int k = 1; k <= 3; k ++) {
					left[k] += (cd[j] == str[k][i]);
				}
			}
		}
	}
	printf("%s\n", answer.c_str());
}

int main() {
	freopen("j.in", "r", stdin);

	while (std::cin >> n >> lim && !(n == 0 && lim == 0)) {
		init();
		work();
	}
	
	return 0;
}
