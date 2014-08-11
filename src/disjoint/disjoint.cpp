#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 트리를 이용해 상호 배제적 집합을 구현한다.
struct NaiveDisjointSet {
	vector<int> parent;

	NaiveDisjointSet(int n) : parent(n) {
		for(int i = 0; i < n; i++)
			parent[i] = i;
	}

	// u 가 속한 트리의 루트의 번호를 반환한다
	int find(int u) const {
		if(u == parent[u]) return u;
		return find(parent[u]);
	}

	// u 가 속한 트리와 v 가 속한 트리를 합친다
	void merge(int u, int v) {
		u = find(u);
		v = find(v);
		// u 와 v 가 이미 같은 트리에 속하더라도 상관 없다
		parent[u] = v;
	}
};

// 트리를 이용해 상호 배제적 집합을 구현한다.
struct OptimizedDisjointSet {
	vector<int> parent, rank;

	OptimizedDisjointSet(int n) : parent(n), rank(n, 1) {
		for(int i = 0; i < n; i++)
			parent[i] = i;
	}

	// u 가 속한 트리의 루트의 번호를 반환한다
	int find(int u) {
		if(u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}

	// u 가 속한 트리와 v 가 속한 트리를 합친다
	void merge(int u, int v) {
		u = find(u); v = find(v);
		// 이미 둘이 같은 트리에 속한 경우
		if(u == v) return;
		if(rank[u] > rank[v]) swap(u, v);
		// 이제 항상 rank[v] 가 더 크므로 u 를 v 의 자식으로 넣는다
		if(rank[u] == rank[v]) rank[v]++;
		parent[u] = v;
	}
};
int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {

    }
}

