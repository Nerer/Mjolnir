#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long LL;
const int N = 1100010;
int n;
int a[N];
LL s1, s2;
long long mgcd(long long x, long long y) {
	if (y == 0) {
		return x;
	} else {
		return mgcd(y, x % y);
	}
}

void input()
{
	s1 = s2 = 0;
	cin >> n;
	for(int i = 1; i <= n; i++)
		{
			scanf("%d", &a[i]);
			if(a[i] < 0) a[i] = -a[i];
			s1 += 1LL * a[i];
			s2 += 1LL * a[i] * a[i];
		}
	}
	void solve()
	{
		LL x, y;
		x = - s1 * s1 + 1LL * n * s2;
		y = n;
		LL d = __gcd(x, y);
		x /= d;
		y /= d;
		cout << x << '/' << y << endl;
	}
	int main()
	{
		int t;
		cin >> t;
		while(t--)
		{
			input();
			solve();
		}
		return 0;
	}
