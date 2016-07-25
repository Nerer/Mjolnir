#include <bits/stdc++.h>
using namespace std;
int tmp[30][10][10];
int A[10][10], B[10][10];
struct data
{
	int x1, y1, x2, y2;
	int pre;
	data() {
		pre = -1;
   }
}S;
int sx1,sy1,sx2,sy2;
vector<data>q;
int l;
int vis[10][10][10][10], clk;
const int dx[] = {1, 0, 0, -1};
const int dy[] = {0, -1, 1, 0};
const char ch[] = {'D', 'L', 'R', 'U'};
void get(int x, int y, int k, int &nx, int &ny, int A[10][10])
{
	nx = x;
	ny = y;
	if(k == 0)
	{
		if(A[x][y] >> 1 & 1)
		{
			return;
		}
		else
		{
			nx++;
			return;
		}
	}
	else if(k == 1)
	{
		if(A[x][y] >> 0 & 1)
		{
			return;
		}
		else
		{
			ny--;
			return;
		}
	}
	else if(k == 2)
	{
		if(A[x][y] >> 2 & 1)
		{
			return;
		}
		else
		{
			ny++;
			return;
		}
	}
	else
	{
		if(A[x][y] >> 3 & 1)
		{
			return;
		}
		else
		{
			nx--;
			return;
		}
	}
}
bool check(const data &a)
{
	if(a.x1 < 1 || a.y1 < 1 || a.x1 > 6 || a.y1 > 6) return 0;
	if(a.x2 < 1 || a.y2 < 1 || a.x2 > 6 || a.y2 > 6) return 0;
	if((A[a.x1][a.y1] >> 4 & 1) == 0) return 0;
	if((B[a.x2][a.y2] >> 4 & 1) == 0) return 0;
	if(vis[a.x1][a.y1][a.x2][a.y2] == clk) return 0;
	vis[a.x1][a.y1][a.x2][a.y2] = clk;
	return 1;
}
char cal(int x1,int y1,int x2,int y2,int xx1,int yy1,int xx2,int yy2)
{
	for(int k = 0; k < 4; k++)
	{
		if(x1 + dx[k] == xx1 && y1 + dy[k] == yy1) return ch[k];
		if(x2 + dx[k] == xx2 && y2 + dy[k] == yy2) return ch[k];
	}
}
bool checktarget(data v)
{
	if(!((A[v.x1][v.y1] >> 6 & 1) && (B[v.x2][v.y2] >> 6 & 1))) return 0;
	if (v.pre == -1) {
		puts("");
		return 1;
	}
	data pre = q[v.pre];

	vector<char>ans;
	ans.push_back(cal(pre.x1,pre.y1,pre.x2,pre.y2, v.x1,v.y1,v.x2,v.y2));
	for(int i = v.pre; i != 0; i = q[i].pre)
	{
		v = pre;
		pre = q[v.pre];
		ans.push_back(cal(pre.x1,pre.y1,pre.x2,pre.y2, v.x1,v.y1,v.x2,v.y2));
	}
	for(int i = (int)ans.size() - 1; i >= 0; i--)
	{
		putchar(ans[i]);
	}
	puts("");
	return 1;
}
void input(int id)
{
	q.clear();
	l = 0;
	clk++;

	for(int i = 1; i <= 6; i++)
		for(int j = 1; j <= 6; j++)
		{
			A[i][j] = tmp[id][i][j];
		}
	for(int i = 1; i <= 6; i++)
		for(int j = 1; j <= 6; j++)
		{
			B[i][j] = tmp[id + 1][i][j];
		}
	for(int i = 1; i <= 6; i++)
		for(int j = 1; j <= 6; j++)
		{
			if(A[i][j] >> 5 & 1)
			{
				sx1 = i;
				sy1 = j;
			}
		}
	for(int i = 1; i <= 6; i++)
		for(int j = 1; j <= 6; j++)
		{
			if(B[i][j] >> 5 & 1)
			{
				sx2 = i;
				sy2 = j;
			}
		}
	S.x1 = sx1;
	S.y1 = sy1;
	S.x2 = sx2;
	S.y2 = sy2;
}
void solve()
{
	q.push_back(S);
	check(S);
	S.pre = -1;
	if(checktarget(S)) return;
	l = 0;
	while(l < (int)q.size())
	{
		data u = q[l++];
		int x1, y1, x2, y2;
		x1 = u.x1;
		y1 = u.y1;
		x2 = u.x2;
		y2 = u.y2;
		for(int k = 0; k < 4; k++)
		{
			int nx1, ny1, nx2, ny2;
			get(x1, y1, k, nx1, ny1, A);
			get(x2, y2, k, nx2, ny2, B);
			data v;
			v.x1 = nx1;
			v.y1 = ny1;
			v.x2 = nx2;
			v.y2 = ny2;
			v.pre = l - 1;
			if(!check(v)) continue;
			if(checktarget(v)) return;
			q.push_back(v);
		}
	}
	puts("-1");
}
int main()
{
	int t;
	cin >> t;
	for(int i = 1; i <= t; i++)
	{
		for(int j = 1; j <= 6; j++)
			for(int k = 1; k <= 6; k++)
			{
				scanf("%d", &tmp[i][j][k]);
			}
	}
	for(int i = 1; i < t; i++)
	{
		input(i);
		solve();
	}
	return 0;
}
