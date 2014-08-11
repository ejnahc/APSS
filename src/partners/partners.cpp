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


class Partners {
public:
	pair<double,double> cache[101];

	double M, D;
	string offer;

	pair<double,double> maxPayoff(int day) {
		if(day == offer.size()) return make_pair(0, 0);
		pair<double,double>& ret = cache[day];
		if(ret.first >= 0) return ret;

		return ret;
	}

	Partner() {
		for(int i = 0; i < 101; ++i) 
			cache[i] = make_pair(-1, -1);
	}
};

int main()
{
	int cases;
	cin >> cases;
	REP(cc,cases)
	{
		fprintf(stderr, "%d of %d ..\r", cc+1, cases);
		printf("Case #%d: ", cc+1);
	}
}
