#include <bits/stdc++.h>

using namespace std;

char s[10000010];

int main()
{
	int t = 0;
	while(~scanf("%s", s + 1))
	{
		printf("Case #%d: ", ++t);
		int len = strlen(s + 1);
		int a = 0, b = 0;
		for(int i = 1; i <= len; i++)
		{
			a = (a * 10 + s[i] - '0') % 73;
			b = (b * 10 + s[i] - '0') % 137;
		}
		puts(a == 0 && b == 0 ? "YES": "NO");
	}
	return 0;
}
