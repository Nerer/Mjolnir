#include <bits/stdc++.h>

using namespace std;
const int N = 200010;
#define ls o<<1, L ,mid
#define rs o << 1 | 1, mid + 1, R

int n;
map<int, vector<int> >M;
struct Event
{
	int x, y1, y2, add;
	friend bool operator < (const Event &A, const Event &B)
	{
		if(A.x != B.x) return A.x < B.x;
		return A.add > B.add;
	}
};
vector<int>Add[N], Del[N];
Event operation[N * 4];
int add[N * 4], mi[N * 4];
int tot;
pair<int, int> a[N];

void up(int o)
{
	mi[o] = min(mi[o << 1], mi[o << 1 | 1]);
}
void down(int o)
{
	if(add[o])
	{
		add[o << 1] += add[o];
		add[o << 1 | 1] += add[o];
		mi[o << 1] += add[o];
		mi[o << 1 | 1] += add[o];
		add[o] = 0;
	}
}
void sgt_add(int l, int r, int x, int o, int L, int R)
{
	if(l <= L && R <= r)
	{
		mi[o] += x;
		add[o] += x;
		return;
	}
	int mid = L + R >> 1;
	down(o);
	if(r <= mid) sgt_add(l, r, x, ls);
	else if(l > mid) sgt_add(l, r, x, rs);
	else sgt_add(l, mid, x, ls), sgt_add(mid + 1, r, x, rs);
	up(o);
}
int getmin(int l, int r, int o, int L, int R)
{
	if(l <= L && R <= r) return mi[o];
	down(o);
	int mid = L + R >> 1;
	if(r <= mid) return getmin(l, r, ls);
	else if(l > mid) return getmin(l, r, rs);
	else return  min(getmin(l, mid, ls), getmin(mid + 1, r, rs));
}
void solve()
{
	tot = 0;
	for(int k = 1; k <= n; )
	{
		static vector <int> tmp;
		tmp.clear();
		tmp.push_back(0);

		int j;
		for(j = k; j <= n; j++) if(a[k].first == a[j].first)
		{
			tmp.push_back(a[j].second);
		}
		else break;

		tmp.push_back(n + 1);
		int sz = (int)tmp.size();
		{
			for(int i = 0; i < sz - 2; i++)
			{
				Event x1, x2, y1, y2;
				//x1.x = tmp[i + 1];     x1.y1 = tmp[i] + 1; x1.y2 = tmp[i + 1];     x1.add = 1;
				//x2.x = tmp[i + 2] - 1; x2.y1 = tmp[i] + 1; x2.y2 = tmp[i + 1];     x2.add = -1;
				y1.x = tmp[i] + 1;     y1.y1 = tmp[i + 1]; y1.y2 = tmp[i + 2] - 1; y1.add = 1;
				y2.x = tmp[i + 1];     y2.y1 = tmp[i + 1]; y2.y2 = tmp[i + 2] - 1; y2.add = -1;
				
				//operation[++tot] = x1;
				//Add[x1.x].push_back(tot);
				operation[++tot] = y1;
				Add[y1.x].push_back(tot);
				//operation[++tot] = x2;
				//Del[x2.x].push_back(tot);
			    operation[++tot] = y2;
		     	Del[y2.x].push_back(tot);								
			}
		}

		k = j;
	}

	for(int i = 1; i <= n; i++)
	{
		for(int j = 0; j < (int) Add[i].size(); j++)
		{
			Event now = operation[Add[i][j]];
			sgt_add(now.y1, now.y2, 1, 1, 1, n);
		}
		if(getmin(i, n, 1, 1, n) == 0)
		{
			puts("boring");
			return;
		}
		for(int j =0; j < (int) Del[i].size(); j++)
		{
			Event now = operation[Del[i][j]];
			sgt_add(now.y1, now.y2, -1, 1, 1, n);
		}
	}
	puts("non-boring");
}
int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		cin >> n;

		for(int i = 1; i <= 4 * n; i++) mi[i] = add[i] = 0;
		for(int i = 1; i <= n; i++) Add[i].clear(), Del[i].clear();
		for(int i = 1; i <= n + 1; i++) a[i] = make_pair(0, 0);

		for(int i = 1; i <= n; i++)
		{
			scanf("%d", &a[i].first);
			a[i].second = i;
		}
		sort(a + 1, a + n + 1);
		solve();
	}
	return 0;
}
