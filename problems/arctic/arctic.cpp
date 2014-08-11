#include<cstring>
#include<iostream>
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

int n;
// 두 기지 사이의 거리
double dist[101][101];
double y[101], x[101];

// 거리 d 이하인 기지들만을 연결했을 때 모든 기지가 연결되는지 여부를 반환한다.
bool decision(double d) {
	vector<bool> visited(n, false);
	visited[0] = true;
	queue<int> q;
	q.push(0);
	int seen = 0;
	while(!q.empty()) {
		int here = q.front();
		q.pop();
		++seen;
		for(int there = 0; there < n; ++there)
			if(!visited[there] && dist[here][there] <= d) {
				visited[there] = true;
				q.push(there);
			}
	}
	return seen == n;
}

// 모든 기지를 연결할 수 있는 최소의 d 를 반환한다.
double optimize() {
	double lo = 0, hi = 1416.00;
	for(int it = 0; it < 100; ++it) {
		double mid = (lo + hi) / 2;
		// mid 가 가능하다면, 더 좋은 (작은) 답을 찾는다.
		if(decision(mid))
			hi = mid;
		// mid 가 불가능하다면, 더 나쁜 (큰) 답을 찾는다.
		else
			lo = mid;
	}
	return hi;
}

int main()
{
	int cases;
	cin >> cases;
	REP(cc,cases)
	{
		cin >> n;
		REP(i,n) cin >> y[i] >> x[i];
		REP(i,n) REP(j,i) dist[i][j] = dist[j][i] = hypot(x[i]-x[j], y[i]-y[j]);
		printf("%.2lf\n", optimize());
	}
}
