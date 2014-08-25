// 정점의 개수
int V;

// 그래프의 인접 행렬 표현
// adj[u][v] = u에서 v로 가는 간선의 가중치. 간선이 없으면 아주 큰 값을 넣는다
int adj[MAX_V][MAX_V];
int C[MAX_V][MAX_V][MAX_V];

void allPairShortestPath1() {
    // C[0]을 초기화
    for (int i=0; i<V; ++i)
        for (int j=0; j<V; ++j)
            if (i != j)
                C[0][i][j] = min(adj[i][j], adj[i][0] + adj[0][j]);
            else
                C[0][i][j] = 0;

    // C[k-1]이 있으면 C[k]를 계산할 수 있다
    for (int k=1; k<V; ++k)
        for (int i=0; i<V; ++i)
            for (int j=0; j<V; ++j)
                C[k][i][j] = min(C[k-1][i][j], C[k-1][i][k] + C[k-1][k][j]);
}