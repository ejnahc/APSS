// polyominoes reference solution by JM

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MOD = 10*1000*1000;
int cache[101][101];

// n개의 정사각형으로 이루어졌고, 맨 위 가로줄에 first 개의
// 정사각형을 포함하는 폴리오미노의 수를 반환한다
int poly(int n, int first)
{
	// 기저 사례: n == first
	if(n == first) return 1;
	// 메모이제이션
	int& ret = cache[n][first];
	if(ret != -1) return ret;

    ret = 0;
    for(int second = 1; second <= n-first; ++second) {
    	int add = second + first - 1;
    	add *= poly(n - first, second);
    	add %= MOD;
    	ret += add;
    	ret %= MOD;
	}
    return ret;
}

int main()
{
    memset(cache, -1, sizeof(cache));

	int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc)
	{
        int n;
        cin >> n;
        int ret = 0;
        for(int i = 0; i < n; i++)
        	(ret += poly(n, i+1)) %= MOD;
        cout << ret << endl;
	}
}
