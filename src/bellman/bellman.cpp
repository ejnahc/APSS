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

const int MAX_V = 100;
const int INF = 987654321;

// 정점의 개수
int V; 
// 그래프의 인접 리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<pair<int,int> > adj[MAX_V];

// 음수 사이클이 있을 경우 텅 빈 배열을 반환
vector<int> bellmanFord(int src) {
	// 시작점을 제외한 모든 정점까지의 최단 거리 상한을 INF로 둔다
	vector<int> upper(V, INF);
	upper[src] = 0;
	bool updated;
	// V번 순회한다
	for(int iter = 0; iter < V; ++iter) {
		updated = false;
		for(int here = 0; here < V; ++here)
			for(int i = 0; i < adj[here].size(); i++)  {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				// (here, there) 간선을 따라 완화를 시도한다
				if(upper[there] > upper[here] + cost) {
					// 성공
					upper[there] = upper[here] + cost;
					updated = true;
				}
			}
		// 모든 간선에 대해 완화가 실패할 경우 곧장 종료한다
		if(!updated) break;
	}
	// V번째 순회에서도 완화가 성공했다면 음수 사이클이 있다
	if(updated) upper.clear();
	return upper;
}

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
