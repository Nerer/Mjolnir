#include <bits/stdc++.h>

using namespace std;
const int N = 100010;

char s[N];
int n;

void print(int n)
{
	int a = n / 16, b = n % 16;
	if(a >= 0 && a <= 9) printf("%d", a);
	else
	{
		a -= 10;
		printf("%c", a + 'a');
	}
	if(b >= 0 && b <= 9) printf("%d", b);
	else
	{
		b -= 10;
		printf("%c", b + 'a');
	}

}
void solve()
{
	string str;
	int pos = 0;
	for(int i = 1; i <= n; i += 16)
	{
		str = "";
		print((i - 1) / 256);
		print((i - 1) % 256);

		printf(": ");
		
		for(int j = i; j < i + 16; j++)
		{
			if(j > n) printf("  ");
			else
			{
				char c = s[j];

				print(c);

				if(c >= 'A' && c <= 'Z') c += 'a' - 'A';
				else if(c >= 'a' && c <= 'z') c += 'A' - 'a';

				str += c;
			}
			if(j % 2 == 0) printf(" ");
		}
		cout << str << endl;
	}
}
int main()
{
	while(gets(s + 1))
	{
		n = strlen(s + 1);
		solve();
	}
	return 0;
}
