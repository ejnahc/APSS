// 정점의 개수
int V;

// 그래프의 인접 행렬 표현
// adj[u][v] = u에서 v로 가는 간선의 가중치. 간선이 없으면 아주 큰 값을 넣는다
int adj[MAX_V][MAX_V];

// 플로이드의 모든 쌍 최단 거리 알고리즘
void floyd() {
    for (int i=0; i<V; ++i)        adj[i][i] = 0;

    for (int k=0; k<V; ++k)
    for (int i=0; i<V; ++i)
    for (int j=0; j<V; ++j)
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}