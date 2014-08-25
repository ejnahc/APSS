#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <vector>

using namespace std;

#define MAX_V 111
int V;

const int INF = 987654321;

vector<pair<int, int> > adj[MAX_V];
bool reachable[MAX_V][MAX_V];

int bellman2(int src, int target) {
    vector<int> upper(V, INF);

    upper[src] = 0;
    for (int iter=0; iter<V-1; ++iter) {
        for (int here=0; here<V; ++here) {
            for (int i=0; i<adj[here].size(); i++) {
                int there = adj[here][i].first;
                int cost = adj[here][i].second;
                upper[there] = min(upper[there], upper[here] + cost);
            }
        }
    }

    for (int here=0; here<V; ++here) {
        for (int i=0; i<adj[here].size(); i++) {
            int there = adj[here][i].first;
            int cost = adj[here][i].second;

            if (upper[here] + cost < upper[there])
                if (reachable[src][here] && reachable[here][target])
                    return -INF;
        }
    }

    return upper[target];
}

int main() {
    int C; cin >> C; while (C--) {
        int W;
        cin >> V >> W;

        for (int i=0; i<MAX_V; i++) {
            adj[i].clear();
            for (int j=0; j<MAX_V; j++)
                reachable[i][j] = (i == j);
        }

        int ai,bi,di;
        for (int i=0; i<W; i++) {
            cin >> ai >> bi >> di;
            adj[ai].push_back(make_pair(bi, di));

            reachable[ai][bi] = true;
        }

        for(int i = 0; i < V; i++) for(int j = 0; j < V; j++) for(int k = 0; k < V; k++) reachable[j][k] = reachable[j][k] || (reachable[j][i] && reachable[i][k]);

        if (reachable[0][1]) {
            int ret = bellman2(0, 1);

            if (ret == -INF) cout << "INFINITY ";
            else cout << ret << " ";

            // flip
            for (int j=0; j<V; j++)
            for (int i=0; i<adj[j].size(); i++)
                adj[j][i].second = -adj[j][i].second;

            int ret2 = bellman2(0, 1);
            if (ret2 == -INF) cout << "INFINITY" << endl;
            else cout << -ret2 << endl;
        } else {
            cout << "UNREACHABLE\n";
        }
    }
}