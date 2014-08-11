#include<cassert>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// [1,n] 범위에서 2, 3, 5, 7 중 정확히 하나로만 나누어 떨어지는 수의 개수를 반환한다
int count(int n) {
	return (n/2 + n/3 + n/5 + n/7)
		   - 2 * (n/6 + n/10 + n/14 + n/15 + n/21 + n/35)
		   + 3 * (n/30 + n/42 + n/70 + n/105)
		   - 4 * (n/210);
}

const int INT_MAX = 2147483647;

// 2, 3, 5, 7 중 정확히 하나로만 나누어 떨어지는 수 중 k번째의 수를 반환한다
int solve(int k) {
	// 루프 불변 조건: count(lo) < k <= count(hi)
	// 오버플로우를 방지하기 위해 64비트 정수를 사용한다
	long long lo = 0, hi = INT_MAX;
	while(lo + 1 < hi) {
		long long mid = (lo + hi) / 2;
		if(count(mid) < k)
			lo = mid;
		else
			hi = mid;
	}
	return hi;
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	int k;
    	cin >> k;
    	int ret = solve(k);
    	int div = 0;
    	div += (ret % 2 == 0);
    	div += (ret % 3 == 0);
    	div += (ret % 5 == 0);
    	div += (ret % 7 == 0);
    	assert(div == 1);
    	cout << ret << endl;
    }
}

