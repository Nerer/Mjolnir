#include <bits/stdc++.h>

std::map<std::string, int> cnt;

void makeList() {
	cnt["Cleveland Cavaliers"] ++;
cnt["Golden State Warriors"] ++;
cnt["San Antonio Spurs"] ++;
cnt["Miami Heat"] ++;
cnt["Miami Heat"] ++;
cnt["Dallas Mavericks"] ++;
cnt["L.A. Lakers"] ++;
cnt["L.A. Lakers"] ++;
cnt["Boston Celtics"] ++;
cnt["San Antonio Spurs"] ++;
cnt["Miami Heat"] ++;
cnt["San Antonio Spurs"] ++;
cnt["Detroit Pistons"] ++;
cnt["San Antonio Spurs"] ++;
cnt["L.A. Lakers"] ++;
cnt["L.A. Lakers"] ++;
cnt["L.A. Lakers"] ++;
cnt["San Antonio Spurs"] ++;
cnt["Chicago Bulls"] ++;
cnt["Chicago Bulls"] ++;
cnt["Chicago Bulls"] ++;
cnt["Houston Rockets"] ++;
cnt["Houston Rockets"] ++;
cnt["Chicago Bulls"] ++;
cnt["Chicago Bulls"] ++;
cnt["Chicago Bulls"] ++;
cnt["Detroit Pistons"] ++;
cnt["Detroit Pistons"] ++;
cnt["L.A. Lakers"] ++;
cnt["L.A. Lakers"] ++;
cnt["Boston Celtics"] ++;
cnt["L.A. Lakers"] ++;
cnt["Boston Celtics"] ++;
cnt["Philadelphia 76ers"] ++;
cnt["L.A. Lakers"] ++;
cnt["Boston Celtics"] ++;
cnt["L.A. Lakers"] ++;
cnt["Seattle Sonics"] ++;
cnt["Washington Bullets"] ++;
cnt["Portland Trail Blazers"] ++;
cnt["Boston Celtics"] ++;
cnt["Golden State Warriors"] ++;
cnt["Boston Celtics"] ++;
cnt["New York Knicks"] ++;
cnt["L.A. Lakers"] ++;
cnt["Milwaukee Bucks"] ++;
cnt["New York Knicks"] ++;
cnt["Boston Celtics"] ++;
cnt["Boston Celtics"] ++;
cnt["Philadelphia 76ers"] ++;
cnt["Boston Celtics"] ++;
cnt["Boston Celtics"] ++;
cnt["Boston Celtics"] ++;
cnt["Boston Celtics"] ++;
cnt["Boston Celtics"] ++;
cnt["Boston Celtics"] ++;
cnt["Boston Celtics"] ++;
cnt["Boston Celtics"] ++;
cnt["St. Louis Hawks"] ++;
cnt["Boston Celtics"] ++;
cnt["Philadelphia Warriors"] ++;
cnt["Syracuse Nats"] ++;
cnt["Minneapolis Lakers"] ++;
cnt["Minneapolis Lakers"] ++;
cnt["Minneapolis Lakers"] ++;
cnt["Rochester Royals"] ++;
cnt["Minneapolis Lakers"] ++;
cnt["Minneapolis Lakers"] ++;
cnt["Baltimore Bullets"] ++;
cnt["Philadelphia Warriors"] ++;
}

int main() {
	freopen("k.in", "r", stdin);
	
	makeList();
	
	int testCnt = 0;
	std::cin >> testCnt;
	scanf("\n");
	for (int i = 1; i <= testCnt; i ++) {
		printf("Case #%d: ", i);
		std::string str;
		std::getline(std::cin, str);
		std::cout << cnt[str] << std::endl;
	}
	
	return 0;
}
