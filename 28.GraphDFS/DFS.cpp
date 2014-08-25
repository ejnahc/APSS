// 그래프의 인접 리스트 표현
vector<vector<int> > adj;

// 각 정점을 방문했는지 여부를 나타낸다
vector<bool> visited;

// 깊이 우선 탐색을 구현한다
void dfs(int here) {
    visited[here] = true;
    for (int i=0; i<adj[here].size(); i++) {
        int there = adj[here][i];
        if (!visited[there])
            dfs(there);
    }
}

// 모든 정점을 방문한다
void dfsAll() {
    // visited를 모두 false로 초기화한다
    visited = vector<bool>(adj.size(), false);

    // 모든 정점을 순회하면서, 아직 방문한 적 없으면 방문한다
    for (int i=0; i<adj.size(); i++)
        if (!visited[i])
            dfs(i);
}