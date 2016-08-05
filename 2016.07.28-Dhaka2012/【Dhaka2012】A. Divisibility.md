A. Divisibility

## 题目大意
在$n(n \le 8)$维坐标上，每个整数坐标上有个值，对于$(x_1, x_2, \ldots, x_n)$，任意一维坐标为负该值都是$0$，$(0, 0, \ldots, 0)$的值为$1$，
其他$(x_1, x_2, \ldots, x_n)$的值是$(x_1 - 1, x_2, \ldots, x_n), (x_1, x_2 - 1, \ldots, x_n), \ldots, (x_1, x_2, \ldots, x_n - 1)$这些值的和。
问在该空间中的某个范围内（对于每一维坐标给出一个范围），有多少个整点上的值能整除质数$p(p \le 20)$。

## 做法
首先需要看出的是，$(x_1, x_2, \ldots, x_n)$的值就是$\frac{(\Sigma{x_i})!}{\Pi{(x_i!)}}$。
令$f(n) = [n / p] + [n / p^2] + \ldots$，即$n!$中$p$的次数。
那么模$p$为$0$等价于$f(\sum{x_i}) = \sum{f(x_i)}$
展开式子可以发现这就等价于$\sum{(x_k~mod~p^r)} < p^r$
由归纳法，这等价于$x_k$在$p$进制下的每一位都不发生进位。
于是可以数位dp求方案数。

## 代码
```c++
#include <bits/stdc++.h>

typedef long long Int64;

const Int64 mod = 1e9 + 9;

Int64 n;
std::vector<Int64> bound[2];
Int64 p;

void init() {
	std::cin >> n >> p;
	bound[0] = bound[1] = std::vector<Int64>();
	for (Int64 t = 0; t <= 1; t ++) {
		for (Int64 i = 1; i <= n; i ++) {
			Int64 x;
			scanf("%lld", &x);
			bound[t].push_back(x - (t == 0));
		}
	}
}

Int64 bit(Int64 state, Int64 y) {
	return (state >> y) & 1;
}

std::vector<Int64> trans(Int64 x) {
	std::vector<Int64> result;
	while (x > 0) {
		result.push_back(x % p);
		x /= p;
	}
	return result;
}

Int64 calc(std::vector<std::vector<Int64> > &vec) {
	Int64 len = 0;
	for (Int64 i = 0; i < (Int64)vec.size(); i ++) {
		len = std::max(len, (Int64)vec[i].size());
	}
	for (Int64 i = 0; i < (Int64)vec.size(); i ++) {
		vec[i].resize(len);
	}
	
	static Int64 f[70][1 << 8];
	
	memset(f, 0, sizeof(f));
	f[len][(1 << n) - 1] = 1;
	
	Int64 result = 0;
	for (Int64 c = len; c >= 0; c --) {
		for (Int64 state = 0; state < (1 << n); state ++) {
			if (f[c][state] == 0) {
				continue;
			}
			if (c == 0) {
				result += f[c][state];
				result %= mod;
				continue;
			}
			
			for (Int64 s = state; ; s = (s - 1) & state) {
				static Int64 g[25];
			
				memset(g, 0, sizeof(g));
			
				g[0] = 1;
				for (Int64 i = 0; i < (Int64)vec.size(); i ++) {
					static Int64 tmp[25];
				
					std::copy(g, g + p, tmp);
					memset(g, 0, sizeof(g));
				
					if (bit(s, i) == 1) {
						for (Int64 j = p - 1; j - vec[i][c - 1] >= 0; j --) {
							g[j] += tmp[j - vec[i][c - 1]];
							g[j] %= mod;
						}
					} else {
						Int64 up = p - 1;
						if (bit(state, i) == 1) {
							up = vec[i][c - 1] - 1;
						}
						for (Int64 k = 0; k <= up; k ++) {
							for (Int64 j = p - 1; j - k >= 0; j --) {
								g[j] += tmp[j - k];
								g[j] %= mod;
							}
						}
					}
				}
				for (Int64 i = 1; i < p; i ++) {
					g[i] += g[i - 1];
					g[i] %= mod;
				}
				f[c - 1][s] += (long long)f[c][state] * g[p - 1] % mod;
				f[c - 1][s] %= mod;
				
				if (s == 0) {
					break;
				}
			}
		}
	}
	return result;
}

void work() {
	Int64 answer = 0;
	for (Int64 state = 0; state < (1 << n); state ++) {
		std::vector<std::vector<Int64> > cur;
		std::vector<Int64> vv;
		bool flag = true;
		for (Int64 i = 0; i < n; i ++) {
			if (bit(state, i) == 0 && bound[0][i] == -1) {
				flag = false;
				break;
			}
			cur.push_back(trans(bound[bit(state, i)][i]));
			vv.push_back(bound[bit(state, i)][i]);
		}
		if (flag == false) {
			continue;
		}
		if (__builtin_popcount(state) % 2 == n % 2) {
			answer += calc(cur);
			answer %= mod;
		} else {
			answer -= calc(cur);
			answer %= mod;
		}
	}
	std::cout << (answer + mod) % mod << std::endl;
}

int main() {
	//freopen("a.in", "r", stdin);
	
	Int64 testCount;
	std::cin >> testCount;
	for (Int64 i = 1; i <= testCount; i ++) {
		printf("Case %lld: ", i);
		init();
		work();
	}
	
	return 0;
}
```