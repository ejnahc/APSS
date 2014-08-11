#include<cstdio>
#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 입력 데이터
int n, y[100], x[100], radius[100];

// x^2 를 반환한다
int sqr(int x) { return x*x; }

// 두 성벽 a, b 의 중심점 간의 거리의 제곱을 반환한다
int sqrdist(int a, int b) { return sqr(y[a] - y[b]) + sqr(x[a] - x[b]); }

// 성벽 a 가 성벽 b 를 포함하는지 확인한다.
bool encloses(int a, int b) {
	return radius[a] > radius[b] && sqrdist(a, b) < sqr(radius[a] - radius[b]);
}

// 트리의 루트가 될 외성벽의 번호를 찾는다
int getRoot() {
	for(int i = 0; i < n; i++) {
		bool isRoot = true;
		for(int j = 0; j < n; j++)
			if(i != j && encloses(j, i)) {
				isRoot = false;
				break;
			}
		if(isRoot)
			return i;
	}
	return -1;
}

// "성벽" 트리에서 parent 가 child 의 부모인지 확인한다.
// parent 는 child 를 꼭 직접 포함해야 한다.
bool isChild(int parent, int child) {
	if(!encloses(parent, child)) return false;
	for(int i = 0; i < n; i++)
		if(i != parent && i != child && encloses(parent, i) && encloses(i, child))
			return false;
	return true;
}

struct TreeNode {
	vector<TreeNode*> children;
};

// root 성벽을 루트로 하는 트리를 생성한다
TreeNode* getTree(int root) {
	TreeNode* ret = new TreeNode();
	for(int ch = 0; ch < n; ++ch)
		if(isChild(root, ch))
			ret->children.push_back(getTree(ch));
	return ret;
}

int longest;

// root 를 루트로 하는 서브트리의 높이를 반환한다
int depth(TreeNode* root) {
	// 각 자식을 루트로 하는 서브트리의 높이를 계산한다
	vector<int> heights;
	for(int i = 0; i < root->children.size(); ++i)
		heights.push_back(depth(root->children[i]));
	// 만약 자식이 하나도 없다면 0 을 반환한다
	if(heights.empty()) return 0;
	sort(heights.begin(), heights.end());
	// root 를 최상위 노드로 하는 경로를 고려하자
	if(heights.size() >= 2)
		longest = max(longest, 2 + heights[heights.size()-2] + heights[heights.size()-1]);
	// 트리의 높이는 서브트리 높이의 최대값에 1 을 더해 계산한다
	return heights.back() + 1;
}

int solve() {
	// 우선 외성벽을 찾고 이 성벽을 루트로 하는 트리를 생성한다
	TreeNode* tree = getTree(getRoot());
	longest = 0;
	return max(longest, depth(tree));
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	cin >> n;
    	for(int i = 0; i < n; i++)
    		cin >> x[i] >> y[i] >> radius[i];
    	cout << solve() << endl;
    }
}

