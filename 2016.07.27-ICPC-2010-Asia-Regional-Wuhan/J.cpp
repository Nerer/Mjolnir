#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

double pi = acos(-1.0), eps = 1e-12;
double sqr(const double & x) {
	return x * x;
}
double ans[2001];
int sign(const double & x) {
	return x < -eps?-1:x > eps;
}
struct Point {
	double x, y;
	Point(){}
	Point(const double & x, const double & y) : x(x), y(y) {}
	void scan() {scanf("%lf%lf", &x, &y);}
	double sqrlen() {return sqr(x) + sqr(y);}
	double len() {return sqrt(sqrlen());}
	Point rev() {return Point(y, -x);}
	void print() {printf("%f %f\n", x, y);}
	Point zoom(const double & d) {double lambda = d / len(); return Point(lambda * x, lambda * y);}
} dvd, a[2001];
Point centre[2001];
double atan2(const Point & x) {
	return atan2(x.y, x.x);
}
Point operator - (const Point & a, const Point & b) {
	return Point(a.x - b.x, a.y - b.y);
}
Point operator + (const Point & a, const Point & b) {
	return Point(a.x + b.x, a.y + b.y);
}
double operator * (const Point & a, const Point & b) {
	return a.x * b.y - a.y * b.x;
}
Point operator / (const Point &a, const double &t) {
	return Point(a.x / t, a.y / t);
}
Point operator * (const double & a, const Point & b) {
	return Point(a * b.x, a * b.y);
}
double operator % (const Point & a, const Point & b) {
	return a.x * b.x + a.y * b.y;
}
struct circle {
	double r; Point o;
	circle() {}
	void scan() {
		o.scan();
		scanf("%lf", &r);
	}
} cir[2001];
struct arc {
	double theta;
	int delta;
	Point p;
	arc() {};
	arc(const double & theta, const Point & p, int d) : theta(theta), p(p), delta(d) {}
} vec[4444];
int nV;
inline bool operator < (const arc & a, const arc & b) {
	return a.theta + eps < b.theta;
}
int cnt;
inline void psh(const double t1, const Point p1, const double t2, const Point p2) {
	if(t2 + eps < t1) 
		cnt++;
	vec[nV++] = arc(t1, p1, 1);
	vec[nV++] = arc(t2, p2, -1);
}
inline double cub(const double & x) {
	return x * x * x;
}
inline void combine(int d, const double & area, const Point & o) {
	if(sign(area) == 0) return;
	centre[d] = 1 / (ans[d] + area) * (ans[d] * centre[d] + area * o);
	ans[d] += area;
}
bool equal(const double & x, const double & y) {
	return x + eps>  y and y + eps > x;
}
bool equal(const Point & a, const Point & b) {
	return equal(a.x, b.x) and equal(a.y, b.y);
}
bool equal(const circle & a, const circle & b) {
	return equal(a.o, b.o) and equal(a.r, b.r);
}
bool f[2001];
Point p[4];
int main() {
	while (1) {
		for (int i = 0; i < 4; i++) {
			p[i].scan();
		}
		bool flag = true;
		for (int i = 0; i < 4; i++) {
			if (sign(p[i].x) == 0 && sign(p[i].x) == 0) {
				continue;
			} else {
				flag = false;
				break;
			}
		}
		if (flag) {
			break;
		}

		int n = 4;
		cir[0].o = (p[0] + p[2]) / 2.; cir[0].r = 0.5 * ((p[0] - p[2]).len());
		cir[1].o = (p[0] + p[3]) / 2.; cir[1].r = 0.5 * ((p[0] - p[3]).len());
		cir[2].o = (p[1] + p[2]) / 2.; cir[2].r = 0.5 * ((p[1] - p[2]).len());
		cir[3].o = (p[1] + p[3]) / 2.; cir[3].r = 0.5 * ((p[1] - p[3]).len());

		fill(ans, ans + n + 1, 0);
		fill(centre, centre + n + 1, Point(0, 0));
		for(int i(0); i < n; i++) {
			dvd = cir[i].o - Point(cir[i].r, 0);
			nV = 0;
			vec[nV++] = arc(-pi, dvd, 1);
			cnt = 0;
			for(int j(0); j < n; j++) if(j != i) {
				double d = (cir[j].o - cir[i].o).sqrlen();
				if(d < sqr(cir[j].r - cir[i].r) + eps) {
					if(cir[i].r + i * eps < cir[j].r + j * eps)
						psh(-pi, dvd, pi, dvd);
				}else if(d + eps < sqr(cir[j].r + cir[i].r)) {
					double lambda = 0.5 * (1 + (sqr(cir[i].r) - sqr(cir[j].r)) / d);
					Point cp(cir[i].o + lambda * (cir[j].o - cir[i].o));
					Point nor((cir[j].o - cir[i].o).rev().zoom(sqrt(sqr(cir[i].r) - (cp - cir[i].o).sqrlen())));
					Point frm(cp + nor);
					Point to(cp - nor);
					psh(atan2(frm - cir[i].o), frm, atan2(to - cir[i].o), to);
				}
			}
			sort(vec + 1, vec + nV);
			vec[nV++] = arc(pi, dvd, -1);
			for(int j = 0; j + 1 < nV; j++) {
				cnt += vec[j].delta;
					double theta(vec[j + 1].theta - vec[j].theta);
					double area(sqr(cir[i].r) * theta * 0.5);
					combine(cnt, area, cir[i].o + 1. / area / 3 * cub(cir[i].r) * Point(sin(vec[j + 1].theta) - sin(vec[j].theta), cos(vec[j].theta) - cos(vec[j + 1].theta)));
					combine(cnt, -sqr(cir[i].r) * sin(theta) * 0.5, 1. / 3 * (cir[i].o + vec[j].p + vec[j + 1].p));
					combine(cnt, vec[j].p * vec[j + 1].p * 0.5, 1. / 3 * (vec[j].p + vec[j + 1].p));
				}
			}
		static int testCount = 0;
		printf("Case %d: %.3f\n\n", ++testCount, ans[1] - ans[4]);
	}
	return 0;
}
