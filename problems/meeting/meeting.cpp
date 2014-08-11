#include<algorithm>
#include<stack>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 그래프의 인접 리스트 표현
vector<vector<int> > adj;

// 두 구간 a 와 b 가 서로 겹치지 않는지를 확인한다
bool disjoint(const pair<int,int>& a, const pair<int,int>& b) {
	return a.second <= b.first || b.second <= a.first;
}

// meetings[] 가 각 팀이 하고 싶어하는 회의 시간의 목록일 때, 이를 
// 2-SAT 문제로 변환한 뒤 함축 그래프를 생성한다.
// i번 팀은 meetings[2*i] 혹은 meetings[2*i+1] 중 하나 시간에 회의실을 써야 한다.
void getGraph(const vector<pair<int,int> >& meetings) {
	int vars = meetings.size();

	// 그래프는 각 변수마다 두 개의 정점을 갖는다.
	adj.clear(); adj.resize(vars * 2); 

	for(int i = 0; i < vars; i += 2) {
		// 각 팀은 i번 회의나 j번 회의 둘 중 하나는 해야 한다.
		// (i or j) 절을 추가한다.
		int j = i+1;
		adj[i*2+1].push_back(j*2);
		adj[j*2+1].push_back(i*2);
	}	

	for(int i = 0; i < vars; i++) 
		for(int j = 0; j < i; j++) {
			// i번 회의와 j번 회의가 서로 겹칠 경우
			if(!disjoint(meetings[i], meetings[j])) {
				// i번 회의가 열리지 않거나, j번 회의가 열리지 않아야 한다.
				// (~i or ~j) 절을 추가한다.
				//printf("meetings %d and %d overlap\n", i, j);
				adj[i*2].push_back(j*2+1);
				adj[j*2].push_back(i*2+1);
			}
		}
}

// 각 정점의 컴포넌트 번호. 컴포넌트 번호는 0 부터 시작하며, 
// 같은 강결합 컴포넌트에 속한 정점들의 컴포넌트 번호가 같다.
vector<int> sccId, discovered, finished;

// 정점의 번호를 담는 스택
stack<int> st;

int sccCounter, vertexCounter;

// here 를 루트로 하는 서브트리에서 역방향 간선으로 닿을 수 있는 최소의 발견 순서를
// 반환한다.
int scc(int here) {
	int ret = discovered[here] = vertexCounter++;
	//printf("scc(%d) open. discovered = %d\n", here, discovered[here]);
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
	//printf("scc(%d) ends. ret %d\n", here, ret);
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
	sccId = discovered = finished = vector<int>(adj.size(), -1);
	// 카운터 초기화
	sccCounter = vertexCounter = 0;

	for(int i = 0; i < adj.size(); i++)
		if(discovered[i] == -1)
			scc(i);
	return sccId;
}


// meetings[] 가 각 팀이 하고 싶어하는 회의 시간의 목록일 때,
// 회의실 배정 문제를 해결한다. 각 회의를 할 것인지 여부를
// 나타내는 정수 배열을 반환하고, 답을 찾는 것이 불가능하다면
// 텅 빈 배열을 반환한다.
vector<int> solve(const vector<pair<int,int> >& meetings) {
	int n = meetings.size();

	// 2-SAT 문제로 바꾼 뒤 함축 그래프를 생성한다.
	getGraph(meetings);

	// 함축 그래프의 정점들을 강결합 컴포넌트별로 묶는다
	vector<int> label = tarjanSCC();

	// 이 SAT 문제를 푸는 것이 불가능한지 확인한다.
	for(int i = 0; i < 2*n; i += 2) 
		if(label[i] == label[i+1]) 
			return vector<int>();

	// SAT 문제를 푸는 것이 가능하다. 답을 생성하자!
	vector<int> value(2*n, -1);

	// Tarjan 알고리즘에서 SCC 번호는 위상 정렬의 역순으로 배정된다.
	// SCC 번호의 역순으로 각 정점을 정렬하면 위상 정렬 순서가 된다.
	vector<pair<int,int> > order;
	for(int i = 0; i < 2*n; i++) 
		order.push_back(make_pair(-label[i], i));
	sort(order.begin(), order.end());

	// 각 정점에 값을 배정한다.
	for(int i = 0; i < 2*n; ++i) {
		int vertex = order[i].second;
		int variable = vertex / 2, isTrue = vertex % 2;
		if(value[variable] != -1) continue;
		// not A 가 A 보다 먼저 나왔으면 A 는 참
		// A 가 not A 보다 먼저 나왔으면 A 는 거짓
		value[variable] = !isTrue;
	}

	return value;
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	int n;
    	cin >> n;
    	vector<pair<int,int> > meetings(2*n);
    	for(int i = 0; i < 2*n; i++) 
    		cin >> meetings[i].first >> meetings[i].second;
    	vector<int> value = solve(meetings);
    	if(value.empty()) {
    		cout << "IMPOSSIBLE" << endl;
    	}
		else {
			cout << "POSSIBLE" << endl;

			// 각 팀이 회의할 수 있는 시간을 출력한다
			for(int i = 0; i < 2*n; i += 2) 
				if(value[i] == 1)
					cout << meetings[i].first << " " 
						<< meetings[i].second << endl;
				else
					cout << meetings[i+1].first << " " 
						<< meetings[i+1].second << endl;
		}
	}
}

