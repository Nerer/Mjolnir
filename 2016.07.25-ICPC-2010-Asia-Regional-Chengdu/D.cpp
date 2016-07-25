#include <bits/stdc++.h>

const double eps = 1e-8;
const double PI = acos(-1.0);

int dcmp(double x) {
	if (std::abs(x) < eps) {
		return 0;
	}
	if (x > 0) {
		return 1;
	}
	return -1;
}

struct Point {
	double x, y;
	
	Point() {}
	Point(double x, double y):x(x), y(y) {}
	
	void init() {
		scanf("%lf%lf", &x, &y);
	}
	
	void print() {
		printf("(%.2f, %.2f)", x, y);
	}
	
	friend Point operator + (const Point &a, const Point &b) {
		return Point(a.x + b.x, a.y + b.y);
	}
	
	friend Point operator - (const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
	}
	
	friend Point operator * (const Point &a, const double &b) {
		return Point(a.x * b, a.y * b);
	}
	
	Point rotate(double alpha) {
		return Point(x * cos(alpha) - y * sin(alpha), y * cos(alpha) + x * sin(alpha));
	}
	
	double length() {
		return std::sqrt(x * x + y * y);
	}
};

double dot(Point a, Point b) {
	return a.x * b.x + a.y * b.y;
}

double cross(Point a, Point b) {
	return a.x * b.y - a.y * b.x;
}

Point getLineIntersection(Point p, Point v, Point q, Point w) {
	Point u = p - q;
	double t = cross(w, u) / cross(v, w);
	return p + v * t;
}

bool onSegment(Point p, Point a1, Point a2) {
	return dcmp(cross(a1 - p, a2 - p)) == 0 && dcmp(dot(a1 - p, a2 - p)) < 0;
}

double getTime(Point p, Point cur, Point dir) {
	if (std::abs(dir.x) > std::abs(dir.y)) {
		return (p.x - cur.x) / dir.x;
	} else {
		return (p.y - cur.y) / dir.y;
	}
}

Point cur, dir;
Point tri[5];
double ref;

void init() {
	Point target;
	cur.init();
	target.init();
	dir = target - cur;
	
	for (int i = 0; i < 3; i ++) {
		tri[i].init();
	}
	
	std::cin >> ref;
}

void work() {
	std::vector<std::pair<Point, Point> > vec; 
	
	for (int i = 0; i < 3; i ++) {
		for (int j = 0; j < 3; j ++) {
			if (i != j) {
				vec.push_back(std::make_pair(tri[i], tri[j]));
			}
		}
	}
	bool inside = false;
	while (true) {
		/*
		printf("cur = ");
		cur.print();
		printf(", dir = ");
		dir.print();
		printf("\n");
		*/
	
		std::vector<std::pair<Point, Point> > newState;
		
		for (int i = 0; i < (int)vec.size(); i ++) {
			Point nor = (vec[i].second - vec[i].first).rotate(PI / 2.0);
			if (dot(nor, dir) > eps) {
				Point np = getLineIntersection(cur, dir, vec[i].first, vec[i].second - vec[i].first);
				if (onSegment(np, vec[i].first, vec[i].second) && getTime(np, cur, dir) > eps) {
					double ss = cross(nor, dir) / dir.length() / nor.length();
					double alpha;
					if (inside) {
						alpha = std::asin(ss * ref);
					} else {
						alpha = std::asin(ss / ref);
					}
					Point nDir = nor.rotate(alpha);
					newState.push_back(std::make_pair(np, nDir));
				}
			}
		}
		if (newState.empty()) {
			if (dir.y > -eps) {
				printf("Error\n");
			} else {
				printf("%.3f\n", getLineIntersection(cur, dir, Point(0, 0), Point(1, 0)).x);
			}
			break;
		}
		
		std::pair<Point, Point> state;
		double dTime = 1e200;
		for (int i = 0; i < (int)newState.size(); i ++) {
			if (getTime(newState[i].first, cur, dir) < dTime) {
				dTime = getTime(newState[i].first, cur, dir);
				state = newState[i];
			}
		}
		cur = state.first;
		dir = state.second;
		inside ^= true;
	}
}

int main() {
	freopen("d.in", "r", stdin);
	
	int testCnt;
	std::cin >> testCnt;
	while (testCnt --) {
		init();
		work();
	}
	
	return 0;
}
