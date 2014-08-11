#include<algorithm>
#include<map>
#include<queue>
#include<cstdio>
#include<cstring>
#include<cassert>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 알파벳 소문자를 저장하는 경우 각 노드는 26개의 자손을 가질 수 있다
const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'a'; }

// 트라이의 한 노드를 나타내는 객체
struct TrieNode {
	TrieNode* children[ALPHABETS];
	TrieNode* next[ALPHABETS];

	// 현 위치에서 끝나는 문자열의 번호
	int terminal;

	// 트라이 노드의 번호
	int no;

	// 이 노드에서 매칭이 실패했을 때 이 곳으로 가서 계속한다.
	// 이 노드에 대응되는 문자열의 접미사이면서 트라이에 포함된 최대 문자열.
	TrieNode* fail;
	// 이 노드가 방문되었을 때 등장하는 문자열들의 번호
	vector<int> output;

	TrieNode() : terminal(-1) {
		memset(children, 0, sizeof(children));
	}

	~TrieNode() {
		for(int i = 0; i < ALPHABETS; i++)
			if(children[i])
				delete children[i];
	}

	// 이 노드를 루트로 하는 트라이에 번호가 id 인 문자열 key 를 추가한다
	void insert(const char* key, int id) {
		// 문자열이 끝나면 terminal 만 참으로 바꾸고 종료
		if(*key == 0)
			terminal = id;
		else {
			int next = toNumber(*key);
			// 해당 자식 노드가 없다면 생성한다
			if(children[next] == NULL)
				children[next] = new TrieNode();
			// 해당 자식 노드로 재귀호출
			children[next]->insert(key + 1, id);
		}
	}

	TrieNode* find(const char* key) {
		if(*key == 0) return this;
		int next = toNumber(*key);
		if(children[next] == NULL) return NULL;
		return children[next]->find(key+1);
	}
};

// 트라이가 주어질 때 각 노드에 대해 실패 연결과 출력 문자열 목록을 계산한다.
void computeFailFunc(TrieNode* root) {
	// 루트에서부터 시작해 한 단계씩 아래로 내려가며 각 노드의 실패 연결을 계산한다.
	queue<TrieNode*> q;
	// 루트의 실패 연결은 자기 자신
	root->fail = root;
	q.push(root);

	while(!q.empty()) {
		TrieNode* here = q.front();
		q.pop();
		// here 의 모든 노드에 대해 실패 연결을 계산하고 이들을 큐에 넣는다
		for(int edge = 0; edge < ALPHABETS; ++edge) {
			TrieNode* child = here->children[edge];
			if(!child) continue;

			// 1레벨 노드의 실패 연결은 항상 루트
			if(here == root)
				child->fail = root;
			else {
				// 아닌 경우 부모의 실패 연결을 따라가면서 실패 연결을 찾는다
				TrieNode* t = here->fail;
				while(t != root && t->children[edge] == NULL)
					t = t->fail;
				if(t->children[edge]) t = t->children[edge];
				child->fail = t;
			}
			// output 배열을 계산: 이 위치에서 끝나는 문자열이 있으면 추가한다
			child->output = child->fail->output;
			if(child->terminal != -1)
				child->output.push_back(child->terminal);
			q.push(child);
		}
	}
}

const int MOD = 10007;
int cache[101][1001];

// 앞으로 length 글자를 더 만들어야 하는데, 아호-코라식 알고리즘의
// 현재 상태가 state 에 주어질 때 IDS 에 걸리지 않는 문자열의 수는?
int count(int length, TrieNode* state) {
	// 기저 사례: 이 상태에 문자열이 출현하면 곧장 종료
	if(state->output.size()) return 0;
	// 기저 사례: 문자열을 전부 만든 경우
	if(length == 0) return 1;
	int& ret = cache[length][state->no];
	if(ret != -1) return ret;
	ret = 0;
	for(int letter = 0; letter < ALPHABETS; letter++) {
		ret += count(length-1, state->next[letter]);
		ret %= MOD;
	}
	return ret;
}


// 상태간의 전이 테이블을 next[] 에 채운다. computeFailFunc()
// 를 통해 이미 실패 함수가 계산되어 있다고 가정한다.
void computeTransition(TrieNode* here, int& nodeCounter) {
	// 0 에서 시작하는 번호를 매긴다: table[] 의 인덱스
	here->no = nodeCounter++;
	// here 뒤에 글자 chr 를 붙였을 때 어느 상태로 가는가?
	for(int chr = 0; chr < ALPHABETS; chr++) {
		// next[] 값을 계산해 저장한다
		TrieNode* next = here;
		while(next != next->fail && next->children[chr] == NULL)
			next = next->fail;
		if(next->children[chr]) next = next->children[chr];
		here->next[chr] = next;

		// 재귀적으로 모든 노드에 대해 전이 테이블을 계산한다
		if(here->children[chr])
			computeTransition(here->children[chr], nodeCounter);
	}
}

int solve(int length, const vector<string>& patterns) {
	// 트라이를 만든다
	TrieNode trie;
	for(int i = 0; i < patterns.size(); i++)
		trie.insert(patterns[i].c_str(), i);

	// 실패 함수를 계산
	computeFailFunc(&trie);

	// 상태 전이 테이블을 생성한다
	int t = 0;
	computeTransition(&trie, t);

	// 동적 계획법을 위한 캐시를 초기화
	memset(cache, -1, sizeof(cache));
	return count(length, &trie);
}


int main() {
	int cases;
	cin >> cases;
	while(cases--) {
		int n, m;
		cin >> n >> m;
		vector<string> patterns(m);
		for(int i = 0; i < m; i++)
			cin >> patterns[i];
		cout << solve(n, patterns) << endl;
	}
}

