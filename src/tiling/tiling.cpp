#include<iostream>
#include<cstring>
#include<algorithm>
#include<sstream>
#include<string>
#include<vector>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<cassert>
#include<numeric>
#include<set>
#include<map>
#include<queue>
#include<list>
#include<deque>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define REP(i,n) FOR(i,0,n)
#define FORE(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define CLEAR(x,with) memset(x,with,sizeof(x))
#define sz size()
typedef long long ll;

const int MOD = 1000000007;
int cache[101];

// 2*width 크기의 사각형을 채우는 방법의 수를 MOD 로 나눈 나머지를 반환한다
int tiling(int width) {
	// 기저 사례: width 가 1 이하일 때
	if(width <= 1) return 1;
	// 메모이제이션
	int& ret = cache[width];
	if(ret != -1) return ret;
	return ret = (tiling(width-2) + tiling(width-1)) % MOD;
}

int main()
{
	memset(cache, -1, sizeof(cache));
	for(int i = 1; i <= 10; ++i)
		cout << i << ": " << tiling(i) << endl;
}
