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

const int dx[4] = { 1, -1, 0, 0 };
const int dy[4] = { 0, 0, 1, -1 };

bool inRange(int y, int x) {
  return 0 <= y && y < H && 0 <= x && x < W;
}

// 직사각형의 정보
int H, W;
vector<string> board;

// 주어진 직사각형에 도미노를 채울 수 있는지 여부를 반환한다
bool fillDomino() {
  // 각 칸을 표현하는 정점의 번호를 계산한다
  vector<vector<int> > id(H, vector<int>(W, -1));
  // 각 칸을 순회하며 번호를 매긴다
  n = m = 0;
  for(int y = 0; y < H; ++y)
    for(int x = 0; x < W; ++x)
      if(board[y][x] != '#') {
        if((y + x) % 2 == 0)
          id[y][x] = n++;
        else
          id[y][x] = m++;
      }

  // adj[][] 를 채운다
  memset(adj, 0, sizeof(adj));
  // A에 속한 모든 칸에 대해 인접한 칸을 검사한다
  for(int y1 = 0; y1 < H; ++y1)
    for(int x1 = 0; x1 < W; ++x1)
      if((y1 + x1) % 2 == 0 && board[y1][x1] != '#') {
        // (y1, x1) 의 모든 인접한 칸을 검사한다
        for(int k = 0; k < 4; ++k) {
          int y2 = y1 + dy[k], x2 = x1 + dx[k];
          // (y2, x2) 가 범위 안에 있는 빈 칸이라면 두 정점을 연결한다
          if(inRange(y2, x2) && board[y2][x2] != '#')
            adj[id[y1][x1]][id[y2][x2]] = 1;
        }
      }
  // 이분 매칭의 크기가 빈 칸의 수의 절반이어야 한다.
  return bipartiteMatch() * 2 == (n + m);
}

int main() {
  int cases;
  cin >> cases;
  for(int cc = 0; cc < cases; ++cc) {
    cin >> H >> W;
    int empty = 0;
    board.resize(H);
    for(int i = 0; i < H; ++i) {
      cin >> board[i];
      for(int j = 0; j < W; ++j)
        if(board[i][j] == '.')
          empty++;
    }
    if(empty % 2)
      cout << "ODD" << endl;
    else
      cout << (fillDomino() ? "YES" : "NO") << endl;
  }
}

