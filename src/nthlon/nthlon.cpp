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
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define REP(i,n) FOR(i,0,n)
#define FORE(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define CLEAR(x,with) memset(x,with,sizeof(x))
#define sz size()
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long ll;

struct WeightedGraph {

    struct Edge {
        int u, v, w;

        Edge(int u, int v, int w) : u(u), v(v), w(w) {}
    };

    int nodes;
    vector<vector<Edge> > edges;

    WeightedGraph(int n) : nodes(n), edges(n) {}
    void addEdge(int u, int v, int w) {
        //cout << "addEdge " << u << " => " << v << " (" << w << ")" << endl; 
        edges[u].push_back(Edge(u, v, w)); 
    }

    vector<int> dijkstra(int origin) {
        vector<int> ret(nodes, -1);
        priority_queue<pair<int,int> > pq;
        ret[origin] = 0;
        pq.push(make_pair(0, origin));
        while(!pq.empty()) {
            int cost = -pq.top().first;
            int here = pq.top().second;
            pq.pop();
            if(ret[here] != cost) continue;
            //printf("diff %d: cost %d\n", here - 200, cost);
            for(int i = 0; i < edges[here].size(); ++i) {
                int there = edges[here][i].v;
                int newCost = cost + edges[here][i].w;
                if(ret[there] == -1 || ret[there] > newCost) {
                    ret[there] = newCost;
                    pq.push(make_pair(-newCost, there));
                }
            }
        }
        return ret;
    }
};

struct Nthlon {
    int n;
    vector<int> a, b;

    int sgn(int x) {
        if(x > 0) return 1;
        if(x < 0) return -1;
        return 0;
    }

    int solve() {
        // node #: a's time - b's time + 200
        WeightedGraph g(402); 

        for(int sport = 0; sport < n; ++sport) 
            g.addEdge(401, a[sport] - b[sport] + 200, max(a[sport], b[sport]));
        

        for(int diff = -200; diff <= 200; ++diff) {
            int node = diff + 200;
            for(int sport = 0; sport < n; ++sport) {
                int newDiff = diff + (a[sport] - b[sport]);
                if(newDiff < -200 || newDiff > 200) continue;
                int newNode = newDiff + 200;
                
                int add = -1;
                
                // 1. 역전되었을 경우
                if(sgn(diff) != sgn(newDiff)) 
                    add = max(a[sport], b[sport]) - abs(diff);
                // 2. 역전 안되었을 경우
                else
                {
                    // 긴 것이 짧은 쪽에 갔을 경우
                    if(sgn(diff) != sgn(a[sport] - b[sport]))
                        add = min(a[sport], b[sport]);
                    // 긴 것이 긴 쪽에 갔을 경우
                    else
                        add = max(a[sport], b[sport]);
                }
                g.addEdge(node, newNode, add);
            }
        }
        return g.dijkstra(401)[200];
    }
};

Nthlon instance;

int main()
{
    int cases;
    scanf("%d", &cases);
    for(int cc = 0; cc < cases; ++cc)
    {
        scanf("%d", &instance.n);
        instance.a.resize(instance.n);
        instance.b.resize(instance.n);
        for(int i = 0; i < instance.n; ++i)
            scanf("%d %d", &instance.a[i], &instance.b[i]);
        int ret = instance.solve();
        if(ret == -1)
            cout << "IMPOSSIBLE" << endl;
        else
            cout << ret << endl;
    }
}
