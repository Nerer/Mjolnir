#include <bits/stdc++.h>
using namespace std;
int tt, n, b;
int Case;
struct data
{
	double sz;
	double per;
	double rest;
	bool operator<(const data &B)const
	{
		return rest > B.rest;
	}
}a[23333];
priority_queue<data>q;
bool cmp(const data &A, const data &B)
{
	if(A.sz != B.sz) return A.sz < B.sz;
	return A.rest < B.rest;
}
void input()
{
	for(int i = 1; i <= tt; i++)
	{
		scanf("%lf%lf", &a[i].sz, &a[i].per);
		a[i].per /= 100;
		a[i].rest = a[i].sz * (1 - a[i].per);
	}
}
void solve()
{
	sort(a + 1, a + tt + 1);
	while (!q.empty()) q.pop();
	for(int i = 1; i <= n; i++)
	{
		q.push(a[i]);
	}
	double t = 0;
	int last = n;
	int sum = n;
	double now = 0;
	while(1)
	{
		data u = q.top(); q.pop();
		double speed = (double) b / sum;
		sum--;
		t += (u.rest - now) / speed;
		now = u.rest;
		if(last < tt) {
			a[last + 1].rest += now;
			q.push(a[last + 1]);
			last++;
			sum++;
		}
		if (sum == 0) {
			break;
		}
	}
	printf("Case %d: %.2f\n", ++Case, t);
	puts("");
}
int main()
{
	while(scanf("%d%d%d", &tt, &n, &b) == 3)
	{
		if(tt == 0 && n == 0 && b == 0) break;
		input();
		solve();
	}
	return 0;
}
