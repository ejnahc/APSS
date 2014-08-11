#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
#include<stack>
using namespace std;

// 그래프의 인접 리스트 표현
vector<vector<int> > adj;

// 각 정점의 컴포넌트 번호. 컴포넌트 번호는 0 부터 시작하며, 
// 같은 강결합 컴포넌트에 속한 정점들의 컴포넌트 번호가 같다.
vector<int> sccId;

// 각 정점의 발견 순서와 scc() 종료 여부
vector<int> discovered, finished;

// 정점의 번호를 담는 스택
stack<int> st;

int sccCounter, vertexCounter;

// here 를 루트로 하는 서브트리에서 역방향 간선으로 닿을 수 있는 최소의 발견 순서를
// 반환한다.
int scc(int here) {
	int ret = discovered[here] = vertexCounter++;
	// 스택에 here 를 넣는다. here 의 후손들은 모두 스택에서 here 후에 들어간다.
	st.push(here);	
	for(int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];
		// (here,there) 가 트리 간선
		if(discovered[there] == -1) 
			ret = min(ret, scc(there));
		// (here,there) 가 교차 간선인 경우는 무시한다
		else if(discovered[there] < discovered[here] && finished[there] != 1) 
			ret = min(ret, discovered[there]);
	}	
	// here 가 강결합 컴포넌트의 루트인가 확인한다
	if(ret == discovered[here]) {
		// here 를 루트로 하는 서브트리에 남아 있는 정점들을 전부 하나의 컴포넌트로 묶는다
		while(true) {
			int t = st.top();
			st.pop();
			sccId[t] = sccCounter;
			if(t == here) break;
		}
		++sccCounter;
	}
	finished[here] = 1;
	return ret;
}

// tarjan 의 SCC 알고리즘
vector<int> tarjanSCC() {
	// 배열들을 전부 초기화
	sccId = discovered = vector<int>(adj.size(), -1);
	finished = vector<int>(adj.size(), 0);
	// 카운터 초기화
	sccCounter = vertexCounter = 0;
	// 모든 정점에 대해 scc() 호출
	for(int i = 0; i < adj.size(); i++) if(discovered[i] == -1) scc(i);
	return sccId;
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	int v, e;
    	cin >> v >> e;
    	adj = vector<vector<int> >(v);
    	for(int i = 0; i < e; i++) {
    		int a, b;
    		cin >> a >> b;
    		adj[a].push_back(b);
    	}
    	vector<int> scc = tarjanSCC();
    	for(int i = 0; i < v; i++) 
    		cout << scc[i] << ' ';
    	cout << endl;
    }
}

