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

// 그래프의 인접 리스트 표현
vector<vector<int> > adj;

// start 에서 시작해 그래프를 너비 우선 탐색하고 각 정점의 방문 순서를 반환한다.
vector<int> bfs(int start) {
	// 각 정점의 방문 여부
	vector<bool> discovered(adj.size(), false);
	// 방문할 정점 목록을 유지하는 큐
	queue<int> q; 
	// 정점의 방문 순서
	vector<int> order;
	discovered[start] = true;
	q.push(start);
	while(!q.empty()) {
		int here = q.front();
		q.pop();		
		// here를 방문한다.
		order.push_back(here);		
		// 모든 인접한 정점을 검사한다.
		for(int i = 0; i < adj[here].size(); i++)  {
			int there = adj[here][i];
			// 처음 보는 정점이면 방문 목록에 집어넣는다.
			if(!discovered[there]) {
				q.push(there);
				discovered[there] = true;
			}
		}
	}	
	return order;
}

// start 에서 시작해 그래프를 너비 우선 탐색하고 시작점부터 각 정점까지의
// 최단 거리와 너비 우선 탐색 신장 트리를 계산한다.
// distance[i] = start 부터 i까지의 최단 거리
// parent[i] = 너비 우선 탐색 신장 트리에서 i의 부모의 번호
void bfs2(int start, vector<int>& distance, vector<int>& parent) {
	distance = vector<int>(adj.size(), -1);
	parent = vector<int>(adj.size(), -1);
	// 방문할 정점 목록을 유지하는 큐
	queue<int> q; 
	distance[start] = 0;
	parent[start] = start;
	q.push(start);
	while(!q.empty()) {
		int here = q.front();
		q.pop();		
		// here의 모든 인접한 정점을 검사한다.
		for(int i = 0; i < adj[here].size(); i++)  {
			int there = adj[here][i];
			// 처음 보는 정점이면 방문 목록에 집어넣는다.
			if(distance[there] == -1) {
				q.push(there);
				distance[there] = distance[here] + 1;
				parent[there] = here;
			}
		}
	}	
}

// v로부터 시작점까지의 최단 경로를 계산한다.
vector<int> shortestPath(int v, const vector<int>& parent) {
	vector<int> path(1, v);
	while(parent[v] != v) {
		v = parent[v];
		path.push_back(v);
	}
	reverse(path.begin(), path.end());
	return path;
}

int main() {
	int v;
	cin >> v;
	adj.resize(v);
	for(int i = 0; i < v; i++) {
		int n;
		cin >> n;
		adj[i].resize(n);
		for(int j = 0; j < n; j++) 
			cin >> adj[i][j];
	}

	printf("bfs()\n");
	vector<int> bfsResult = bfs(0);
	for(int i = 0; i < v; i++) 
		printf("%d ", bfsResult[i]);
	printf("\n");
	printf("bfs2()\n");
	vector<int> distance, parent;
	bfs2(0, distance, parent);
	for(int i = 0; i < v; i++) 
		printf("%d ", distance[i]);
	printf("\n");
	for(int i = 0; i < v; i++) 
		printf("%d ", parent[i]);
	printf("\n");
	for(int i = 0; i < v; i++) {
		vector<int> path = shortestPath(i, parent);
		printf("%d to %d:", 0, i);
		for(int j = 0; j < path.size(); j++)
			printf(" %d", path[j]);
		printf("\n");
	}
}

