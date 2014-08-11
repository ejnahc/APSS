#include<set>
#include<cstdio>
#include<cassert>
#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int brute(const vector<int>& russian, vector<int> korean) {
	sort(korean.begin(), korean.end());
	int ret = 0;
	do {
		int wins = 0;
		for(int i = 0; i < korean.size(); i++)
			if(korean[i] >= russian[i])
				++wins;
		ret = max(wins, ret);
	} while(next_permutation(korean.begin(), korean.end()));
	return ret;
}

int greedy(const vector<int>& russian, vector<int> korean) {
	int n = russian.size();
	vector<bool> taken(n, false);
	sort(korean.begin(), korean.end(), greater<int>());
	int ret = 0;
	for(int kor = 0; kor < n; kor++) {
		int opponent = -1;
		for(int rus = 0; rus < n; rus++)
			if(!taken[rus] && russian[rus] <= korean[kor] &&
				(opponent == -1 || russian[opponent] <= russian[rus]))
				opponent = rus;
		if(opponent == -1) break;
		++ret;
		taken[opponent] = true;
	}
	return ret;
}

int greedy2(const vector<int>& russian, const vector<int>& korean) {
	int n = russian.size(), wins = 0;
	// 아직 남아 있는 선수들의 레이팅
	multiset<int> ratings(korean.begin(), korean.end());
	for(int rus = 0; rus < n; rus++) {
		// 가장 레이팅이 높은 한국 선수가 이길 수 없는 경우 가장 레이팅이 낮은 선수와 경기시킨다.
		if(*ratings.rbegin() < russian[rus])
			ratings.erase(ratings.begin());
		// 그 외의 경우 이길 수 있는 선수 중 가장 레이팅이 낮은 선수와 경기시킨다.
		else {
			ratings.erase(ratings.lower_bound(russian[rus]));
			++wins;
		}
	}
	return wins;
}

int main() {
	int iter = 0;
	while(true) {
		int n = rand() % 8 + 1;

		vector<int> rus(n), kor(n);
		for(int i = 0; i < n; i++) {
			rus[i] = rand() % 3000;
			kor[i] = rand() % 3000;
		}
		assert(brute(rus, kor) == greedy(rus, kor));
		assert(greedy(rus, kor) == greedy2(rus, kor));
		if(++iter % 1000 == 0) printf("%d ..\n", iter);
	}
}

