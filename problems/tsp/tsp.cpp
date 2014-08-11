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
const int MAX = 30;

int n; // 도시의 수
double dist[MAX][MAX]; // 두 도시간의 거리를 저장하는 배열

// 완전 탐색 (6장)

// path: 지금까지 만든 경로
// visited: 각 도시의 방문 여부
// currentLength: 지금까지 만든 경로의 길이
// 나머지 도시들을 모두 방문하는 경로들 중 가장 짧은 것의 길이를 반환한다
double shortestPath(vector<int>& path, vector<bool>& visited, double currentLength) {
  // 기저 사례: 모든 도시를 다 방문했을 때는 0번 도시로 돌아가고 종료한다
  if(path.size() == n)
    return currentLength + dist[0][path.back()];

  double ret = INF; // 매우 큰 값으로 초기화

  // 다음 방문할 도시를 전부 시도해 본다
  for(int next = 0; next < n; ++next) {
    if(visited[next]) continue;
    int here = path.back();

    path.push_back(next);
    visited[next] = true;

    // 나머지 경로를 재귀호출을 통해 완성하고 가장 짧은 경로의 길이를 얻는다
    double cand = shortestPath(path, visited, currentLength + dist[here][next]);
    ret = min(ret, cand);

    visited[next] = false;
    path.pop_back();
  }

  return ret;
}

// dp (9장)

/*
   double cache[MAX][1<<MAX];

// here: 현재 위치
// visited: 각 도시의 방문 여부
// here 에서 시작해 남은 도시들을 방문할 수 있는 최단 경로의 길이를 반환한다.
// 나머지 도시들을 모두 방문하는 경로들 중 가장 짧은 것의 길이를 반환한다
double shortestPath2(int here, int visited) {
// 기저 사례: 모든 도시를 다 방문했을 때는 0번 도시로 돌아가고 종료한다
if(visited == (1<<n)-1) return dist[here][0];

// 메모이제이션
double& ret = cache[here][visited];
if(ret >= 0) return ret;

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
*/
// 조합 탐색 (11장)

// 각 정점에 인접한 간선 중 가장 짧은 것을 미리 찾아 둔다
double minEdge[MAX];

// 순간이동할 수 있다는 가정을 이용한 휴리스틱
double simpleHeuristic(vector<bool>& visited) {
  double ret = minEdge[0];
  for(int i = 0; i < n; i++)
    if(!visited[i])
      ret += minEdge[i];
  return ret;
}

// 각 정점마다 다른 정점들을 가까운 순서대로 정렬해 둔다
vector<int> nearest[MAX];

// path 의 마지막 4개의 정점 중 가운데 2개의 순서를 바꿨을 때 경로가 더 짧아지는지 여부를 반환한다
bool pathSwapPruning(const vector<int>& path) {
  if(path.size() < 4) return false;
  int p = path[path.size() - 4];
  int a = path[path.size() - 3];
  int b = path[path.size() - 2];
  int q = path[path.size() - 1];

  return dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q];
}

// 시작 도시와 현재 도시를 제외한 path 의 부분 경로를
// 뒤집어 보고 더 짧아지는지 확인한다
bool pathReversePruning(const vector<int>& path) {
  if(path.size() < 3) return false;
  int b = path[path.size() - 2];
  int q = path[path.size() - 1];
  for(int i = 0; i + 2 < path.size(); ++i) {
    int p = path[i];
    int a = path[i + 1];
    // [.., p, a, ..., b, q] 를 [.., p, b, ..., a, q] 로 바꿔본다
    if(dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q])
      return true;
  }
  return false;
}

// Union-Find 상호 배제적 집합 자료 구조를 구현한다
struct UnionFind
{
  int n, components;
  vector<int> parent, rank;
  UnionFind(int n) : n(n), components(n), parent(n), rank(n)
  { for(int i = 0; i < n; ++i) { parent[i] = i; rank[i] = 0; } }
  int find(int here) { return parent[here] == here ? here : (parent[here] = find(parent[here])); }
  bool merge(int a, int b)
  {
    a = find(a); b = find(b);
    if(a == b) return false;
    if(rank[a] > rank[b])
      parent[b] = a;
    else
    {
      parent[a] = b;
      if(rank[a] == rank[b]) rank[b]++;
    }
    --components;
    return true;
  }
};

// 모든 도시 간의 도로를 길이 순으로 정렬해 저장해 둔다
vector<pair<double,pair<int,int> > > edges;

// here 와 시작점, 아직 방문하지 않은 도시들을 모두 연결하는 MST 를 찾는다.
double mstHeuristic(int here, const vector<bool>& visited) {
  // Kruskal's MST
  UnionFind sets(n);
  double taken = 0;
  for(int i = 0; i < edges.size(); i++)  {
    int a = edges[i].second.first, b = edges[i].second.second;
    if(a != 0 && a != here && visited[a]) continue;
    if(b != 0 && b != here && visited[b]) continue;
    if(sets.merge(a, b))
      taken += edges[i].first;
  }
  return taken;
}

// 지금까지 찾은 최적해
double best;

double optimize(vector<int> path) {
  while(true) {
    bool improved = false;
    for(int i = 1; i < n; i++)
      for(int j = i+1; j < n; j++) {
        int a = path[i], b = path[j];
        double delta = 0;
        delta += dist[a][path[(j+1) % n]] - dist[b][path[(j+1) % n]];
        delta += dist[b][path[(i+n-1) % n]] - dist[a][path[(i+n-1) % n]];
        if(i + 1 < j) delta += dist[b][path[i+1]] - dist[a][path[i+1]]
          + dist[a][path[j-1]] - dist[b][path[j-1]];
        if(delta < 0) {
          improved = true;
          swap(path[i], path[j]);
        }
        if(improved) break;
      }
    if(!improved) break;
  }
  double length = 0;
  for(int i = 0; i < n; i++)
    length += dist[path[i]][path[(i+1) % n]];
  return length;
}

// 남은 도시의 수가 CACHED_DEPTH 이하면 동적 계획법으로 바꾼다
const int CACHED_DEPTH = 5;

// dp(here, visited) = cache[here][남은 도시의 수][visited]
map<int, double> cache[MAX][CACHED_DEPTH+1];

// here: 현재 위치
// visited: 각 도시의 방문 여부
// 일 때, 나머지 도시들을 모두 방문하고 시작점으로 돌아가는 최단경로의 길이를 반환한다
double dp(int here, int visited) {
  // 기저 사례: 더 방문할 도시가 없으면 시작점으로 돌아간다
  if(visited == (1<<n)-1) return dist[here][0];

  // 메모이제이션
  int remaining = n - __builtin_popcount(visited);
  double& ret = cache[here][remaining][visited];
  if(ret > 0) return ret;

  ret = INF;
  // 다음 도시를 하나하나 시도한다
  for(int next = 0; next < n; ++next) {
    if(visited & (1<<next)) continue;
    ret = min(ret, dp(next, visited + (1<<next)) + dist[here][next]);
  }
  return ret;
}

double blowUp;
clock_t begin;

// path: 지금까지 만든 경로
// visited: 각 도시의 방문 여부
// currentLength: 지금까지 만든 경로의 길이
// 나머지 도시들을 모두 방문하는 경로들을 만들어 보고 가능하면 최적해를 갱신한다
void search(vector<int>& path, vector<bool>& visited, double currentLength) {
  int here = path.back();

  // 지나온 경로를 이용한 가지치기
  if(pathReversePruning(path)) return;

  // MST 휴리스틱을 이용한 가지치기
  double estimation = blowUp * mstHeuristic(here, visited);
  if(best <= currentLength + estimation) return;

  // 기저 사례: 남은 도시 수가 CACHED_DEPTH 이하면 동적 계획법으로 바꾼다
  if(path.size() + CACHED_DEPTH >= n) {
    int mask = 0;
    for(int i = 0; i < n; i++) if(visited[i]) mask += (1 << i);
    double cand = currentLength + dp(here, mask);
    if(cand < best) {
      best = cand;
      //fprintf(stderr, "%g %g\n", (clock() - begin) / (double)CLOCKS_PER_SEC, best);
    }
    return;
  }

  double ret = INF; // 매우 큰 값으로 초기화

  // 다음 방문할 도시를 전부 시도해 본다
  for(int i = 0; i < nearest[here].size(); ++i) {
    int next = nearest[here][i];
    if(visited[next]) continue;

    path.push_back(next);
    visited[next] = true;

    // 나머지 경로를 재귀호출을 통해 완성한다
    search(path, visited, currentLength + dist[here][next]);

    visited[next] = false;
    path.pop_back();
  }
}

vector<string> args;

double solve() {
  // simpleHeuristic() 을 위한 초기화
  for(int i = 0; i < n; ++i) {
    minEdge[i] = INF;
    for(int j = 0; j < n; ++j)
      if(i != j) minEdge[i] = min(minEdge[i], dist[i][j]);
  }

  // nearest 초기화
  for(int i = 0; i < n; ++i) {
    vector<pair<double,int> > order;
    for(int j = 0; j < n; j++)
      if(i != j)
        order.push_back(make_pair(dist[i][j], j));
    sort(order.begin(), order.end());
    nearest[i].clear();
    for(int j = 0; j < n-1; j++)
      nearest[i].push_back(order[j].second);
  }

  // edges 초기화
  edges.clear();
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < i; j++)
      edges.push_back(make_pair(dist[i][j], make_pair(i, j)));
  sort(edges.begin(), edges.end());

  for(int i = 0; i < MAX; i++)
    for(int j = 0; j <= CACHED_DEPTH; j++)
      cache[i][j].clear();

  // best 를 매우 큰 값으로 초기화
  best = INF;

  vector<bool> visited(n, false);
  vector<int> path(1, 0);
  visited[0] = true;

  /*
     if(args.size() <= 3)
     args.push_back("1.0");

     begin = clock();
     for(int i = 3; i < args.size(); ++i) {
     fprintf(stderr, "-1.0\n");
     blowUp = atof(args[i].c_str());
     search(path, visited, 0);

     }   */
  //blowUp = 2.0;
  //search(path, visited, 0);
  //blowUp = 2; search(path, visited, 0);
  //blowUp = 1.5; search(path, visited, 0);
  //blowUpRate = 1.0; search(path, visited, 0);
  //blowUpRate = 1.1; search(path, visited, 0);
  //blowUpRate = 1.1; search(path, visited, 0);
  //blowUpRate = 1.1; search(path, visited, 0);
  blowUp = 1.0; search(path, visited, 0);

  return best;
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
  REP(cc,cases)
  {
    cin >> n;
    vector<double> y(n), x(n);
    for(int i = 0; i < n; i++)
      cin >> y[i] >> x[i];
    REP(i,n) REP(j,n) dist[i][j] = hypot(y[i] - y[j], x[i] - x[j]);
    /*
       CLEAR(cache,0);
       int ret = 1e10;
       REP(st,n) ret = min(ret, shortestPath2(st, 1<<st));
       printf("%.15lf\n", ret);
       */
    vector<bool> visited(n, false);
    visited[0] = true;
    vector<int> path(1, 0);
    //printf("%.15lf\n", shortestPath(path, visited, 0));
    /*
       for(int i = 0; i < n; i++) {
       for(int j = 0; j < (1<<n); j++)
       cache[i][j] = -1;
       }
       printf("%.15lf\n", shortestPath2(0, 1));
       */
    printf("%.15lf\n", solve());
  }
}
