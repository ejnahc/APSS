#include <vector>

struct NaiveDisjointSet {
    vector<int> parent;
    NaiveDisjointSet(int n): parent(n) {
        for (int i=0; i<n; ++i)
            parent[i] = i;
    }

    int find(int u) const {
        if (u == parent[u]) return u;
        return find(parent[u]);
    }

    void merge(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return;
        parent[u] = v;
    }
};