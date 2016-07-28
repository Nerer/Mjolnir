#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
int n, q, Case;
char tmp[128];
char s[128];
char A[128][128][128];
int cnt[128][128];
int main()
{
	scanf("%d%d", &n, &q);
	scanf("%s", s + 1);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= 16; j++)
		{
			scanf("%s", A[s[i]][j] + 1);
		}
		scanf("%s", tmp);
	}
	while(q--)
	{
		printf("Query %d: ", ++Case);
		scanf("%s", tmp + 1);
		int m = strlen(tmp + 1);

		for(int i = 1; i <= 16; i++)
			for(int j = 1; j <= 43; j++)
				cnt[i][j] = 0;

		for(int k = 1; k <= m; k++)
		{
			for(int i = 1; i <= 16; i++)
				for(int j = 1; j <= 43; j++) if(A[tmp[k]][i][j] == '*')
					cnt[i][j]++;
		}

		for(int k = 1; k <= m; k++)
		{
			bool flag = 0;
			for(int i = 1; i <= 16; i++)
				for(int j = 1; j <= 43; j++) if(A[tmp[k]][i][j] == '*')
				{
					if(cnt[i][j] == 1)
					{
						flag = 1;
						break;
					}
				}
			if(flag) putchar('Y');
			else putchar('N');
		}
		puts("");
	}
	return 0;
}
