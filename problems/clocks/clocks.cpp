#include<iostream>
#include<vector>
using namespace std;

const int INF = 9999, SWITCHES = 10, CLOCKS = 16;
const char linked[SWITCHES][CLOCKS+1] = {
// 0123456789012345
  "xxx.............",
  "...x...x.x.x....",
  "....x.....x...xx",
  "x...xxxx........",
  "......xxx.x.x...",
  "x.x...........xx",
  "...x..........xx",
  "....xx.x......xx",
  ".xxxxx..........",
  "...xxx...x...x.."};

bool areAligned(const vector<int>& clocks) {
  for(int i = 0; i < CLOCKS; i++)
    if(clocks[i] % 4 != 0) return false;
  return true;
}

void push(vector<int>& clocks, int swtch) {
  for(int clock = 0; clock < CLOCKS; ++clock)
    if(linked[swtch][clock] == 'x')
      clocks[clock] += 3;
}

int solve(vector<int>& clocks, int swtch) {
  if(swtch == SWITCHES) return areAligned(clocks) ? 0 : INF;
  int ret = INF;
  for(int cnt = 0; cnt < 4; ++cnt) {
    ret = min(ret, cnt + solve(clocks, swtch + 1));
    push(clocks, swtch);
  }
  return ret;
}

int main()
{
  int cases;
  cin >> cases;
  for(int cc = 0; cc < (cases); cc++) {
    vector<int> clocks(16, 0);
    for(int i = 0; i < (16); i++)
      cin >> clocks[i];
    int ret = solve(clocks, 0);
    cout << (ret >= INF ? -1 : ret) << endl;

  }
}

