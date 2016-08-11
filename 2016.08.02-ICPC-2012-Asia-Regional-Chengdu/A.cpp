#include <bits/stdc++.h>

using namespace std;

int T;
int main()
{
	int n;
	while(~scanf("%d", &n))
	{
		int mx = 0;
		char s[111];
		for(int i = 1; i <= n; i++)
		{
			scanf("%s", s + 1);
			int len = strlen(s + 1);
			int sum = 0;
			for(int i = 1; i <= len; i++) sum += s[i];
			mx = max(mx, sum);
		}
		printf("Case %d: %d\n", ++T, mx);
	}
	return 0;
}
