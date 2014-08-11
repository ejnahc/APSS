#include<cstring>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int MOD = 1000000007;
const int coins[] = { 10, 50, 100, 500 };

// amount 원을 반환하는 방법의 수를 MOD 로 나눈 나머지를 반환한다
// chosen 은 이미 고른 동전들을 담는다
int change(int amount, vector<int>& chosen) {
	// 기저 사례: 모든 돈을 돌려준 경우
	if(amount == 0) return 1;

	int ret = 0;
	for(int next = 0; next < 4; next++)
		if(amount >= coins[next] &&
			(chosen.empty() || chosen.back() <= coins[next])) {

			chosen.push_back(coins[next]);
			ret += change(amount - coins[next], chosen);
			ret %= MOD;
			chosen.pop_back();
		}
	return ret;
}

int cache[100001][4];
// amount 원을 반환하는 방법의 수를 MOD 로 나눈 나머지를 반환한다
// last 는 마지막에 돌려준 동전의 번호를 담는다
int change2(int amount, int last) {
	// 기저 사례: 모든 돈을 돌려준 경우
	if(amount == 0) return 1;
	// 메모이제이션
	int& ret = cache[amount][last];
	if(ret != -1) return ret;

	ret = 0;
	for(int next = last; next < 4; next++)
		if(amount >= coins[next]) {
			ret += change2(amount - coins[next], next);
			ret %= MOD;
		}
	return ret;
}



int main() {
	int cases;
	cin >> cases;
	for(int cc = 0; cc < cases; ++cc) {
		int amt;
		cin >> amt;
		vector<int> c;
		memset(cache, -1, sizeof(cache));
		if(amt < 10000)
			cout << change(amt, c) << " ";
		cout << change2(amt, 0) << endl;
	}
}

