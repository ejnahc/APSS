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

const int INF = 987654321;

// 정점의 개수
int V; 
// 그래프의 인접 리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<pair<int,int> > adj[410];

vector<int> dijkstra(int src) {
	vector<int> dist(V, INF);
	dist[src] = 0;
	priority_queue<pair<int, int> > pq;
	pq.push(make_pair(0, src));
	while(!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		// 만약 지금 꺼낸 것보다 더 짧은 경로를 알고 있다면 지금 꺼낸 것을 무시한다
		if(dist[here] < cost) continue;
		printf("visit %d (cost %d)\n", here, cost);
		// 인접한 정점들을 모두 검사한다
		for(int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
			// 더 짧은 경로를 발견하면, dist[] 를 갱신하고 우선 순위 큐에 넣는다
			if(dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
				printf("relaxed %d (cost %d, using %d)\n", there, nextDist, adj[here][i].second);
			}
		}
	}
	return dist;
}

const int START = 401;
// (A국 선수의 예상 시간 - B국 선수의 예상 시간) 의 정점 번호를 반환한다.
int vertex(int delta) {
	 return delta + 200;
}

// a[] = A국 선수의 종목별 예상 시간
// b[] = B국 선수의 종목별 예상 시간
int solve(const vector<int>& a, const vector<int>& b) {
	// 그래프를 만든다. 
	V = 402;
	for(int i = 0; i < V; i++) adj[i].clear();
	for(int i = 0; i < a.size(); i++)  {
		int delta = a[i] - b[i];
		adj[START].push_back(make_pair(vertex(delta), a[i]));
	}
	// 현재 차이
	for(int delta = -200; delta <= 200; ++delta) {		
		// i번 종목을 뒤에 붙인다면?
		for(int i = 0; i < a.size(); ++i) {
			int next = delta + a[i] - b[i];
			// 시간 차이의 절대값이 200을 넘는 정점은 만들 필요가 없다.
			if(abs(next) > 200) continue;
			adj[vertex(delta)].push_back(make_pair(vertex(next), a[i]));
		}
	}
	vector<int> shortest = dijkstra(START);
	int ret = shortest[vertex(0)];
	if(ret == INF) return -1;
	return ret;
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	int m;
    	cin >> m;
    	vector<int> a(m), b(m);
    	for(int i = 0; i < m; i++) 
    		cin >> a[i] >> b[i];
    	int ret = solve(a, b);
    	if(ret == -1)
    		cout << "IMPOSSIBLE" << endl;
		else
			cout << ret << endl;
    }
}

