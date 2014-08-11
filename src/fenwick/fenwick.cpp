#include<cassert>
#include<cstdlib>
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
	FenwickTree(int n) : tree(n+1) {}

	// A[0..pos] 의 부분 합을 구한다
	int sum(int pos) {
		// 인덱스를 1 부터 시작하는 것이라고 생각하자
		++pos;
		int ret = 0;
		while(pos > 0) {
			ret += tree[pos];
			// 다음 구간을 찾기 위해 최종 비트를 지운다
			pos &= (pos-1);
		}
		return ret;
	}

	// A[pos] 에 val 을 더한다
	void add(int pos, int val) {
		++pos;
		while(pos < tree.size()) {
			tree[pos] += val;
			pos += (pos & -pos);
		}
	}
};

int main() {
	const int n = 100;
	vector<int> arr(n);
	FenwickTree tree(n);
	for(int it = 0; it < 100000; it++) {
		if(it % 2 == 0) {
			int a = rand() % n, b = rand() % n;
			if(a > b) swap(a,b);
			int arrsum = 0;
			for(int i = 0; i <= b-a; i++) arrsum += arr[a + i];
			int treesum = tree.sum(b) - tree.sum(a-1);
			assert(arrsum == treesum);
		}
		else {
			int a = rand() % n, b = rand() % 100 - 50;
			arr[a] += b;
			tree.add(a,b);
		}
	}
	printf("all good.\n");
}

