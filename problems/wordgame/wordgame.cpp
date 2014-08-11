#include<algorithm>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 그래프의 인접 행렬 표현. adj[i][j] = i 와 j 사이의 간선의 수
vector<vector<int> > adj;
// graph[i][j] = i 로 시작해서 j 로 끝나는 단어의 목록
vector<string> graph[26][26];
// indegree[i] = i 로 시작하는 단어의 수
// outdegree[i] = i 로 끝나는 단어의 수
vector<int> indegree, outdegree;

void getGraph(const vector<string>& words) {
	for(int i = 0; i < 26; i++) 
		for(int j = 0; j < 26; j++) 
			graph[i][j].clear();
	adj = vector<vector<int> >(26, vector<int>(26, 0));
	indegree = outdegree = vector<int>(26, 0);
	for(int i = 0; i < words.size(); i++)  {
		int a = words[i][0] - 'a';
		int b = words[i][words[i].size()-1] - 'a';
		graph[a][b].push_back(words[i]);
		adj[a][b]++;
		outdegree[a]++;
		indegree[b]++;
	}
}

// 유향 그래프의 인접 행렬 adj 가 주어질 때 오일러 서킷을 
// 계산한다. 
void getEulerCircuit(int here, vector<int>& circuit) {
  for(int there = 0; there < adj.size(); ++there)
    while(adj[here][there] > 0) {
      adj[here][there]--; // 양쪽 간선을 모두 지운다
      getEulerCircuit(there, circuit);
    }
  circuit.push_back(here);
} 

// 현재 그래프의 오일러 트레일이나 서킷을 반환한다
vector<int> getEulerTrailOrCircuit() {
	vector<int> circuit;
	// 우선 트레일을 찾아본다: 시작점이 존재하는 경우
	for(int i = 0; i < 26; i++) 
		if(outdegree[i] == indegree[i]+1) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	// 아니면 서킷이니, 간선에 인접한 아무 정점에서나 시작한다
	for(int i = 0; i < 26; i++) 
		if(outdegree[i]) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	// 모두 실패한 경우 빈 배열을 반환한다
	return circuit;
}

string solve(const vector<string>& words) {
	getGraph(words);

	// 오일러 서킷이나 경로를 찾아낸다
	vector<int> circuit = getEulerTrailOrCircuit();

	// 모든 간선을 방문하지 못했으면 실패!
	if(circuit.size() != words.size() + 1) return "IMPOSSIBLE";

	// 아닌 경우 방문 순서를 뒤집은 뒤 간선들을 모아 문자열로 만들어 반환한다.
	reverse(circuit.begin(), circuit.end());
	string ret;
	for(int i = 1; i < circuit.size(); i++) {
		int a = circuit[i-1], b = circuit[i];
		if(ret.size()) ret += " ";
		ret += graph[a][b].back();
		graph[a][b].pop_back();
	}
	return ret;
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	int n;
    	cin >> n;
    	vector<string> words(n);
    	for(int i = 0; i < n; i++) cin >> words[i];
    	cout << solve(words) << endl;
    }
}

