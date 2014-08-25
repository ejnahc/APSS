// 정점의 개수
int V;

// 그래프의 인접 행렬 표현
// adj[u][v] = u에서 v로 가는 간선의 가중치. 간선이 없으면 아주 큰 값을 넣는다
int adj[MAX_V][MAX_V];

// via[u][v] = u에서 v까지 가는 최단 경로가 경유하는 점 중 가장 번호가 큰 정점
// -1로 초기화한다
int via[MAX_V][MAX_V];

// 플로이드의 모든 쌍 최단 거리 알고리즘
void floyd2() {
    for (int i=0; i<V; ++i) adj[i][i] = 0;
    memset(via, -1, sizeof(via));

    for (int k=0; k<V; ++k)
    for (int i=0; i<V; ++i)
    for (int j=0; j<V; ++j) {
        if (adj[i][j] > adj[i][k] + adj[k][j]) {
            via[i][j] = k;
            adj[i][j] = adj[i][k] + adj[k][j];
        }
    }
}

// u에서 v로 가는 최단 경로를 계산해 path에 저장한다
void reconstruct(int u, int v, vector<int>& path) {
    // 기저 사례
    if (via[u][v] == -1) {
        path.push_back(u);
        if (u != v) path.push_back(v);
    } else {
        int w = via[u][v];
        reconstruct(u, w, path);
        path.pop_back(); // w가 중복으로 들어가므로 지운다
        reconstruct(w, v, path);
    }
}