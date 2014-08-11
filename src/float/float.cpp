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
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long ll;

bool relativeEqual(double a, double b) {
    return fabs(a-b) < 1e-9 * max(1.0, max(fabs(a), fabs(b)));
}

bool absoluteEqual(double a, double b) {
	return fabs(a-b) < 1e-9;
}

// [1,n] 범위의 자연수 x 에 대해 x * 1.0 / x == x 인 x 의 수를 센다
int countObvious(int n) {
	int same = 0;
	for(int x = 1; x <= 50; ++x) {
		// y = 1 / x
		/*
		double y = 1.0 / x;
		if(y * x == 1.0) same++;
		*/
		double y = 1e20 / x;
		if(absoluteEqual(y*x, 1e20)) ++same;
	}
	return same;
}

int main()
{
    printf("1 / x * x == 1 for %d numbers\n", countObvious(50));
}

