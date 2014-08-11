#include<queue>
#include<cstdlib>
#include<cassert>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct RNG {
	int seed, a, b;
	RNG(int _a, int _b) : a(_a), b(_b), seed(1983) {}
	int next() {
		int ret = seed;
		seed = ((seed * (long long)a) + b) % 20090711;
		return ret;
	}
};

typedef int KeyType;
// 트립의 한 노드를 저장한다
struct Node {
	// 노드에 저장된 키
	KeyType key;
	// 이 노드의 우선순위 (priority)
	// 이 노드를 루트로 하는 서브트리의 크기 (size)
	int priority, size;
	// 두 자식 노드의 포인터
	Node *left, *right;

	// 생성자에서 난수 우선순위를 생성하고, size 와 left/right 를 초기화한다
	Node(const KeyType& _key) : key(_key), priority(rand()),
		size(1), left(NULL), right(NULL) {
	}
	void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
	void setRight(Node* newRight) { right = newRight; calcSize(); }
	// size 멤버를 갱신한다
	void calcSize() {
		size = 1;
		if(left) size += left->size;
		if(right) size += right->size;
	}
};

// key 이상의 값 중 가장 작은 값의 위치를 반환한다
Node* lowerBound(Node* root, KeyType key) {
	if(root == NULL) return NULL;
	if(root->key < key) return lowerBound(root->right, key);
	Node* ret = lowerBound(root->left, key);
	if(!ret) ret = root;
	return ret;
}

bool exists(Node* root, KeyType key) {
	Node* node = lowerBound(root, key);
	return node != NULL && node->key == key;
}

// root 를 루트로 하는 트리 중에서 k번째 원소를 반환한다
Node* kth(Node* root, int k) {
	int ls = (root->left ? root->left->size : 0);
	int rs = (root->right ? root->right->size : 0);
	if(k <= ls) return kth(root->left, k);
	if(k == ls + 1) return root;
	return kth(root->right, k - ls - 1);
}

// key 보다 작은 키값의 수를 반환한다
int countLessThan(Node* root, KeyType key) {
	if(root == NULL) return 0;
	if(root->key >= key)
		return countLessThan(root->left, key);
	int ls = (root->left ? root->left->size : 0);
	return ls + 1 + countLessThan(root->right, key);
}

typedef pair<Node*,Node*> NodePair;

// root 를 루트로 하는 트립을 key 미만의 값과 이상의 값을 갖는
// 두 개의 트립으로 분리한다.
NodePair split(Node* root, KeyType key) {
	if(root == NULL) return NodePair(NULL, NULL);
	// 루트가 key 미만이면 오른쪽의 일부를 잘라낸다
	if(root->key < key) {
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	// 루트가 key 이상이면 왼쪽의 일부를 잘라낸다
	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}

// root 를 루트로 하는 트립에 새 노드 node 를 삽입한 뒤 결과 트립의
// 루트를 반환한다.
Node* insert(Node* root, Node* node) {
	if(root == NULL) return node;
	// node 가 루트를 대체해야 한다: 해당 서브트립을 반으로 잘라
	// 각각 자손으로 한다
	if(root->priority < node->priority) {
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	else if(node->key < root->key)
	    root->setLeft(insert(root->left, node));
	else
		root->setRight(insert(root->right, node));
	return root;
}

// a 와 b 가 두 개의 트립이고, max(a) < min(b) 일때 이 둘을 합친다
Node* merge(Node* a, Node* b) {
	if(a == NULL) return b;
	if(b == NULL) return a;

	if(a->priority < b->priority) {
		b->setLeft(merge(a, b->left));
		return b;
	}
	a->setRight(merge(a->right, b));
	return a;
}

// root 를 루트로 하는 트립에서 key 를 지운다
Node* erase(Node* root, KeyType key) {
	if(root == NULL) return root;
	// root 를 지우고 양 서브트립을 합친 뒤 반환한다
	if(root->key == key) {
		Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}
	if(key < root->key)
		root->setLeft(erase(root->left, key));
	else
		root->setRight(erase(root->right, key));
	return root;
}

// rng 가 생성하는 첫 n개의 난수를 수열에 추가하며 중간값을 구한다
int runningMedian(int n, RNG rng) {
	Node* root = NULL;
	int ret = 0;
	for(int cnt = 1; cnt <= n; ++cnt) {
		root = insert(root, new Node(rng.next()));
		int median = kth(root, (cnt + 1) / 2)->key;
		ret = (ret + median) % 20090711;
	}
	return ret;
}

int runningMedian2(int n, RNG rng) {
	priority_queue<int, vector<int>, less<int> > maxHeap;
	priority_queue<int, vector<int>, greater<int> > minHeap;
	int ret = 0;
	// 반복문 불변 조건:
	// 1. maxHeap 의 크기는 minHeap 의 크기와 같거나 1 더 크다
	// 2. maxHeap.top() <= minHeap.top()
	for(int cnt = 1; cnt <= n; ++cnt) {
		// 우선 1번 불변 조건부터 만족시킨다
		if(maxHeap.size() == minHeap.size())
			maxHeap.push(rng.next());
		else
			minHeap.push(rng.next());
		// 2번 불변 조건이 깨졌을 경우 복구하자
		if(!minHeap.empty() && !maxHeap.empty() &&
				minHeap.top() < maxHeap.top()) {
			int a = maxHeap.top(), b = minHeap.top();
			maxHeap.pop(); minHeap.pop();
			maxHeap.push(b);
			minHeap.push(a);
		}
		ret = (ret + maxHeap.top()) % 20090711;
	}
	return ret;
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
		int n;
		unsigned a, b;
		cin >> n >> a >> b;
		RNG rng1(a,b), rng2(a,b);
		{
		int a = runningMedian(n, rng1);
		int b = runningMedian2(n, rng2);
		if(a != b) {
			printf("n = %d a = %d b = %d\n", n,a,b);
		}
		assert(a == b);
    	printf("%d\n", a);
		}
    }
}

