#include<algorithm>
#include<cstdlib>
#include<cassert>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 펜윅 트리의 구현. 가상의 배열 A[] 의 부분 합을
// 빠르게 구현할 수 있도록 한다. 초기화시에는 A[] 의
// 원소가 전부 0 이라고 생각한다.
struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n) : tree(n) {}

	// A[0..pos] 의 부분 합을 구한다
	int sum(int pos) {
		// 인덱스를 1 부터 시작하는 것이라고 생각하자
		++pos;
		int ret = 0;
		while(pos > 0) {
			// 트리의 실제 인덱스는 여전히 [0,n-1] 이므로
			// 접근할 때 1 씩 빼준다
			ret += tree[pos-1];
			// 다음 구간을 찾기 위해 최종 비트를 지운다
			pos &= (pos-1);
		}
		return ret;
	}

	// A[pos] 에 val 을 더한다
	void add(int pos, int val) {
		++pos;
		while(pos <= tree.size()) {
			tree[pos-1] += val;
			pos += (pos & -pos);
		}
	}
};

// 펜윅 트리를 이용해 문제를 해결한다
long long countMoves(const vector<int>& A) {
	FenwickTree tree(1000000);
	long long ret = 0;
	for(int i = 0; i < A.size(); i++) {
		ret += tree.sum(999999) - tree.sum(A[i]);
		tree.add(A[i], 1);
	}
	return ret;
}

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

void print(Node* node, int indent=0) {
	if(indent == 0) printf("====================\n");
	for(int i = 0; i < indent; i++) printf(" ");
	printf("=>");
	if(node == NULL) { printf("\n"); return; }
	printf("Node(key=%d, priority=%d, size=%d)\n", node->key, node->priority, node->size);
	print(node->left, indent+4);
	print(node->right, indent+4);

}

// 만들었던 트리를 지운다
void deleteTree(Node* node) {
	if(node == NULL) return;
	deleteTree(node->left);
	deleteTree(node->right);
	delete node;
}

// 트립을 이용해 문제를 해결한다
long long countMoves2(const vector<int>& A) {
	Node* root = NULL;
	long long ret = 0;
	for(int i = 0; i < A.size(); i++)  {
		ret += i - countLessThan(root, A[i]+1);
		root = insert(root, new Node(A[i]));
	}
	deleteTree(root);
	return ret;
}

// A[left..right] 를 재귀적으로 병합 정렬하고,
// 해당 범위 내의 inversion 의 수를 반환한다
long long countMoves3(vector<int>& A, int left, int right) {
	// 기저 사례: 구간의 길이가 1 이라면 이미 정렬되었고, inversion 도 없다
	if(left == right) return 0;

	// 반으로 나눠서 부분 정복
	int mid = (left + right) / 2;
	long long ret = countMoves3(A, left, mid) + countMoves3(A, mid+1, right);

	// 임시 배열에 정렬된 두 부분 배열을 합친다
	vector<int> tmp(right - left + 1);
	int tmpIndex = 0, leftIndex = left, rightIndex = mid+1;
	while(leftIndex <= mid || rightIndex <= right) {
		if(leftIndex <= mid && (rightIndex > right || A[leftIndex] <= A[rightIndex]))
			tmp[tmpIndex++] = A[leftIndex++];
		else {
			// A[rightIndex] 는 왼쪽 부분 배열에 남아 있는 모든 수보다 작다
			// 이 수들만큼 inversion 을 더해준다
			ret += mid - leftIndex + 1;
			tmp[tmpIndex++] = A[rightIndex++];
		}
	}
	// tmp 에 합친 결과를 A 로 다시 복사한다
	for(int i = 0; i < tmp.size(); ++i)
		A[left + i] = tmp[i];
	return ret;
}

int main() {
	/*
    int cases;
    scanf("%d", &cases);
    for(int cc = 0; cc < cases; ++cc) {
    	int n;
    	scanf("%d", &n);
    	vector<int> A(n);
    	for(int i = 0; i < n; i++)
    		scanf("%d", &A[i]);
    	printf("%Ld\n", countMoves(A));
    }
    */

    for(int n = 6; n <= 10; ++n) {
    	vector<int> perm(n);
    	for(int i = 0; i < n; i++) perm[i] = rand() % n;
    	sort(perm.begin(), perm.end());
    	do {
    		long long A = countMoves(perm);
    		long long b = countMoves2(perm);
    		vector<int> copy = perm;
    		long long c = countMoves3(copy, 0, n-1);
    		if(A != b || A != c) {
    			printf("shit\n");
    			for(int i = 0; i < n; i++)
    				printf("%d ", perm[i]);
    			printf("=> A=%Ld b=%Ld\n", A, b);
    			return 0;

    		}
    		assert(A == b);
    	} while(next_permutation(perm.begin(), perm.end()));
    	printf("passed all perms for n=%d\n", n);
    }
    printf("all good.\n");
}

