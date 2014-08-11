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

const int MAX_N = 100;
const int MAX_M = 100;

// A와 B의 정점의 개수
int n, m;

// adj[i][j] = A_i 와 B_j 가 연결되어 있는가?
bool adj[MAX_N][MAX_M];

// 각 정점에 매칭된 상대 정점의 번호를 저장한다.
vector<int> aMatch, bMatch;

// dfs() 의 방문 여부
vector<bool> visited;

// A의 정점인 a에서 B의 매칭되지 않은 정점으로 가는 경로를 찾는다.
bool dfs(int a) {
  if(visited[a]) return false;
  visited[a] = true;
  for(int b = 0; b < m; ++b)
    if(adj[a][b])
      if(bMatch[b] == -1 || dfs(bMatch[b])) {
        // 증가 경로 발견!! a 와 b 를 매치시킨다.
        aMatch[a] = b;
        bMatch[b] = a;
        return true;
      }
  return false;
}

// aMatch, bMatch 배열을 계산하고 최대 매칭의 크기를 반환한다.
int bipartiteMatch() {
  // 처음에는 어떤 정점도 연결되어 있지 않다
  aMatch = vector<int>(n, -1);
  bMatch = vector<int>(m, -1);

  int size = 0;
  for(int start = 0; start < n; ++start) {
    visited = vector<bool>(n, false);
    // 깊이 우선 탐색을 이용해 start에서 시작하는 증가 경로를 찾는다
    if(dfs(start))
      ++size;
  }
  return size;
}

int main() {
  int cases;
  cin >> cases;
  for(int cc = 0; cc < cases; ++cc) {
  }
}

