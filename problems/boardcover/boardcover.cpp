#include<numeric>
#include<algorithm>
#include<cassert>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 주어진 칸을 덮을 수 있는 4가지 방법
// 블록을 구성하는 3칸의 상대적 위치 (dy,dx) 의 목록
const int coverType[4][3][2] = {
  { { 0, 0 }, { 1, 0 }, { 0, 1 } },
  { { 0, 0 }, { 0, 1 }, { 1, 1 } },
  { { 0, 0 }, { 1, 0 }, { 1, 1 } },
  { { 0, 0 }, { 1, 0 }, { 1, -1 } }};

// board 의 (y,x) 를 type 번 방법으로 덮거나, 덮었던 블록을 없앤다.
// delta = 1 이면 덮고, -1 이면 덮었던 블록을 없앤다.
// 만약 블록이 제대로 덮이지 않은 경우 (게임판 밖으로 나가거나,
// 겹치거나, 검은 칸을 덮을 때) false 를 반환한다.
bool set(vector<vector<int> >& board, int y, int x, int type, int delta) {
  bool ok = true;
  for(int i = 0; i < 3; ++i) {
    const int ny = y + coverType[type][i][0];
    const int nx = x + coverType[type][i][1];
    if(ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size())
      ok = false;
    else if((board[ny][nx] += delta) > 1)
      ok = false;
  }
  return ok;
}

// board 의 모든 빈 칸을 덮을 수 있는 방법의 수를 반환한다
// board[i][j] = 1 이미 덮인 칸 혹은 검은 칸
// board[i][j] = 0 아직 덮이지 않은 칸
int cover(vector<vector<int> >& board) {
  // 아직 채우지 못한 칸 중 가장 윗줄 왼쪽에 있는 칸을 찾는다
  int y = -1, x = -1;
  for(int i = 0; i < board.size(); ++i) {
    for(int j = 0; j < board[i].size(); ++j)
      if(board[i][j] == 0) {
        y = i;
        x = j;
        break;
      }
    if(y != -1) break;
  }
  // 기저 사례: 모든 칸을 채웠으면 1을 반환한다
  if(y == -1) return 1;

  int ret = 0;
  for(int type = 0; type < 4; ++type) {
    // 만약 board[y][x] 을 type 형태로 덮을 수 있으면 재귀호출한다
    if(set(board, y, x, type, 1))
      ret += cover(board);
    // 덮었던 블록을 치운다
    set(board, y, x, type, -1);
  }
  return ret;
}

int main() {
  int cases;
  cin >> cases;
  for(int cc = 0; cc < cases; ++cc) {
    int height, width;
    cin >> height >> width;
    assert(1 <= height && height <= 20);
    assert(1 <= width && width <= 20);
    vector<vector<int> > board(height, vector<int>(width, 0));
    int whites = 0;
    for(int i = 0; i < (height); i++) {
      string s;
      cin >> s;
      for(int j = 0; j < (width); j++) {
        if(s[j] == '#')
          board[i][j] = 1;
      }
      whites += count(board[i].begin(), board[i].end(), 0);
    }
    assert(whites <= 50);
    int ways = cover(board);
    cout << ways << endl;
  }
}

