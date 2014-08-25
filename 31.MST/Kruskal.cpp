// 트리를 이용해 상호 배재적 집합을 구현한다 (25.DisjointSet)

struct DisjointSet;
const int MAX_V = ;

// 정점의 개수
int V;
// 그래프의 인접 리스트 (연결된 정점 번호, 간선 가중치) 쌍을 담는다
vector<pair<int, int> > adj[MAX_V];

// 주어진 그래프에 대해 최소 스패닝 트리에 포함된 간선의 목록을 selected에 저장하고 가중치의 합을 반환한다
int kruskal(vector<pair<int, int> >& selected) {
    int ret = 0;
    selected.clear();

    // (가중치, (정점1, 정점2))의 목록을 얻는다
    vector<pair<int, pair<int, int> > > edges;
    for (int u=0; u<V; ++u)
        for (int i=0; i<adj[u].size(); ++i) {
            int v = adj[u][i].first, cost = adj[u][i].second;
            edges.push_back(make_pair(cost, make_pair(u, v)));
        }

    // 가중치 순으로 정렬
    sort(edges.begin(), edges.end());

    // 처음에는 모든 정점이 서로 분리되어 있다
    DisjointSet sets(V);
    for (int i=0; i<edges.size(); i++) {
        // 간선 (u, v)를 검사한다
        int cost = edges[i].first;
        int u = edges[i].second.first, v = edges[i].second.second;

        // 이미 u와 v가 연결되어 있을 경우 무시한다
        if (sets.find(u) == sets.find(v)) continue;
        // 이 둘을 합친다
        sets.merge(u, v);
        selected.push_back(make_pair(u, v));
        ret += cost;
    }

    return ret;
}