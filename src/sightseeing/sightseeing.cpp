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

class Sightseeing {
public:
	// 방문할 수 있는 곳의 개수
	int n;

	// 모든 관광지 간의 소요시간 
	int distance[10][10];

	// 지금 만들 수 있는 경로 중 가장 짧은 것의 길이를 반환한다.
	// here: 현재 위치
	// visited: 각 관광지별 방문 여부
	// curLength: 지금까지 따라온 경로의 길이
	// toPick: 더 방문해야 할 관광지의 수
	int shortestPath(int here, vector<bool>& visited, int curLength, int toPick) {
		// 기저 사례: 이미 경로가 완성되었을 때 현재 길이를 그냥 반환
		if(toPick == 0) return curLength;
		visited[here] = true;
		// 그 외: 다음에 방문할 정점을 결정하고 그 중 가장 작은 것을 반환
		int ret = INT_MAX;
		for(int next = 0; next < n; ++next)
			if(!visited[next]) {
				int cand = shortestPath(next, visited, 
						   curLength + distance[here][next], toPick-1);
				ret = min(ret, cand);
			}
		visited[here] = false;
		return ret;
	}

	// 지금 만들 수 있는 경로 중 가장 짧은 것의 길이를 반환한다.
	// here: 현재 위치
	// visited: 각 관광지별 방문 여부
	// curLength: 지금까지 따라온 경로의 길이
	// toPick: 더 방문해야 할 관광지의 수
	int shortestPath2(int here, vector<bool>& visited, int curLength, int toPick) {
		// 기저 사례: 이미 경로가 완성되었을 때 현재 길이를 그냥 반환
		if(toPick == 0) return curLength;	
		if(here != -1) visited[here] = true;
		// 그 외: 다음에 방문할 정점을 결정하고 그 중 가장 작은 것을 반환
		int ret = INT_MAX;
		for(int next = 0; next < n; ++next)
			if(!visited[next]) {
				int nextLength = curLength;
				if(here != -1) nextLength += distance[here][next];
				int cand = shortestPath(next, visited, nextLength, toPick-1);
				ret = min(ret, cand);
			}
		if(here != -1) visited[here] = false;
		return ret;
	}

	// n 개의 관광지 중 m 개를 방문할 수 있는 최단 시간을 반환한다.
	int visitM(int m)
	{
		int ret = INT_MAX;
		// 모든 시작점에 대해 shortestPath() 를 호출해 보고 최소값을 반환한다 		
		for(int start = 0; start < n; ++start)
		{
			vector<bool> visited(n, false);
			ret = min(ret, shortestPath(start, visited, 0, m-1));
		}
		return ret;
	}
};

int main()
{
	Sightseeing s;
	s.n = 4;
	int weights[4][4] = {{0,4,7,2},{4,0,3,6},{7,3,0,8},{2,6,8,0}};
	for(int i = 0; i < 4; ++i) 
		for(int j = 0; j < 4; ++j)
			s.distance[i][j] = weights[i][j];
	vector<bool> seen(4);
	assert(s.shortestPath(0, seen, 0, 2) == 7);
	assert(s.shortestPath(1, seen, 0, 2) == 6);
	assert(s.shortestPath(2, seen, 0, 2) == 7);
	assert(s.shortestPath(3, seen, 0, 2) == 6);
	assert(s.visitM(3) == 6);
	assert(s.visitM(2) == 2);
	assert(s.visitM(1) == 0);
	for(int i = 3; i >= 1; --i)
		assert(s.visitM(i) == s.shortestPath2(-1, seen, 0, i));
	printf("all tests passed\n");
}
