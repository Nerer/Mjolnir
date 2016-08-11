#include <bits/stdc++.h>

const int N = 55;
const double eps = 1e-8;
const double PI = acos(-1.0);
const int mod = 1e9 + 7;

int dcmp(double x) {
	if (std::abs(x) < eps) {
		return 0;
	} else if (x > 0) {
		return 1;
	} else {
		return -1;
	}
}

int n, m;
int cntColor;
std::pair<int, int> a[N];

struct Point {
	double x, y;
	
	Point() {}
	Point(double x, double y):x(x), y(y) {}
	
	friend Point operator + (const Point &a, const Point &b) {
		return Point(a.x + b.x, a.y + b.y);
	}
	
	friend Point operator - (const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
	}
	
	friend Point operator * (const Point &a, const double b) {
		return Point(a.x * b, a.y * b);
	}
	
	friend bool operator == (const Point &a, const Point &b) {
		return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
	}
	
	Point rotate(double alpha) {
		return Point(x * cos(alpha) - y * sin(alpha), x * sin(alpha) + y * cos(alpha));
	}
	
	double angle() {
		return std::atan2(y, x);
	}
	
	double length2() {
		return x * x + y * y;
	}
};
Point point[N];

int edge[N][N];
std::map<std::pair<int, int>, int> num;

std::vector<std::vector<int> > pmt;

int fastPower(int x, int y) {
	int result = 1;
	for ( ; y; y >>= 1) {
		if (y & 1) {
			result = (long long)result * x % mod;
		}
		x = (long long)x * x % mod;
	}
	return result;
}

double cross(Point a, Point b) {
	return a.x * b.y - a.y * b.x;
}

Point getLineIntersection(Point p, Point v, Point q, Point w) {
	Point u = p - q;
	double t = cross(w, u) / cross(v, w);
	return p + (v * t);
}

void init() {
	std::cin >> n >> m >> cntColor;
	for (int i = 0; i < n; i ++) {
		scanf("%d%d", &a[i].first, &a[i].second);
		point[i] = Point((double)a[i].first, (double)a[i].second);
	}
	memset(edge, 0, sizeof(edge));
	for (int i = 1; i <= m; i ++) {
		int u, v;
		scanf("%d%d", &u, &v);
		u --;
		v --;
		edge[u][v] ++;
		edge[v][u] ++;
	}
}

bool check(Point a, Point b, Point c, Point d, std::vector<int> &tmp) {
	if (a == c || b == d) {
		return false;
	}
	
	double alpha = (d - c).angle() - (b - a).angle();
	
	Point e = (a + b) * 0.5, f = (c + d) * 0.5;
	Point v1 = (b - a).rotate(PI / 2), v2 = (d - c).rotate(PI / 2);
	
	Point o;
	if (e == f) {
		o = e;
	} else {
		o = getLineIntersection(e, v1, f, v2);
	}
	
	tmp.clear();
	for (int i = 0; i < n; i ++) {
		Point vv = point[i] - o;
		vv = vv.rotate(alpha);
		vv = vv + o;
		
		if (dcmp(vv.x - round(vv.x)) != 0 || dcmp(vv.y - round(vv.y)) != 0) {
			return false;
		}
		
		int nx = (int)round(vv.x), ny = (int)round(vv.y);
		if (num.count(std::make_pair(nx, ny)) == 0) {
			return false;
		} else {
			tmp.push_back(num[std::make_pair(nx, ny)]);
		}
	}
	
	for (int i = 0; i < n; i ++) {
		for (int j = 0; j < n; j ++) {
			if (edge[i][j] != edge[tmp[i]][tmp[j]]) {
				return false;
			}
		}
	}
	return true;
}

void work() {
	num.clear();
	for (int i = 0; i < n; i ++) {
		num[a[i]] = i;
	}
	
	pmt.clear();
	for (int i = 0; i < n; i ++) {
		for (int j = 0; j < n; j ++) {
			if (i != j) {
				for (int k = 0; k < n; k ++) {
					for (int l = 0; l < n; l ++) {
						if (k != l && dcmp((point[i] - point[j]).length2() - (point[k] - point[l]).length2()) == 0) {
							std::vector<int> tmp;
							if (check(point[i], point[j], point[k], point[l], tmp)) {
								pmt.push_back(tmp);
							}
						}
					}
				}
			}
		}
	}
	std::vector<int> vec;
	for (int i = 0; i < n; i ++) {
		vec.push_back(i);
	}
	pmt.push_back(vec);
	
	std::sort(pmt.begin(), pmt.end());
	pmt.erase(std::unique(pmt.begin(), pmt.end()), pmt.end());
	
	int answer = 0;
	for (int i = 0; i < (int)pmt.size(); i ++) {
		std::map<int, bool> visit;
		int t = 1;
		
		for (int j = 0; j < (int)pmt[i].size(); j ++) {
			if (!visit[j]) {
				t = (long long)t * cntColor % mod;
				for (int k = j; visit[k] == false; k = pmt[i][k]) {
					visit[k] = true;
				}
			}
		}
		answer += t;
		answer %= mod;
	}
	std::cout << (long long)answer * fastPower((int)pmt.size(), mod - 2) % mod << std::endl;
}

int main() {
	freopen("k.in", "r", stdin);
	
	int testCount;
	std::cin >> testCount;
	while (testCount --) {
		init();
		work();
	}
	
	return 0;
}
