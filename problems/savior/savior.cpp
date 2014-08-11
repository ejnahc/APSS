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

const int MAX_V = 220;

// 그래프의 인접 행렬 표현
int V;
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];

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

int n, m;
int wins[20], match[200][2];

// 0번 선수가 총 totalWins 승으로 우승할 수 있는지 여부를 확인한다.
bool canWinWith(int totalWins) {
  // 이미 totalWins승 이상 한 선수가 있으면 안된다
  if(*max_element(wins+1, wins+n) >= totalWins)
    return false;
  // 0번은 소스, 1번은 싱크
  V = 2 + m + n;
  memset(capacity, 0, sizeof(capacity));
  for(int i = 0; i < m; ++i) {
    // 소스에서 각 경기로 가는 간선
    capacity[0][2 + i] = 1;
    // 각 경기에서 두 선수로 가는 간선
    for(int j = 0; j < 2; ++j)
      capacity[2 + i][2 + m + match[i][j]] = 1;
  }
  // 각 선수에서 싱크로, 가능한 최대 승수를 용량으로 하는 간선을 추가
  for(int i = 0; i < n; ++i) {
    int maxWin = (i == 0 ? totalWins : totalWins - 1);
    capacity[2 + m + i][1] = maxWin - wins[i];
  }
  // 이 때 모든 경기에 승자를 지정할 수 있는가?
  return networkFlow(0, 1) == m;
}

int main() {
  int cases;
  cin >> cases;
  for(int cc = 0; cc < cases; ++cc) {
    cin >> n >> m;
    for(int i = 0; i < n; ++i) cin >> wins[i];
    int matches = 0;
    for(int i = 0; i < m; ++i) {
      cin >> match[i][0] >> match[i][1];
      if(match[i][0] == 0 || match[i][1] == 0)
        ++matches;
    }
    bool ok = false;
    for(int m = 0; m <= matches; ++m) {
      if(canWinWith(wins[0] + m)) {
        printf("%d\n", wins[0] + m);
        ok = true;
        break;
      }
    }
    if(!ok) printf("-1\n");
  }
}

