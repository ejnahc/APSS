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

const int MAX_V = 10000;

int V, E;
// 그래프의 연결 리스트 표현
vector<pair<int,int> > adj[MAX_V];
// 모든 간선의 가중치의 목록
vector<int> weights;

// 가중치가 weights[low] 이상인 간선으로 0과 V-1을 연결하는
// 경로를 만들기 위해 필요한 간선의 최소 상한을 계산한다.
// 두 정점을 연결할 수 없을 경우 큰 값을 반환한다.
int minMaxEdge(int low);

// 0과 V-1을 연결하는 경로 중 가중치의 상한과 하한 차이의
// 최소값을 계산한다.
int minWeightDifference() {
  int ret = 987654321;
  for(int i = 0; i < weights.size(); ++i)
    ret = min(ret, minMaxEdge(i) - weights[i]);
  return ret;
}

int seen[MAX_V];

// [lo,hi] 범위 가중치를 갖는 간선만으로 here에서 target에
// 갈 수 있는가?
bool dfs(int here, int lo, int hi) {
  if(here == V-1) return true;
  seen[here] = 1;
  for(int i = 0; i < adj[here].size(); ++i) {
    int there = adj[here][i].first, edge = adj[here][i].second;
    if(edge < lo || hi < edge || seen[there]) continue;
    if(dfs(there, lo, hi)) return true;
  }
  return false;
}


// 0과 V-1을 잇는 경로 중 사용 가중치 범위가 [lo,hi] 안인
// 경로가 있는가?
bool hasPath(int lo, int hi) {
  memset(seen, 0, sizeof(seen));
  return dfs(0, lo, hi);
}

int binarySearchMinMaxEdge(int low) {
  // 반복문 불변식:
  // 1. 가중치가 [weights[low], weights[lo]]
  // 범위에 있는 간선을 사용하면 두 정점을 연결할 수 없다.
  // 2. 가중치가 [weights[low], weights[hi]] 범위에 있는
  // 간선을 사용하면 두 정점을 연결할 수 있다.
  int lo = low-1, hi = weights.size();
  while(lo + 1 < hi) {
    int mid = (lo + hi) / 2;
    if(hasPath(weights[low], weights[mid]))
      hi = mid;
    else lo = mid;
  }
  if(hi == weights.size())
    return 987654321;
  return weights[hi];
}

// 트리를 이용해 상호 배제적 집합을 구현한다.
struct DisjointSet {
  vector<int> parent, rank;

  DisjointSet(int n) : parent(n), rank(n, 1) {
    for(int i = 0; i < n; i++)
      parent[i] = i;
  }

  // u 가 속한 트리의 루트의 번호를 반환한다
  int find(int u) {
    if(u == parent[u]) return u;
    return parent[u] = find(parent[u]);
  }

  // u 가 속한 트리와 v 가 속한 트리를 합친다
  void merge(int u, int v) {
    u = find(u); v = find(v);
    // 이미 둘이 같은 트리에 속한 경우
    if(u == v) return;
    if(rank[u] > rank[v]) swap(u, v);
    // 이제 항상 rank[v] 가 더 크므로 u 를 v 의 자식으로 넣는다
    if(rank[u] == rank[v]) rank[v]++;
    parent[u] = v;
  }
};

// (가중치, (정점1, 정점2)) 의 목록. 미리 정렬해 둔다.
vector<pair<int,pair<int,int> > > edges;

int kruskalMinMaxEdge(int low) {
  DisjointSet sets(V);
  for(int i = 0; i < edges.size(); ++i) {
    if(edges[i].first < weights[low]) continue;

    // edges[i] 를 그래프에 추가하자
    sets.merge(edges[i].second.first, edges[i].second.second);

    // 0과 V-1이 연결되었다면 마지막에 추가한 간선의 가중치를 반환한다.
    if(sets.find(0) == sets.find(V-1))
      return edges[i].first;
  }
  return 987654321;
}

int primMinMaxEdge(int low) {
  vector<int> maxEdge(V, 987654321);
  priority_queue<pair<int,int> > pq;

  maxEdge[0] = weights[low];
  pq.push(make_pair(-maxEdge[0], 0));
  while(!pq.empty()) {
    int here = pq.top().second, maxEdgeToHere = -pq.top().first;
    pq.pop();
    if(maxEdge[here] != maxEdgeToHere) continue;
    for(int i = 0; i < adj[here].size(); ++i) {
      int there = adj[here][i].first, edge = adj[here][i].second;
      if(edge < weights[low]) continue;
      int maxEdgeToThere = max(maxEdgeToHere, edge);
      if(maxEdge[there] > maxEdgeToThere) {
        maxEdge[there] = maxEdgeToThere;
        pq.push(make_pair(-maxEdgeToThere, there));
      }
    }
  }
  return maxEdge[V-1];
}

// 모든 가중치 범위에 대해 경로가 존재하는지 전부 확인해
// 보고, 경로가 존재하는 최소 범위의 크기를 반환한다.
int brute() {
  int ret = 987654321;
  for(int lo = 0; lo < weights.size(); ++lo)
    for(int hi = lo; hi < weights.size(); ++hi) {
      // 사용할 수 있는 간선 가중치 범위가 주어질 때, 두 점을 잇는
      // 경로가 존재하는가?
      if(hasPath(weights[lo], weights[hi])) {
        ret = min(ret, weights[hi] - weights[lo]);
        break;
      }
    }
  return ret;
}

// brute() 를 더 빠르게 개선한 알고리즘
int optimized() {
  // foundPathUsing = 경로를 찾기 위해 마지막으로 사용했던 가중치의 위치
  int ret = 987654321, foundPathUsing = 0;
  for(int lo = 0; lo < weights.size(); ++lo) {
    // 이 하한에 대해 경로를 발견했는가?
    bool foundPath = false;
    for(int hi = foundPathUsing; hi < weights.size(); ++hi) {
      if(hasPath(weights[lo], weights[hi])) {
        ret = min(ret, weights[hi] - weights[lo]);
        foundPath = true;
        foundPathUsing = hi;
        break;
      }
    }
    // 경로가 없다면 곧장 종료한다
    if(!foundPath) break;
  }
  return ret;

}

// 가중치 범위를 훑어나가며 경로가 존재하는 가중치 범위의 최소 크기를 찾는다.
int scanning() {
  int lo = 0, hi = 0, ret = 987654321;
  while(true) {
    if(hasPath(weights[lo], weights[hi])) {
      ret = min(ret, weights[hi] - weights[lo]);
      ++lo;
    }
    else {
      if(hi == weights.size()-1) break;
      ++hi;
    }
  }
  return ret;
}

// 모든 간선의 가중치를 모아 정렬하고 중복을 제거해 반환한다
vector<int> collectWeights() {
  vector<int> weights;
  // 모든 간선의 가중치를 저장한다
  for(int i = 0; i < V; ++i)
    for(int j = 0; j < adj[i].size(); ++j)
      weights.push_back(adj[i][j].second);
  // 정렬하고 중복을 제거한다
  sort(weights.begin(), weights.end());
  weights.erase( unique(weights.begin(), weights.end()), weights.end() );
  return weights;
}

string algo;
int minMaxEdge(int low) {
  if(algo == "binary") return binarySearchMinMaxEdge(low);
  if(algo == "kruskal") return kruskalMinMaxEdge(low);
  if(algo == "prim") return primMinMaxEdge(low);
  assert(false);
  return 0;
}

int main(int argc, const char* argv[]) {
  algo = (argc > 1 ? argv[1] : "prim");
  int cases;
  scanf("%d", &cases);
  for(int cc = 0; cc < cases; ++cc) {
    scanf("%d %d", &V, &E);
    edges.resize(E);
    for(int i = 0; i < V; ++i) adj[i].clear();
    for(int i = 0; i < E; ++i) {
      int a, b, c;
      scanf("%d %d %d", &a, &b, &c);
      edges[i] = make_pair(c, make_pair(a, b));
      adj[a].push_back(make_pair(b, c));
      adj[b].push_back(make_pair(a, c));
    }
int g[1000][1000][720];
for(int i = 0; i < 1000; ++i)
for(int j = 0; j < 1000; ++j)
for(int k = 0; k < 720; ++k)
g[i][j][k] = i*j*k;
int ret = 0;
for(int i = 0; i < 1000; ++i)
for(int j = 0; j < 1000; ++j)
for(int k = 0; k < 720; ++k)
  ret += g[i][j][k];
printf("%d\n", ret);

    weights = collectWeights();
    sort(edges.begin(), edges.end());
    if(algo == "scanning")
      printf("%d\n", scanning());
    else if(algo == "brute")
      printf("%d\n", brute());
    else if(algo == "optimized")
      printf("%d\n", optimized());
    else
      printf("%d\n", minWeightDifference());
  }
}
