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
int toNumber(char ch) { return ch - 'A'; }

struct LinkedListNode {

	int elem;
	LinkedListNode* next;

	LinkedListNode(int _elem, LinkedListNode* _next) : elem(_elem), next(_next) {
	}

};

// 트라이의 한 노드를 나타내는 객체
struct TrieNode {
	TrieNode* children[ALPHABETS];
	// 이 노드가 종료 노드인가?
	bool terminal;

	TrieNode() : terminal(false) {
		memset(children, 0, sizeof(children));
	}

	~TrieNode() {
		for(int i = 0; i < ALPHABETS; i++)
			if(children[i])
				delete children[i];
	}

	// 이 노드를 루트로 하는 트라이에 문자열 key 를 추가한다.
	void insert(const char* key) {
		// 문자열이 끝나면 terminal 만 참으로 바꾸고 종료
		if(*key == 0)
			terminal = true;
		else {
			int next = toNumber(*key);
			// 해당 자식 노드가 없다면 생성한다
			if(children[next] == NULL)
				children[next] = new TrieNode();
			// 해당 자식 노드로 재귀호출
			children[next]->insert(key + 1);
		}
	}

	// 이 노드를 루트로 하는 트라이에 문자열 key 와 대응되는 노드를 찾는다.
	// 없으면 NULL 을 반환한다.
	TrieNode* find(const char* key) {
		if(*key == 0) return this;
		int next = toNumber(*key);
		if(children[next] == NULL) return NULL;
		return children[next]->find(key+1);
	}
};

// 트라이의 한 노드를 나타내는 객체
struct TrieDict {
	TrieDict* children[ALPHABETS];
	// 현 위치에서 끝나는 문자열의 번호
	int terminal;

	// 이 노드에서 매칭이 실패했을 때 이 곳으로 가서 계속한다.
	// 이 노드에 대응되는 문자열의 접미사이면서 트라이에 포함된 최대 문자열.
	TrieDict* fail;
	// 이 노드가 방문되었을 때 등장하는 문자열들의 번호
	LinkedListNode* output;

	TrieDict() : terminal(-1), output(NULL) {
		memset(children, 0, sizeof(children));
	}

	~TrieDict() {
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
				children[next] = new TrieDict();
			// 해당 자식 노드로 재귀호출
			children[next]->insert(key + 1, id);
		}
	}

	TrieDict* find(const char* key) {
		if(*key == 0) return this;
		int next = toNumber(*key);
		if(children[next] == NULL) return NULL;
		return children[next]->find(key+1);
	}
};

void calcFailureFunction(TrieDict* root) {
	queue<TrieDict*> q;
	// 루트의 fail 함수는 자기 자신
	root->fail = root;
	q.push(root);
	while(!q.empty()) {
		TrieDict* here = q.front();
		q.pop();
		for(int edge = 0; edge < ALPHABETS; ++edge) {
			if(!here->children[edge]) continue;

			TrieDict* child = here->children[edge];

			// 1레벨 노드의 실패 연결은 항상 루트
			if(here == root)
				child->fail = root;
			else {
				TrieDict* t = here->fail;
				while(t != root && t->children[edge] == NULL)
					t = t->fail;
				if(t->children[edge]) t = t->children[edge];
				child->fail = t;
			}
			if(child->terminal != -1)
				child->output = new LinkedListNode(child->terminal,
						child->fail->output);
			else
				child->output = child->fail->output;

			q.push(child);
		}
	}
}

template<class CALLBACK>
void ahoCorasick(const string& s, TrieDict* trie, CALLBACK callback) {
	TrieDict* state = trie;
	for(int i = 0; i < s.size(); i++) {
		int chr = toNumber(s[i]);
		while(state != trie && state->children[chr] == NULL)
			state = state->fail;
		if(state->children[chr]) state = state->children[chr];
		for(LinkedListNode* t = state->output; t; t = t->next)
			callback(i, t->elem);
	}
}


void naiveTest() {
	TrieDict* trie = new TrieDict();
	trie->insert("HELLO",1);
	assert(1 == trie->find("HELLO")->terminal);
	assert(NULL == trie->find("HELLOB"));
	assert(-1 == trie->find("HELL")->terminal);
	delete trie;
}

TrieDict* find(TrieDict* node, const char* key) {
	if(*key == 0) return node;
	int next = toNumber(*key);
	if(node->children[next] == NULL) return NULL;
	return find(node->children[next], key+1);
}

vector<pair<int,int> > accumulated;
void test(int a, int b) {
	printf("pattern %d at pos %d\n", b, a);
	accumulated.push_back(make_pair(a,b));
}


void acTest() {
	TrieDict* trie = new TrieDict();
	trie->insert("SHE", 0);
	trie->insert("HE", 1);
	trie->insert("HERS", 2);
	trie->insert("HIS", 3);

	calcFailureFunction(trie);

	map<TrieDict*, string> nodeToStr;
	queue<pair<TrieDict*,string> > q;
	q.push(make_pair(trie, ""));
	while(!q.empty()) {
		TrieDict* here = q.front().first;
		string label = q.front().second;
		q.pop();
		nodeToStr[here] = label;
		printf("[%s] => [%s]\n", label.c_str(), nodeToStr[here->fail].c_str());
		for(int i = 0; i < ALPHABETS; i++) {
			if(here->children[i])
				q.push(make_pair(here->children[i], label + char('A' + i)));
		}
	}
	assert(nodeToStr[find(trie, "SH")->fail] == "H");
	assert(nodeToStr[find(trie, "SHE")->fail] == "HE");
	assert(nodeToStr[find(trie, "HIS")->fail] == "S");
	assert(nodeToStr[find(trie, "HERS")->fail] == "S");

	//                  012345678
	ahoCorasick(string("HERSHISHE"), trie, test);
	// HE at 1
	// HERS at 3
	// HIS at 6
	// SHE at 8
	// HE at 8
	assert(accumulated.size() == 5);
	assert(accumulated[0] == make_pair(1, 1));
	assert(accumulated[1] == make_pair(3, 2));
	assert(accumulated[2] == make_pair(6, 3));
	assert(accumulated[3] == make_pair(8, 0));
	assert(accumulated[4] == make_pair(8, 1));

}

int main() {
	naiveTest();
	acTest();
	printf("all good.\n");
}

