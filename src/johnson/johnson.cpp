#include<iostream>
#include<cstring>
#include<algorithm>
#include<sstream>
#include<string>
#include<vector>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<cassert>
#include<numeric>
#include<set>
#include<map>
#include<queue>
#include<list>
#include<deque>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define REP(i,n) FOR(i,0,n)
#define FORE(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define CLEAR(x,with) memset(x,with,sizeof(x))
#define sz size()
typedef long long ll;

const int INF = 987654321;

struct DiGraph {
	struct Edge {
		int target, weight;
		Edge(int t, int w) : target(t), weight(w) { }
	};

	vector<vector<Edge> > adj;
	int getV() const { return adj.size(); }

	DiGraph(int V) {
		adj.resize(V);
	}

	int addVertex() {
		adj.push_back(vector<Edge>());
		return adj.size()-1;
	}

	void addEdge(int a, int b, int c) {
		adj[a].push_back(Edge(b, c));
	}

	bool bellmanFord(int start, vector<int>& ret) const {
		int V = getV();
		ret.resize(V);
		fill(ret.begin(), ret.end(), INF);
		ret[start] = 0;
		int lastRelaxed = -1;
		for(int round = 0; round < V; ++round) 
			for(int here = 0; here < V; ++here)
				for(int i = 0; i < adj[here].size(); ++i) {
					int there = adj[here][i].target;
					int cost = adj[here][i].weight;
					if(ret[there] > ret[here] + cost) {
						lastRelaxed = round;
						ret[there] = ret[here] + cost;
					}
				}
		return lastRelaxed < V-1;
	}

	void dijkstra(int start, vector<int>& ret) const {
		int V = getV();
		ret.resize(V); 
		fill(ret.begin(), ret.end(), INF);
		priority_queue<pair<int, int> > pq;

		ret[start] = 0;
		pq.push(make_pair(0, start));

		while(!pq.empty()) {
			int cost = -pq.top().first;
			int here = pq.top().second;
			pq.pop();
			if(ret[here] < cost) continue;
			for(int i = 0; i < adj[here].size(); ++i) {
				int there = adj[here][i].target;
				int thereCost = cost + adj[here][i].weight;
				if(ret[there] > thereCost) {
					ret[there] = thereCost;
					pq.push(make_pair(-thereCost, there));
				}
			}
		}
	}

	bool johnson(vector<vector<int> >& ret) {
		ret.clear();
		int V = getV();
		int superSource = addVertex();
		for(int i = 0; i < V; ++i) 
			addEdge(superSource, i, 0);
		vector<int> h;
		if(!bellmanFord(superSource, h)) return false;

		V = getV();
		for(int here = 0; here < V; ++here)
			for(int i = 0; i < adj[here].size(); ++i) {
				int there = adj[here][i].target;
				adj[here][i].weight += h[here] - h[there];
			}
		ret.resize(V-1); // exclude super-source
		for(int start = 0; start < V-1; ++start) {
			dijkstra(start, ret[start]);
			ret[start].pop_back(); // distance to super-source must be zero
			for(int end = 0; end < V-1; ++end) 
				if(ret[start][end] != INF)
					ret[start][end] -= h[start] - h[end];
		}
		return true;
	}
};

int main()
{
	int n, m;
	cin >> n >> m;
	DiGraph g(n);
	REP(i,m)
	{
		int a, b, c;
		cin >> a >> b >> c;
		g.addEdge(a, b, c);
	}
	vector<vector<int> > ret;
	g.johnson(ret);
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j)
			printf("%d ", ret[i][j]);
		printf("\n");
	}
		
	/*
	vector<int> d(n+1, 987654321);
	d[0] = 0;
	REP(it,n)
	{
		REP(i,n+1) REP(j,adj[i].sz)
		{
			int there = adj[i][j].first;
			int cost = adj[i][j].second;
			d[there] = min(d[there], d[i] + cost);
		}
	}
	REP(i,n+1) REP(j,adj[i].sz)
	{
		int there = adj[i][j].first;
		int cost = adj[i][j].second;
		if(d[there] > d[i] + cost)
		{
			printf("ooops (%d,%d)\n", i, there);
		}
	}
	REP(i,n+1) printf("d[%d] = %d\n", i, d[i]);
	REP(here,n+1) REP(j,adj[here].sz)
	{
		int there = adj[here][j].first;
		int cost = adj[here][j].second;
		cost += d[here] - d[there];
		printf("%d => %d (%d)\n", here, there, cost);
	}
	*/
}
