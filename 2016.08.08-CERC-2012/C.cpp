#include <bits/stdc++.h>

using namespace std;

int n;
char s[55555];
set <string> str;
bool dp[55555];

void init()
{
str.insert("h");
str.insert("he");
str.insert("li");
str.insert("be");
str.insert("b");
str.insert("c");
str.insert("n");
str.insert("o");
str.insert("f");
str.insert("ne");
str.insert("na");
str.insert("mg");
str.insert("al");
str.insert("si");
str.insert("p");
str.insert("s");
str.insert("cl");
str.insert("ar");
str.insert("k");
str.insert("ca");
str.insert("sc");
str.insert("ti");
str.insert("v");
str.insert("cr");
str.insert("mn");
str.insert("fe");
str.insert("co");
str.insert("ni");
str.insert("cu");
str.insert("zn");
str.insert("ga");
str.insert("ge");
str.insert("as");
str.insert("se");
str.insert("br");
str.insert("kr");
str.insert("rb");
str.insert("sr");
str.insert("y");
str.insert("zr");
str.insert("nb");
str.insert("mo");
str.insert("tc");
str.insert("ru");
str.insert("rh");
str.insert("pd");
str.insert("ag");
str.insert("cd");
str.insert("in");
str.insert("sn");
str.insert("sb");
str.insert("te");
str.insert("i");
str.insert("xe");
str.insert("cs");
str.insert("ba");
str.insert("hf");
str.insert("ta");
str.insert("w");
str.insert("re");
str.insert("os");
str.insert("ir");
str.insert("pt");
str.insert("au");
str.insert("hg");
str.insert("tl");
str.insert("pb");
str.insert("bi");
str.insert("po");
str.insert("at");
str.insert("rn");
str.insert("fr");
str.insert("ra");
str.insert("rf");
str.insert("db");
str.insert("sg");
str.insert("bh");
str.insert("hs");
str.insert("mt");
str.insert("ds");
str.insert("rg");
str.insert("cn");
str.insert("la");
str.insert("ac");
str.insert("ce");
str.insert("th");
str.insert("pr");
str.insert("pa");
str.insert("nd");
str.insert("u");
str.insert("pm");
str.insert("np");
str.insert("sm");
str.insert("pu");
str.insert("eu");
str.insert("am");
str.insert("gd");
str.insert("cm");
str.insert("tb");
str.insert("bk");
str.insert("dy");
str.insert("cf");
str.insert("ho");
str.insert("es");
str.insert("fl");
str.insert("er");
str.insert("fm");
str.insert("tm");
str.insert("md");
str.insert("lv");
str.insert("yb");
str.insert("no");
str.insert("lu");
str.insert("lr");
}
void solve()
{
	dp[0] = 1;
	for(int i = 0; i < n; i++) if(dp[i])
	{
		string tmp;
		tmp.clear();
		tmp += s[i + 1];

		if(str.count(tmp))
		{
			dp[i + 1] = 1;
		}

		if(i != n - 1)
		{
			tmp += s[i + 2];
			if(str.count(tmp))
			{
				dp[i + 2] = 1;
			}
		}
	}
	puts(dp[n] ? "YES" : "NO");
}
int main()
{
	init();
	int t;
	cin >> t;
	while(t--)
	{
		scanf("%s", s + 1);
		n = strlen(s + 1);
		for(int i = 0; i <= n; i++) dp[i] = 0;
		solve();
	}
	return 0;
}
