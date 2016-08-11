#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 5050;
typedef pair<int, LL> pii;

int n;
pii a[N];
int cnt;
int topw, top;

void success()
{
	puts("success.");
}
void maintain()
{
	top = 0;
	for(int i = 1; i <= cnt; i++)
	{
		if(a[i].first == topw)
		{
			top = i;
			break;
		}
	}
	if(top == 0) topw = 0;
}
void to_first(int pos)
{
	pii tmp = a[pos];
	for(int i = pos; i > 1; i--) a[i] = a[i - 1];
	a[1] = tmp;
}
void solve()
{
	char op[10];
	int u;
	for(int i = 1; i <= n; i++)
	{
		printf("Operation #%d: ", i);

		maintain();

		scanf("%s", op);
		if(op[0] != 'U' && op[0] != 'P') scanf("%d", &u);

		if(op[0] == 'A')
		{
			bool flag = 1;
			for(int i = 1; i <= cnt; i++)
			{
				if(a[i].first == u)
				{
					puts("same priority.");
					flag = 0;
					break;
				}
			}
			if(flag)
			{
				a[++cnt] = pii(u, 0);
				success();
			}
		}
		else if(op[0] == 'C' && op[1] == 'l')
		{
			bool flag = 1;
			if(top && a[top].first == u)
			{
				topw = 0;
			}
			for(int i = 1; i <= cnt; i++)
			{
				if(a[i].first == u)
				{
					int x = a[i].first;
					LL y = a[i].second;
					for(int j = i; j < cnt; j++)
					{
						a[j] = a[j + 1];
					}
					cnt--;
					printf("close %d with %I64d.\n", x, y);
					flag = 0;
					break;
				}
			}
			if(flag)
			{
				puts("invalid priority.");
			}
		}
		else if(op[0] == 'C' && op[1] == 'h' && op[2] == 'a')
		{
			if(top)
			{
				a[top].second += u;
				success();
			}
			else
			{
				if(cnt)
				{
					a[1].second += u;
					success();
				}
				else
				{
					puts("empty.");
				}
			}
		}
		else if(op[0] == 'R')
		{
			if(u < 1 || u > cnt)
			{
				puts("out of range.");
			}
			else
			{
				to_first(u);
				success();
			}
		}
		else if(op[0] == 'P')
		{
			if(cnt == 0)
			{
				puts("empty.");
			}
			else
			{
				pii mx = pii(0, 0);
				int pos = 0;
				for(int i = 1; i <= cnt; i++)
				{
					if(a[i] > mx)
					{
						mx = a[i];
						pos = i;
					}
				}

				to_first(pos);
				success();
			}
		}
		else if(op[0] == 'C' && op[1] == 'h' && op[2] == 'o')
		{
			bool flag = 0;
			for(int i = 1; i <= cnt; i++)
			{
				if(a[i].first == u)
				{
					to_first(i);
					flag = 1;
				}
			}
			if(flag)
			{
				success();
			}
			else
			{
				puts("invalid priority.");
			}
		}
		else if(op[0] == 'T')
		{
			bool flag = 0;
			for(int i = 1; i <= cnt; i++)
			{
				if(a[i].first == u)
				{
					topw = u;
					flag = 1;
				}
			}
			if(flag)
			{
				success();
			}
			else
			{
				puts("invalid priority.");
			}
		}
		else
		{
			if(top)
			{
				topw = 0;
				success();
			}
			else
			{
				puts("no such person.");
			}
		}
	}
	
	maintain();

	if(top)
	{
		if(a[top].second)
		{
			printf("Bye %d: %I64d\n", a[top].first, a[top].second);
		}
	}
	for(int i = 1; i <= cnt; i++) if(i != top) if(a[i].second)
	{
		printf("Bye %d: %I64d\n", a[i].first, a[i].second);
	}
}
int main()
{
	//freopen("B.in", "r", stdin);
	int t;
	for(cin >> t; t--; )
	{
		cnt = top = topw = 0;

		cin >> n;
		solve();
	}
	return 0;
}
