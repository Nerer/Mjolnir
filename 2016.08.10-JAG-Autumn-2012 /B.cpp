#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
char text1[11], text2[11];
int number[1111];
int occur[111][111];
int sum[16];
int counter[111][111];
vector<int> answer[2];
vector<pair<int, int> > card[2];
pair<int, int> getpair(char s[]) {
	pair<int, int> ret;
	ret.first = number[s[0]];
	if (s[1] >= '0' && s[1] <= '9') {
		ret.second = s[1] - '0' - 1;
	} else {
		if (s[1] == 'A') {
			ret.second = 0;
		} else {
			if (s[1] == 'J') {
				ret.second = 10;
			}
			if (s[1] == 'Q') {
				ret.second = 11;
			}
			if (s[1] == 'K') {
				ret.second = 12;
			}			
			if (s[1] == 'T') {
				ret.second = 9;				
			}
		}
	}
	return ret;
}

vector<int> royal_straight_flush(const vector<pair<int, int> > &player) {
	static vector<pair<int, int> > vec;
	vec = player;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j <= 14; j++) {
			counter[i][j] = 0;
		}
	}
	
	for (int i = 0; i < (int)vec.size(); i++) {
		++counter[vec[i].first][vec[i].second];
	}
	
	for (int i = 0; i < 4; i++) {
		int flg = 1;
		for (int j = 12; j >= 9; j--) {
			if (!counter[i][j]) {
				flg = 0;
			}
		}
		if (!counter[i][0]) {
			flg = 0;
		}
		if (!flg) {
			continue;
		}
		vector<int> ret; 
		ret.push_back(13);
		return ret;
	}
	return vector<int>();
}
vector<int> straight_flush(const vector<pair<int, int> > &player) {
	static vector<pair<int, int> > vec;
	vec = player;
	for (int i = 0; i < (int)vec.size(); i++) {
		if (vec[i].second == 0) {
			vec.push_back(make_pair(vec[i].first, 13));
		}
	}
	sort(vec.begin(), vec.end());
	bool flag = true;
	int best = -1;
	for (int i = 0; i < (int)vec.size() - 5; i++) {
		flag = true;
		for (int j = i; j < i + 5 && j < (int)vec.size(); j++) {
			if (vec[j].first == vec[i].first && vec[j].second - vec[i].second == j - i) {
				continue;
			}
			flag = false;
			break;
		}
		if (flag) {
			if (vec[i].second > best) {
				best = vec[i].second;
			}
		}
	}

	vector<int> ret;
	if (best != -1) {
		ret.push_back(best + 4);	
	}
	return ret;
}

vector<int> four_of_a_kind(const vector<pair<int, int> > &player) {
	for (int i = 0; i <= 14; i++) {
		sum[i] = 0;
	}
	for (int i = 0; i < (int)player.size(); i++) {
		if (player[i].second == 0) {
			sum[13]++;
		} else {
			sum[player[i].second]++;
		}
	}
	vector<int> ret;
	for (int i = 13; i >= 1; i--) {
		if (sum[i] == 4) {
			ret.push_back(i);
			for (int j = 13; j >= 1; j--) {
				if (i != j && sum[j] > 0) {
					ret.push_back(j);
					return ret;
				}
			}
		}
	}
	
	return vector<int>();
} 

vector<int> full_house(const vector<pair<int, int> > &player) {
	for (int i = 0; i <= 14; i++) {
		sum[i] = 0;
	}
	for (int i = 0; i < (int)player.size(); i++) {
		if (player[i].second == 0) {
			sum[13]++;
		} else {
			sum[player[i].second]++;
		}
	}
	
	vector<int> ret;
	for (int i = 13; i >= 1; i--) {
		for (int j = 13; j >= 1; j--) {
			if (i != j) {
				if (sum[i] >= 3 && sum[j] >= 2) {
					ret.push_back(i);
					ret.push_back(j);
					return ret;
				}
			}
			
		}
	}
	
	return ret;
}

vector<int> flush(const vector<pair<int, int> > &player) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j <= 14; j++) {
			counter[i][j] = 0;
		}
	}
	memset(sum, 0, sizeof sum);
	for (int i = 0; i < (int)player.size(); i++) {
		++sum[player[i].first];
		if (player[i].second == 0) {
			++counter[player[i].first][13];
		} else {
			++counter[player[i].first][player[i].second];
		}		
	}
	vector<int> ret;
	for (int i = 0; i < 4; i++) {
		if (sum[i] >= 5) {
			int cnt = 5;
			for (int j = 13; j >= 1; j--) {
				if (counter[i][j]) {
					cnt++;
					ret.push_back(j);
					if (cnt == 5) {
						return ret;
					}
				}
			}
		}
	}
	return ret;
}
vector<int> straight(const vector<pair<int, int> > &player) {
	memset(sum, 0, sizeof sum);
	for (int i = 0; i < (int)player.size(); i++) {
		sum[player[i].second]++;
		if (player[i].second == 0) {
			sum[13]++;
		}
	}
	vector<int> ret;
	for (int i = 13; i >= 4; i--) {
		if (sum[i] && sum[i - 1] && sum[i - 2] && sum[i - 3] && sum[i - 4]) {
			ret.push_back(i);
			return ret;
		}
	}
	return ret;
}

vector<int> three_of_a_kind(const vector<pair<int, int> > &player) {
	memset(sum, 0, sizeof sum);
	for (int i = 0; i < (int)player.size(); i++) {
		sum[player[i].second]++;
		if (player[i].second == 0) {
			sum[13]++;
		}
	}
	
	vector<int> ret; 
	for (int i = 13; i >= 1; i--) {
		if (sum[i] >= 3) {
			ret.push_back(i);
			int cnt = 0;
			for (int j = 13; j >= 1; j--) {
				if (j == i) continue;
				if (sum[j]) {
					ret.push_back(j);
					cnt++;
					if (cnt == 2) {
						return ret;
					}
				}
			}
		}
	}
	return ret;
}

vector<int> two_pairs(const vector<pair<int, int> > &player) {
	memset(sum, 0, sizeof sum);
	for (int i = 0; i < (int)player.size(); i++) {
		sum[player[i].second]++;
		if (player[i].second == 0) {
			sum[13]++;
		}
	}
	
	vector<int> ret;
	for (int i = 13; i >= 1; i--) {
		for (int j = 13; j >= 1; j--) {
			if (sum[i] >= 2 && sum[j] >= 2 && i != j) {
				ret.push_back(i);
				ret.push_back(j);
				for (int k = 13; k >= 1; k--) {
					if (k != i && k != j && sum[k] > 0) {
						ret.push_back(k);
						return ret;
					}
				}
			}			
		}
	}
	
	return ret;
}

vector<int> one_pair(const vector<pair<int, int> > &player) {
	memset(sum, 0, sizeof sum);
	for (int i = 0; i < (int)player.size(); i++) {
		sum[player[i].second]++;
		if (player[i].second == 0) {
			sum[13]++;
		}
	}
	vector<int> ret;
	for (int i = 13; i >= 1; i--) {
		if (sum[i] >= 2) {
			ret.push_back(i);
			for (int j = 13; j >= 1; j--) {
				if (sum[j] && j != i) {
					ret.push_back(j);
				}
				if ((int)ret.size() == 4) {
					return ret;
				}
			}
		}
	}
	return ret;
}
vector<int> high_card(const vector<pair<int, int> > &player) {
	static vector<int> vec;
	vec.clear();
	for (int i = 0; i < (int)player.size(); i++) {
		if (player[i].second == 0) {
			vec.push_back(13);
		} else {
			vec.push_back(player[i].second);
		}
	}
	
	sort(vec.begin(), vec.end());
	
	vector<int> ret;
	int cnt = 0;
	for (int i = (int)vec.size() - 1; i >= 0; i--) {
		cnt++;
		ret.push_back(vec[i]);
		if (cnt == 5) {
			return ret;
		}
	}
	return ret;
}

int check() {
	if (answer[1].size() == 0 && answer[0].size() == 0) {
		return 0;
	}
	if (answer[0].size() == 0) {
		return -1;
	}
	if (answer[1].size() == 0) {
		return 1;
	}
	
	return answer[0] > answer[1] ? 1 : -1;
	
}
int win() {
	static vector<pair<int, int> > player[2];
	player[0] = card[0];
	player[1] = card[1];
	int flg = 0;
	for (int k = 0; k < 2; k++) {	
		answer[k] = royal_straight_flush(player[k]);
	}
	if (flg = check()) {
		return flg > 0;
	}
	
	for (int k = 0; k < 2; k++) {	
		answer[k] = straight_flush(player[k]);
	}
	if (flg = check()) {
		return flg > 0;
	}
	
	for (int k = 0; k < 2; k++) {	
		answer[k] = four_of_a_kind(player[k]);
	}
	if (flg = check()) {
		return flg > 0;
	}
	
	
	for (int k = 0; k < 2; k++) {	
		answer[k] = full_house(player[k]);
		
	}
	
	if (flg = check()) {
		return flg > 0;
	}
	
	
	for (int k = 0; k < 2; k++) {	
		answer[k] = flush(player[k]);
	}
	if (flg = check()) {
		return flg > 0;
	}
	
	for (int k = 0; k < 2; k++) {	
		answer[k] = straight(player[k]);
	}
	if (flg = check()) {
		return flg > 0;
	}
	
	
	for (int k = 0; k < 2; k++) {	
		answer[k] = three_of_a_kind(player[k]);
	}
	if (flg = check()) {
		return flg > 0;
	}
	
	
	for (int k = 0; k < 2; k++) {	
		answer[k] = two_pairs(player[k]);
	}
	if (flg = check()) {
		return flg > 0;
	}
	
	
	for (int k = 0; k < 2; k++) {	
		answer[k] = one_pair(player[k]);
	}
	if (flg = check()) {
		return flg > 0;
	}
	
	for (int k = 0; k < 2; k++) {	
		answer[k] = high_card(player[k]);
	}
	if (flg = check()) {
		return flg > 0;
	}
	return 0;
}

void solve() {
	card[0].clear();
	card[1].clear();
	card[0].push_back(getpair(text1));
	card[0].push_back(getpair(text2));
	scanf("%s%s", text1, text2);
	card[1].push_back(getpair(text1));
	card[1].push_back(getpair(text2));
	
	for (int i = 0; i < 3; i++) {
		scanf("%s", text1);
		card[0].push_back(getpair(text1));
		card[1].push_back(getpair(text1));
	}
	
	memset(occur, 0, sizeof occur);
	for (int i = 0; i < 5; i++) {
		occur[card[0][i].first][card[0][i].second] = 1;
		occur[card[1][i].first][card[1][i].second] = 1;
	}
	double prob = 0;
	double numbers = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			for (int k = 0; k < 4; k++) {
				for (int p = 0; p < 13; p++) {
					if (occur[i][j] == 0 && occur[k][p] == 0) {
						if (i == k && j == p ){
							continue;
						}
						card[0].push_back(make_pair(i, j));
						card[0].push_back(make_pair(k, p));
						card[1].push_back(make_pair(i, j));
						card[1].push_back(make_pair(k, p));
						numbers += 1;
						prob += win();
						for (int rep = 0; rep < 2; rep++) {
							card[0].pop_back();
							card[1].pop_back();
						}
					}
				}
			}
		}
	}

	printf("%.20f\n", prob / numbers);
}

int main() {
	number['S'] = 0;
	number['H'] = 1;
	number['D'] = 2;
	number['C'] = 3;
	for (; scanf("%s%s", text1, text2) == 2 && text1[0] != '#'; solve());
	return 0;
}

