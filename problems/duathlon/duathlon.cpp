#include<cstdio>
#include<cassert>
#include<cstring>
#include<map>
#include<set>
#include<time.h>
#include<algorithm>
#include<stack>
#include<queue>
#include<utility>
#include<cmath>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

double t;
vector<double> runSpeed, cycleSpeed;

// 달리기 구간의 길이가 run일 때, i번 선수가 걸리는 시간
double time(int i, double run) {
	double cycle = t - run;
	return run / runSpeed[i] + cycle / cycleSpeed[i];
}

// 달리기 구간 길이가 r일 때, others(r) - cheater(r) 를 반환한다.
double diff(double r) {
	int n = runSpeed.size();
	double cheater = time(n-1, r);
	double others = time(0, r);
	for(int i = 1; i < n-1; ++i) 
		others = min(others, time(i, r));
	return others - cheater;
}

// diff() 함수의 최대값의 위치를 삼분 검색으로 계산한다.
double maxDifference() {
	double lo = 0, hi = t;
	for(int it = 0; it < 100; ++it) {
		double aab = (2*lo + hi) / 3;
		double abb = (lo + 2*hi) / 3;
		if(diff(aab) > diff(abb))
			hi = abb;
		else
			lo = aab;
	}
	return (lo + hi) / 2;
}

int main() {
    while(cin >> t) {
    	int n;
    	cin >> n;
    	runSpeed.resize(n);
    	cycleSpeed.resize(n);
    	for(int i = 0; i < n; ++i) 
    		cin >> runSpeed[i] >> cycleSpeed[i];
    	double ret = maxDifference();
    	double timeDiff = diff(ret);
    	if(timeDiff < 0)
    		printf("The cheater cannot win.\n");
		else
			printf("The cheater can win by %.0lf seconds with r = %.2lfkm and k = %.2lfkm.\n",
					timeDiff * 3600,
					ret,
					t - ret);
    }
}

