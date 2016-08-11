#include <bits/stdc++.h>

using namespace std;
typedef vector<int> data;

int x1, x2, x3;
queue <data> q;
int dis[1 << 10], tot;

int NAND(int x, int y)
{
	return (~(x & y)) & ((1 << 8) - 1);
}
int main()
{
	x1 |= 1 << 4;
	x1 |= 1 << 5;
	x1 |= 1 << 6;
	x1 |= 1 << 7;

	x2 |= 1 << 2;
	x2 |= 1 << 3;
	x2 |= 1 << 6;
	x2 |= 1 << 7;

	x3 |= 1 << 1;
	x3 |= 1 << 3;
	x3 |= 1 << 5;
	x3 |= 1 << 7;

	data start;
	start.push_back(x1);
	start.push_back(x2);
	start.push_back(x3);

	q.push(start);

	while(!q.empty())
	{
		data u = q.front(); q.pop();

		bool flag = 0;
		for(int i = 0; i < (int) u.size(); i++)
			for(int j = i; j < (int) u.size(); j++)
			{
				if(tot == (1 << 8)) break;
				int x = NAND(u[i], u[j]);
				if(dis[x]) continue;
				dis[x] = u.size()  - 2;
				data v = u;
				v.push_back(x);
				q.push(v);
				tot++;
				if(tot == (1 << 8))
				{
					flag = 1;
					break;
				}
			}
		if(flag) break;
	}

	int t;
	for(cin >> t; t--; )
	{
		char s[10];
		scanf("%s", s);
		int x = 0;
		for(int i = 0; i < 8; i++) if(s[i] == '1') x |= (1 << 7 - i);
		cout << dis[x] << endl;
	}
	return 0;
}
