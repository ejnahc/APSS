#include<cassert>
#include<cstring>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int MAX_BUDGET = 10000;

int n, m, price[50], pref[50];
int cache[MAX_BUDGET+1];

// budget 만큼의 예산으로 초밥을 먹어서 얻을 수 있는 최대 선호도
int sushi(int budget) {
	// 메모이제이션
	int& ret = cache[budget];
	if(ret != -1) return ret;
	ret = 0;
	for(int dish = 0; dish < n; ++dish) {
		if(budget < price[dish]) continue;
		ret = max(ret, sushi(budget - price[dish]) + pref[dish]);
	}
	return ret;
}

int c[MAX_BUDGET+1];
// sushi() 를 반복적 동적 계획법으로 구현하기
int sushi2() {
	int ret = 0;
	for(int budget = 1; budget <= m; ++budget) {
		c[budget] = 0;
		for(int dish = 0; dish < n; ++dish)
			if(budget >= price[dish])
				c[budget] = max(c[budget],
						c[budget - price[dish]] + pref[dish]);
		ret = max(ret, c[budget]);
	}
	return ret;
}

//int c[201];
int sushi3() {
	int ret = 0;
	c[0] = 0;
	for(int budget = 1; budget <= m; ++budget) {
		int cand = 0;
		for(int dish = 0; dish < n; ++dish)
			if(budget >= price[dish])
				cand = max(cand, c[(budget - price[dish]) % 201] + pref[dish]);
		c[budget % 201] = cand;
		ret = max(ret, cand);
	}
	return ret;
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	cin >> n >> m;
    	for(int i = 0; i < n; i++) {
    		cin >> price[i] >> pref[i];
    		price[i] /= 100;
		}
		m /= 100;
		/*
		memset(cache, -1, sizeof(cache));
		int ret = 0;
		for(int budget = 0; budget <= m; ++budget)
			ret = max(ret, sushi(budget));
		assert(ret == sushi2());
		printf("%d\n", ret);
		*/
		cout << sushi3() << endl;
    }
}

