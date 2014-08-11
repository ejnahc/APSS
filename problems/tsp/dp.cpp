#include<iostream>
#include<cstring>
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
#include<bitset>
#include<time.h>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define REP(i,n) FOR(i,0,n)
#define FORE(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define CLEAR(x,with) memset(x,with,sizeof(x))
#define sz size()
typedef long long ll;

const double INF = 1e200;
const int MAX = 24;

// dp (9장)

vector<string> args;
int n; // 도시의 수
double dist[MAX][MAX]; // 두 도시간의 거리를 저장하는 배열

double* cache[MAX];

// here: 현재 위치
// visited: 각 도시의 방문 여부
// here 에서 시작해 남은 도시들을 방문할 수 있는 최단 경로의 길이를 반환한다.
// 나머지 도시들을 모두 방문하는 경로들 중 가장 짧은 것의 길이를 반환한다
double shortestPath2(int here, int visited) {
  // 기저 사례: 모든 도시를 다 방문했을 때는 0번 도시로 돌아가고 종료한다
  if(visited == (1<<n)-1) return dist[here][0];

  // 메모이제이션
  double& ret = cache[here][visited];
  if(ret > 0) return ret;

  ret = INF; // 매우 큰 값으로 초기화

  // 다음 방문할 도시를 전부 시도해 본다
  for(int next = 0; next < n; ++next) {
    // 이미 방문한 도시인 경우
    if(visited & (1<<next)) continue;

    double cand = dist[here][next] + shortestPath2(next, visited + (1<<next));
    ret = min(ret, cand);
  }

  return ret;
}

#include<sys/wait.h>
#include<unistd.h>

int main(int argc, char* argv[])
{
  int pid = fork();
  if(pid != 0) {
    int status;
    waitpid(pid, &status, 0);
    return 0;
  }
  if(argc > 1) freopen(argv[1], "r", stdin);
  if(argc > 2) freopen(argv[2], "w", stdout);
  for(int i = 0; i < argc; i++) args.push_back(argv[i]);

  int cases;
  cin >> cases;
  int pn = -1;
  REP(cc,cases)
  {
    cin >> n;
    if(pn == -1) {
      for(int i = 0; i < n; i++)
        cache[i] = new double[1<<n];
      pn = n;
    }
    assert(pn == n);
    vector<double> y(n), x(n);
    for(int i = 0; i < n; i++)
      cin >> y[i] >> x[i];
    REP(i,n) REP(j,n) dist[i][j] = hypot(y[i] - y[j], x[i] - x[j]);
    for(int i = 0; i < n; i++)
      memset(cache[i], 0, sizeof(double)*(1<<n));
    double ret = shortestPath2(0, 1);
    printf("%.15lf\n", ret);
  }
}
