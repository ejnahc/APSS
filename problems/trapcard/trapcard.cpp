#include<cstdio>
#include<cassert>
#include<cstring>
#include<set>
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

// A에 포함된 정점의 수, B에 포함된 정점의 수
int n, m;
// adj[i][j] = A_i 와 B_j 가 연결되어 있는가?
bool adj[MAX_N][MAX_M];

// 각 정점에 매칭된 상대 정점의 번호를 저장한다.
vector<int> aMatch, bMatch;

// dfs() 의 방문 여부
vector<bool> visited;
//
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

const int MAX_SIZE = 30;

// 기지의 지도
int H, W, id[MAX_SIZE][MAX_SIZE+1];
char map[MAX_SIZE][MAX_SIZE+1];

// (y, x)가 좌표 범위 안에 있는지 확인한다
bool inRange(int y, int x) {
  return 0 <= y && y < H && 0 <= x && x < W;
}

// 이진 그래프를 생성한다
void makeGraph() {
  // 인접한 칸들의 위치
  const int dx[4] = { 1, -1, 0, 0 };
  const int dy[4] = { 0, 0, 1, -1 };

  // 각 칸에 번호를 배정한다
  memset(id, -1, sizeof(id));
  n = m = 0;
  for(int y = 0; y < H; ++y)
    for(int x = 0; x < W; ++x)
      if(map[y][x] == '.') {
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
      if((y1 + x1) % 2 == 0 && map[y1][x1] == '.') {
        // (y1, x1) 의 모든 인접한 칸을 검사한다
        for(int k = 0; k < 4; ++k) {
          int y2 = y1 + dy[k], x2 = x1 + dx[k];
          // (y2, x2) 가 범위 안에 있는 빈 칸이라면 두 정점을 연결한다
          if(inRange(y2, x2) && map[y2][x2] == '.')
            adj[id[y1][x1]][id[y2][x2]] = 1;
        }
      }
}

// aChosen[i] = 최대 독립 집합에 A_i가 포함되었는가?
// bChosen[i] = 최대 독립 집합에 B_i가 포함되었는가?
vector<bool> aChosen, bChosen;

// 이분 그래프의 정보가 주어질 때 실제 최대 독립 집합을 계산한다
void calcMaxIndependentSet() {
  // aMatch[] 와 bMatch[] 를 계산한다
  int C = bipartiteMatch();

  // 1. A의 모든 정점들을 선택하고, B에서 대응되지 않은 정점들을 선택한다
  aChosen = vector<bool>(n, true);
  bChosen = vector<bool>(m, false);
  for(int i = 0; i < m; ++i)
    if(bMatch[i] == -1)
      bChosen[i] = true;

  // 2. 두 정점이 연결되어 있을 경우, 그 중 A의 정점을 지우고 B의 대응된 정점을
  // 대신 선택한다. 더 이상 변화가 일어나지 않을 때까지 반복한다.

  while(true) {
    bool changed = false;
    for(int i = 0; i < n; ++i)
      for(int j = 0; j < m; ++j)
        if(aChosen[i] && bChosen[j] && adj[i][j]) {
          // A는 항상 매칭에 포함된 정점임을 증명할 수 있다
          assert(aMatch[i] != -1);
          aChosen[i] = false;
          bChosen[aMatch[i]] = true;
          changed = true;
        }
    if(!changed) break;
  }
}

void printTraps() {
  // 답을 출력하자
  int C = 0;
  for(int y = 0; y < H; ++y)
    for(int x = 0; x < W; ++x)
      if(map[y][x] == '.')
        if(((y + x) % 2 == 0 && aChosen[id[y][x]]) ||
           ((y + x) % 2 == 1 && bChosen[id[y][x]])) {
          map[y][x] = '^';
          ++C;
        }
  cout << C << endl;
  for(int y = 0; y < H; ++y)
    cout << map[y] << endl;
}

int main() {
  int cases;
  cin >> cases;
  for(int cc = 0; cc < cases; ++cc) {
    cin >> H >> W;
    for(int y = 0; y < H; ++y)
      cin >> map[y];
    makeGraph();
    calcMaxIndependentSet();
    printTraps();
  }
}

