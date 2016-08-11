#include <bits/stdc++.h>

using namespace std;
#define next _next
const int N = 2e6 + 10;

int n, m;
char s[N], t[N];
int next[N];

void solve()
{
	int j = 0;
	int last = 1;
	t[++m] = s[1];
	for(int i = 2; i <= n; i++)
	{
		while(j && s[i] != t[j + 1]) j = next[j];
		if(s[i] == t[j + 1])
		{
			j++;
			if(j == m && i != n)
			{
				last = i;
				j = next[j];
			}
		}
		else if(i != n)
		{
			j = next[m - 1];
			for(int k = last + 1; k <= i; k++)
			{
				t[++m] = s[k];
				while(j && t[j + 1] != s[k]) j = next[j];
				next[m] = j += t[j + 1] == s[k];
			}
			j = 0;
			last = i;
		}
		if(i == n)
		{
			if(j != m)
			{
				for(int i = last + 1; i <= n; i++)
				{
					t[++m] = s[i];
				}
			}
		}
	}
	printf("%d\n", m);
}
int main()
{
	freopen("E.in", "r", stdin);
	int t = 0;
	while(~scanf("%s", s + 1))
	{
		n = strlen(s + 1);
		for(int i = 1; i <= n; i++) next[i] = ::t[i] = 0;
		m = 0;
		printf("Case %d: ", ++t);
		solve();
	}
	return 0;
}
