#include <vector>
#include <queue>

using namespace std;

// start에서 시작해 그래프를 너비 우선 탐색하고 시작점부터 각 정점까지의
// 최단 거리와 너비 우선 탐색 스패닝 트리를 계산한다
// distance[i] = start부터 i까지의 최단거리
// parent[i] = 너비 우선 탐색 스패닝 트리에서 i의 부모의 번호, 루트인 경우 자신의 번호
void bfs2(int start, vector<int>& distance, vector<int>& parent) {
    distance = vector<int>(adj.size(), -1);
    parent = vector<int>(adj.size(), -1);

    // 방문할 정점 목록을 유지하는 큐
    queue<int> q;
    distance[start] = 0;
    parent[start] = start;
    q.push(start);
    while (!q.empty()) {
        int here = q.front();
        q.pop();
        // here의 모든 인접한 정점을 검사한다
        for (int i=0; i<adj[here].size(); i++) {
            int there = adj[here][i];
            if (distance[there] == -1) {
                q.push(there);
                distance[there] = distance[here] + 1;
                parent[there] = here;
            }
        }
    }
}

// v로부터 시작점까지의 최단 경로를 계산
vector<int> shortestPath(int v, const vector<int>& parent) {
    vector<int> path(1, v);
    while(parent[v] != v) {
        v = parent[v];
        path.push_back(v);
    }

    reverse(path.begin(), path.end());
    return path;
}