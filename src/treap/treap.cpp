#include<set>
#include<cassert>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

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

void print(Node* node, int indent=0) {
	if(indent == 0) printf("====================\n");
	for(int i = 0; i < indent; i++) printf(" ");
	printf("=>");
	if(node == NULL) { printf("\n"); return; }
	printf("Node(key=%d, priority=%d, size=%d)\n", node->key, node->priority, node->size);
	print(node->left, indent+4);
	print(node->right, indent+4);

}

void randomTest() {
	set<int> a;
	Node* b = NULL;
	srand(12378);
	const int ITER = 10000000;
	for(int i = 0; i < ITER; i++) {
		int num = rand() % 10000;
		int op = rand() % 4;
		if(op == 0) {
			bool ae = a.count(num) > 0;
			bool be = exists(b, num);
			if(ae != be) {
				printf("a \n");
				for(typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
					printf("%d ", *it);
				printf("\n");
				print(b);

			}
			assert(ae == be);
		}
		else if(op == 1) {
			bool ae = a.count(num) > 0;
			if(ae) {
				a.erase(num);
				b = erase(b, num);
			}
			else {
				a.insert(num);
				b = insert(b, new Node(num));
			}
		}
		else if(op == 2) {
			set<int>::iterator it = a.lower_bound(num);
			Node* jt = lowerBound(b, num);
			if(it == a.end())
				assert(jt == NULL);
			else
				assert(*it == jt->key);
		}
		else {
			int k = rand() % a.size()+1;
			int skip = k, ak = 0;
			for(typeof(a.begin()) it = a.begin(); it != a.end(); ++it) {
				if(--skip == 0) {
					ak = *it;
					break;
				}
			}
			if(ak != kth(b, k)->key) {

				printf("a \n");
				for(typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
					printf("%d ", *it);
				printf("\n");
				print(b);
				printf("k = %d, ak = %d, kth = %d\n", k, ak, kth(b, k)->key);
				assert(false);
			}
			assert(countLessThan(b, ak) == k-1);
		}
	}
}

int main() {
	Node* root = NULL;
	const int arr[10] = { 5, 7, 6, 9, 2, 3, 10, 12, 4 };
	for(int i = 0; i < 10; i++) {
		root = insert(root, new Node(arr[i]));
		print(root);
	}
	for(int i = 0; i < 10; ++i) {
		assert(lowerBound(root, arr[i])->key == arr[i]);
	}
	assert(lowerBound(root, 1)->key == 2);
	assert(lowerBound(root, 8)->key == 9);
	assert(lowerBound(root, 11)->key == 12);
	assert(lowerBound(root, 13) == NULL);
	root = erase(root, 5);
	print(root);
	root = erase(root, 2);
	print(root);
	root = erase(root, 10);
	print(root);
	assert(lowerBound(root, 5)->key == 6);
	assert(lowerBound(root, 2)->key == 3);
	assert(lowerBound(root, 10)->key == 12);

	randomTest();

	printf("all good.\n");
}

