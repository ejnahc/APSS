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

const int MAX_V = 100;

// 그래프의 인접 행렬 표현
int V;
// capacity[u][v] = u에서 v로 보낼 수 있는 용량
// flow[u][v] = u에서 v로 흘러가는 유량 (반대 방향인 경우 음수)
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];

// flow[][]를 계산하고 총 유량을 반환한다
int networkFlow(int source, int sink) {
  // flow 를 0으로 초기화한다
  memset(flow, 0, sizeof(flow));
  int totalFlow = 0;

  while(true) {
    // 너비 우선 탐색으로 증가 경로를 찾는다
    vector<int> parent(MAX_V, -1);
    queue<int> q;
    parent[source] = source;
    q.push(source);
    while(!q.empty()) {
      int here = q.front(); q.pop();
      for(int there = 0; there < V; ++there)
        // 잔여 용량이 남아 있는 간선을 따라 탐색한다
        if(capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
          q.push(there);
          parent[there] = here;
        }
    }
    // 증가 경로가 없으면 종료한다
    if(parent[sink] == -1) break;
    // 증가 경로를 통해 유량을 얼마나 보낼지 결정한다
    int amount = 987654321;
    for(int p = sink; p != source; p = parent[p])
      amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);
    // 증가 경로를 통해 유량을 보낸다
    for(int p = sink; p != source; p = parent[p]) {
      flow[parent[p]][p] += amount;
      flow[p][parent[p]] -= amount;
    }
    totalFlow += amount;
  }

  return totalFlow;
}

int main() {
  int cases;
  cin >> cases;
  for(int cc = 0; cc < cases; ++cc) {
    int E;
    cin >> V >> E;
    memset(capacity, 0, sizeof(capacity));
    for(int i = 0; i < E; ++i) {
      int a, b, c;
      cin >> a >> b >> c;
      capacity[a][b] = c;
    }
    cout << networkFlow(0, V-1) << endl;
    for(int i = 0; i < V; ++i)
      for(int j = 0; j < V; ++j)
        if(flow[i][j] > 0)
          cout << i << " => " << j << ": " << flow[i][j] << endl;
  }
}

