#include <vector>

struct OptimizedDisjointSet {
    vector<int> parent, rank;

    OptimizedDisjointSet(int n) : parent(n), rank(n, 1) {
        for (int i=0; i<n; ++i)
            parent[i] = i;
    }

    int find(int u) {
        if (u == parent[u]) return u;
        return parent[u] = find(parent[u]);
    }

    void merge(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return;

        if (rank[u] > rank[v]) swap(u, v);

        parent[u] = v;
        if (rank[u] == rank[v]) ++rank[v];
    }
};