#include<fstream>
#include<cstdio>
#include<cassert>
#include<cstring>
#include<map>
#include<time.h>
#include<algorithm>
#include<stack>
#include<queue>
#include<utility>
#include<cmath>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

typedef unsigned long long State;

const int SHIFT = 5; // MAXCAPACITY < (2 ** SHIFT)
const int FULL = (1 << SHIFT) - 1;

int n, target;
vector<int> capacity;

int get(State state, int jug) { 
	return (state >> (SHIFT * jug)) & FULL; 
}

State set(State state, int jug, int amt) {
	return (state & ~(FULL << (SHIFT * jug)) | (amt << (SHIFT * jug)));
}


void decode(State state, vector<int>& amt) {
	amt.resize(n);
	for(int i = 0; i < n; i++) 
		amt[i] = get(state, i);
}

void getNeighbors(State here, vector<State>& neighbors) {
	neighbors.clear();
	vector<int> amt;
	decode(here, amt);
	// fill operation
	for(int i = 0; i < n; i++) 
		if(amt[i] < capacity[i]) {
			State filled = set(here, i, capacity[i]);
			neighbors.push_back(filled);
		}

	// empty operation
	for(int i = 0; i < n; ++i) 
		if(amt[i] > 0) {
			State emptied = set(here, i, 0);
			neighbors.push_back(emptied); 
		}
	// move operation
	for(int i = 0; i < n; i++) {
		if(amt[i] == 0) continue;
		for(int j = 0; j < n; j++) 
			if(i != j && amt[j] < capacity[j]) {
				int moveAmt = min(amt[i], capacity[j] - amt[j]);
				State moved = set(set(here, i, amt[i] - moveAmt), j, amt[j] + moveAmt);
				neighbors.push_back(moved);
			}
	}
}

void getReverseNeighbors(State here, vector<State>& neighbors) {
	neighbors.clear();
	vector<int> amt;
	decode(here, amt);
	// last operation was a fill?
	for(int i = 0; i < n; i++) 
		if(amt[i] == capacity[i]) 
			for(int prevAmt = 0; prevAmt < capacity[i]; ++prevAmt) 
				neighbors.push_back(set(here, i, prevAmt));
	// last operation was an empty?
	for(int i = 0; i < n; i++) 
		if(amt[i] == 0) 
			for(int prevAmt = 1; prevAmt <= capacity[i]; ++prevAmt) 
				neighbors.push_back(set(here, i, prevAmt));
	// last operation was a move from i to j?
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j) {
			if(i == j) continue;
			// either (i should be empty) or (j should be full)
			if(amt[i] == 0 || amt[j] == capacity[j])
				for(int amtMoved = 1; amtMoved <= min(capacity[i] - amt[i], amt[j]); ++amtMoved)
					neighbors.push_back(set(set(here, i, amt[i] + amtMoved), j, amt[j] - amtMoved));
		}
}

bool isFinished(State state) {
	for(int i = 0; i < n; i++) 
		if(state == set(0, i, target)) 
			return true;
	return false;
}

int bfs() {
	map<State, int> c;
	queue<State> q;
	c[0] = 0;
	q.push(0);
	while(!q.empty()) {
		State here = q.front();
		q.pop();

		int dist = c[here];
		if(isFinished(here)) return dist;

		vector<State> neighbors;
		getNeighbors(here, neighbors);
		for(int i = 0; i < neighbors.size(); i++)  {
			State there = neighbors[i];
			if(c.count(there) == 0) {
				c[there] = dist + 1;
				q.push(there);
			}
		}
	}
	return -1;
}

int best;

void dfs(State here, int steps) {
	int nonzero = 0;
	for(int i = 0; i < n; i++) if(get(here, i)) ++nonzero;
	if(steps + max(0, nonzero - 1) >= best) return;
	if(isFinished(here)) {
		best = steps;
		return;
	}
	vector<State> neighbors;
	getNeighbors(here, neighbors);
	for(int i = 0; i < neighbors.size(); ++i) 
		dfs(neighbors[i], steps+1);
}

int ids() {
	for(int limit = 4; limit; limit += 4) {
		best = limit + 1;
		dfs(0, 0);
		if(best <= limit) return best;
	}
	return best;
}

// x 의 부호를 반환한다
int sgn(int x) { if(x < 0) return -1; if(x > 0) return 1; return 0; }
// x 의 절대값을 1 증가시킨다
int incr(int x) { if(x < 0) return x-1; return x+1; }

const int BACKWARDS_LIMIT = 1;

int bidir() {
	map<State,int> c;
	queue<State> q;
	for(int i = 0; i < n; i++) 
		if(target <= capacity[i]) {
			State candidate = set(0, i, target);
			c[candidate] = -1;
			q.push(candidate);
		}
	while(!q.empty()) {
		State here = q.front();
		q.pop();
		int dist = c[here];
		vector<State> neighbors;
		getReverseNeighbors(here, neighbors);		
		for(int i = 0; i < neighbors.size(); i++) {
			State there = neighbors[i];
			if(c.count(there) == 0) {
				c[there] = incr(dist);
				if(dist > -BACKWARDS_LIMIT-1) q.push(there);
			}
		}
	}
	printf("backwards %d\n", c.size());
	
	c[0] = 1;
	q.push(0);

	while(!q.empty()) {
		State here = q.front();
		q.pop();

		int dist = c[here];
		vector<State> neighbors;
		getNeighbors(here, neighbors);
		for(int i = 0; i < neighbors.size(); i++) {
			State there = neighbors[i];
			map<State,int>::iterator it = c.find(there);
			if(it == c.end()) {
				c[there] = incr(dist);
				q.push(there);
			}
			// 가운데서 만났나?
			else if(it->second < 0)
				return dist + abs(it->second) - 1;			
		}
	}	
	return -1;
}

int solve(const char* algo) {
	// target 이 capacity들의 최대공약수로 나눠 떨어지지 않으면 무조건 실패!
	int g = capacity[0];
	for(int i = 1; i < n; i++) g = __gcd(g, capacity[i]);
	if(target % g) return -1;
	if(strcmp(algo, "BFS") == 0) return bfs();
	if(strcmp(algo, "BIDIR") == 0) return bidir();
	if(strcmp(algo, "IDS") == 0) return ids();
	printf("unknown algo %s\n", algo);
	return -1;
}

int main(int argc, char* argv[]) {
    int cases;
    cin >> cases;
    //ifstream outp("output.bfs.txt");
    for(int cc = 0; cc < cases; ++cc) {
    	cin >> n >> target;
    	capacity.resize(n);
    	for(int i = 0; i < n; i++) cin >> capacity[i];
    	int sol = solve(argc == 1 ? "BFS" : argv[1]);
    	/*
    	int bfs;
    	outp >> bfs;
    	if(sol != bfs) {
    		printf("n = %d, target = %d\ncapa =", n, target);
    		for(int i = 0; i < n; i++) 
    			printf(" %d", capacity[i]);
    		printf("\n");
    		printf("BFS %d BIDIR %d\n", bfs, sol);
		}
		*/
		cout << sol << endl;
    }
}

