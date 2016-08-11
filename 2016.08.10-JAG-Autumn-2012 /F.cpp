#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

int n;
LL a[100];
LL cnt[100];

void cal(LL n, int x)
{
	for(LL i = ::n - 1; i >= 0; i--)
	{
		if(n >> i & 1)
		{
			for(LL j = i - 1; j >= 0; j--)
			{
				cnt[j] += x * (1LL << i - 1);
			}
			cnt[i] += x * ((n & ((1LL << i) - 1)) + 1);
		}
	}
}
bool check2(LL l, LL r)
{
	for(int i = 0; i <= 64; i++) cnt[i] = 0;
	cal(r, 1);
	cal(l - 1, -1);
	for(int i = 0; i < n; i++) if(a[i] != cnt[i]) return 0;
	return 1;
}
bool check(LL len, LL &A, LL &B)
{
	if(len <= 0) return 0;
	LL retA = 0, retB = 0;
	for(LL i = n - 1; i >= 0; i--)
	{
		if(a[i] == 0)
		{
			continue;
		}
		else if(a[i] == len)
		{
			retA |= 1LL << i;
			retB |= 1LL << i;
		}
		else
		{
			retB |= 1LL << i;
			retB += a[i] - 1;
			retA = retB - len + 1;
			break;
		}
	}

	if(retA >= 1 && retB <= 1000000000000000000LL && check2(retA, retB))
	{
		A = retA;
		B = retB;
		return 1;
	}
	else return 0;
}
void solve()
{
	if(n == 64 && a[n - 1])
	{
		puts("None");
		return;
	}
	else if(n == 64) n--;

	if(n == 63 && a[n - 1])
	{
		puts("None");
		return;
	}
	else if(n == 63) n--;

	LL A = 0, B = 0;
	int cnt = 0;
	for(LL len = 2 * a[0] - 1; len <= 2 * a[0] + 1; len++)
	{
		if(check(len, A, B)) cnt++;
	}
	if(cnt == 0) puts("None");
	else if(cnt > 1) puts("Many");
	else printf("%lld %lld\n", A, B);
}

int main()
{
	while(~scanf("%d", &n))
	{
		if(n == 0) break;
		for(int i = 0; i <= 64; i++) a[i] = cnt[i] = 0;
		for(int i = 0; i < n; i++) scanf("%lld", &a[i]);
		solve();
	}
	return 0;
}
