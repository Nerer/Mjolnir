#include <bits/stdc++.h>

using namespace std;

char s[200010];
int n;
char t[200010];

void solve()
{
	for(int i = 1; i <= 40; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			bool tmp = 0;
			if(s[j - 1] == '1') tmp ^= 1;
			if(s[j + 1] == '1') tmp ^= 1;
			t[j] = '0' + tmp;
		}
		printf("%s\n", t + 1);
		memcpy(s,t,sizeof t);
	}
}
int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	solve();
	return 0;
}
