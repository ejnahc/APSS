#include<sstream>
#include<algorithm>
#include<cassert>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 그래프의 인접 리스트 표현
vector<vector<int> > adj;
// 각 정점을 방문했는지 여부를 나타낸다
vector<bool> visited;

// 깊이 우선 탐색을 구현한다
void dfs(int here) {
	cout << "DFS visits " << here << endl;
	visited[here] = true;
	// 모든 인접 정점을 순회하면서
	for(int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];
		// 아직 방문한 적 없다면 방문한다
		if(!visited[there])
			dfs(there);
	}
}

// discovered[i] = i번 정점의 발견 순서
// finished[i] = dfs(i) 가 종료했으면 1, 아니면 0
vector<int> discovered, finished;
// 지금까지 발견한 정점의 수.
int counter;

void dfs2(int here) {
	discovered[here] = counter++;
	// 모든 인접 정점을 순회하면서
	for(int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];
		cout << "(" << here << "," << there << ") is a ";
		// 아직 방문한 적 없다면 방문한다.
		if(discovered[there] == -1) {
			cout << "tree edge" << endl;
			dfs2(there);
		}
		// 만약 there 가 here 보다 늦게 발견됐으면 there 는
		// here 의 후손이다. 순방향 간선 발견!
		else if(discovered[here] < discovered[there])
			cout << "forward edge" << endl;
		// 만약 dfs2(there) 가 아직 종료하지 않았으면 there
		// 는 here 의 선조다. 역방향 간선 발견!
		else if(finished[there] == 0)
			cout << "back edge" << endl;
		// 이외의 경우는 모두 교차 간선
		else
			cout << "cross edge" << endl;

	}
	finished[here] = 1;
}


// 그래프의 인접 행렬 표현
//vector<vector<int> > adj;

// 무향 그래프의 인접 행렬 adj 가 주어질 때 오일러 서킷을
// 계산한다.
void getEulerCircuit(int here, vector<int>& circuit) {
	for(int there = 0; there < adj.size(); ++there)
		while(adj[here][there] > 0) {
			adj[here][there]--;
			adj[there][here]--;
			getEulerCircuit(there, circuit);
		}
	circuit.push_back(here);
}


// 모든 정점을 방문한다
void dfsAll() {
	// visited 를 모두 false 로 초기화한다
	visited = vector<bool>(adj.size(), false);

	// 모든 정점을 순회하면서, 아직 방문한 적 없으면
	// 방문한다
	for(int i = 0; i < adj.size(); ++i)
		if(!visited[i])
			dfs(i);
}


void testEuler() {

	adj = vector<vector<int> >(4, vector<int>(4, 0));
	adj[0][1] = 1;
	adj[0][2] = 2;
	adj[0][3] = 1;
	adj[1][2] = 2;
	adj[1][3] = 1;
	adj[2][3] = 2;
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < i; j++)
			adj[i][j] = adj[j][i];
	vector<int> circuit;
	getEulerCircuit(0, circuit);
	for(int i = 0; i < circuit.size(); i++) printf("%d ", circuit[i]);
	printf("\n");
	assert(circuit.size() == 10);
	const int expected[] = { 0, 1, 2, 0, 2, 1, 3, 2, 3, 0 };
	reverse(circuit.begin(), circuit.end());
	assert(vector<int>(expected, expected+10) == circuit);
}

void testTree() {
	adj.clear();
	adj.resize(7);
	string s("0 5 0 6 5 6 5 3 6 3 0 4 4 2 2 0 0 1 1 2");
	istringstream inp(s);
	int a, b;
	while(inp >> a >> b) adj[a].push_back(b);
	discovered = vector<int>(7, -1);
	finished = vector<int>(7, 0);
	dfs2(0);
}

int main() {
	testEuler();
	testTree();

	printf("all good.\n");
}

