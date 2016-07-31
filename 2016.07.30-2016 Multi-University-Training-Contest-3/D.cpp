#include <bits/stdc++.h>

const int N = 35;

int n, m;
int a[N][N];
int matrix[N * N][N * N];

const int dir[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

int num(int x, int y) {
	return (x - 1) * m + y;
}

bool checkValid(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= m;
}

void init() {
	std::cin >> n >> m;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			scanf("%d", &a[i][j]);
		}
	}
}

void gauss(int answer[]) {
	for (int i = 1; i <= n * m; i ++) {
		if (matrix[i][i] == 0) {
			bool flag = false;
			for (int j = i + 1; j <= n * m; j ++) {
				if (matrix[j][i]) {
					for (int k = 1; k <= n * m + 1; k ++) {
						std::swap(matrix[i][k], matrix[j][k]);
					}
					flag = true;
					break;
				}
			}
			if (flag == false) {
				continue;
			}
		}
		for (int j = i + 1; j <= n * m; j ++) {
			if (matrix[j][i] != 0) {
				int t = matrix[i][i] * matrix[j][i] % 3;
				for (int k = 1; k <= n * m + 1; k ++) {
					matrix[j][k] -= matrix[i][k] * t % 3;
					matrix[j][k] = (matrix[j][k] + 3) % 3;
				}
			}
		}
		/*
		for (int i = 1; i <= n * m; i ++) {
			for (int j = 1; j <= n * m + 1; j ++) {
				printf("%d ", matrix[i][j]);
			}
			printf("\n");
		}printf("\n");
		*/
	}
	for (int i = n * m; i >= 1; i --) {
		if (matrix[i][i] != 0) {
			answer[i] = matrix[i][n * m + 1] * matrix[i][i] % 3;
		} else {
			answer[i] = 0;
		}
		for (int j = i - 1; j >= 1; j --) {
			matrix[j][n * m + 1] -= matrix[j][i] * answer[i] % 3;
			matrix[j][n * m + 1] = (matrix[j][n * m + 1] + 3) % 3;
		}
	}
}

void work() {
	for (int i = 1; i <= n * m; i ++) {
		for (int j = 1; j <= n * m + 1; j ++) {
			matrix[i][j] = 0;
		}
	}
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			matrix[num(i, j)][num(i, j)] = 2;
			matrix[num(i, j)][n * m + 1] = (3 - a[i][j]) % 3;
			for (int k = 0; k < 4; k ++) {
				int ii = i + dir[k][0], jj = j + dir[k][1];
				if (checkValid(ii, jj)) {
					matrix[num(i, j)][num(ii, jj)] ++;
				}
			}
		}
	}
	
	
	static int answer[N * N];
	gauss(answer);
	
	int cnt = 0;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			for (int k = 1; k <= answer[num(i, j)]; k ++) {
				cnt ++;
				//printf("%d %d\n", i, j);
			}
		}
	}
	std::cout << cnt << std::endl;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			for (int k = 1; k <= answer[num(i, j)]; k ++) {
				printf("%d %d\n", i, j);
			}
		}
	}
}

int main() {
	freopen("d.in", "r", stdin);
	
	int testCount;
	std::cin >> testCount;
	while (testCount --) {
		init();
		work();
	}
	
	return 0;
}
