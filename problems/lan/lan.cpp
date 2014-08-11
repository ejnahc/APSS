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
int v, e;
int x[501], y[501];
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
int main() {
  int cases;
  cin >> cases;
  for(int cc = 0; cc < cases; ++cc) {
    cin >> v >> e;
    for(int i = 0; i < v; ++i) cin >> x[i];
    for(int i = 0; i < v; ++i) cin >> y[i];
    DisjointSet d(v);
    for(int i = 0; i < e; ++i) {
      int u, v;
      cin >> u >> v;
      d.merge(u, v);
    }
    vector<pair<double,pair<int,int> > > edges;
    for(int i = 0; i < v; ++i)
      for(int j = i+1; j < v; ++j)
        if(d.find(i) != d.find(j)) {
          edges.push_back(make_pair(hypot(x[i] - x[j], y[i] - y[j]),
                                    make_pair(i, j)));
        }
    sort(edges.begin(), edges.end());
    double ret = 0;
    for(int i = 0; i < edges.size(); ++i)  {
      double w = edges[i].first;
      int a = edges[i].second.first;
      int b = edges[i].second.second;
      if(d.find(a) != d.find(b)) {
        ret += w;
        d.merge(a, b);
      }
    }
    printf("%.10lf\n", ret);


  }
}

