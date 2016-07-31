#include <bits/stdc++.h>

using namespace std;

int a, v1, v2;
int main()
{
	while(scanf("%d%d%d", &a, &v1, &v2) == 3)
	{
		if(a == 0)
		{
			printf("%.10f\n", 0);
			continue;
		}
		if(v1 <= v2)
		{
			puts("Infinity");
			continue;
		}
		printf("%.10f\n", (double) a * v1 / (v1 * v1 - v2 * v2));
	}
	return 0;
}
