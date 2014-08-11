#include<cstdlib>
#include<algorithm>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
#include<limits>
using namespace std;

const int INT_MAX = numeric_limits<int>::max();

// 배열의 구간 최소 쿼리를 해결하기 위한 구간 트리의 구현
struct RMQ {
	// 배열의 길이
	int n;
	// 각 구간의 최소값
	vector<int> rangeMin;
	RMQ(const vector<int>& array) {
		n = array.size();
		rangeMin.resize(n * 4);
		init(array, 1, 0, n-1);

	}
	// node 노드가 array[left..right] 배열을 표현할 때
	// node 를 루트로 하는 서브트리를 초기화하고, 이 구간의 최소값을 반환한다
	int init(const vector<int>& array, int node, int left, int right) {
		if(left == right)
			return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		return rangeMin[node] = min(init(array, node*2, left, mid),
								    init(array, node*2+1, mid+1, right));
	}

	// array[index] = newValue 로 바뀌었을 때 node 를 루트로 하는 구간 트리를
	// 업데이트하고 노드가 표현하는 구간의 최소값을 반환한다
	int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
		// index 가 노드가 표현하는 구간과 상관없는 경우엔 무시한다
		if(index < nodeLeft || nodeRight < index) return rangeMin[node];
		// 트리의 리프까지 내려온 경우
		if(nodeLeft == nodeRight) return rangeMin[node] = newValue;
		int mid = (nodeLeft + nodeRight) / 2;
		return rangeMin[node] = min(update(index, newValue, node*2, nodeLeft, mid),
				update(index, newValue, node*2+1, mid+1, nodeRight));
	}

	// update() 를 외부에서 호출하기 위한 인터페이스
	int update(int index, int newValue) { return update(index, newValue, 1, 0, n-1); }

	// node 가 표현하는 범위 array[nodeLeft..nodeRight] 가 주어질 때
	// 이 범위와 array[left..right] 의 교집합의 최소값을 구한다
	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		// 두 구간이 겹치지 않으면 아주 큰 값을 반환한다: 무시됨
		if(right < nodeLeft || nodeRight < left) return INT_MAX;
		// node 가 표현하는 범위가 array[left..right] 에 완전히 포함되는 경우
		if(left <= nodeLeft && nodeRight <= right) return rangeMin[node];
		// 양쪽 구간을 나눠서 푼 뒤 결과를 합친다
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node*2, nodeLeft, mid),
			   	   query(left, right, node*2+1, mid+1, nodeRight));
	}

	// query() 를 외부에서 호출하기 위한 인터페이스
	int query(int left, int right) { return query(left, right, 1, 0, n-1); }
};

template<typename TRAITS>
struct SegmentTree {
	TRAITS processor;

	typedef typename TRAITS::ELEM ELEM;
	typedef typename TRAITS::RESULT RESULT;

	int n;
	const vector<ELEM>& A;
	vector<RESULT> result;

	SegmentTree(const vector<ELEM>& _A): n(_A.size()), A(_A), result(_A.size() * 4 + 10) {
		init(0, n-1, 1);
	}

	void init(int left, int right, int node) {
		if(left == right) {
			result[node] = processor.single(A[left]);
			return;
		}
		int mid = (left + right) / 2;
		init(left, mid, node*2);
		init(mid+1, right, node*2+1);
		result[node] = processor.combine(result[node*2], result[node*2+1]);
	}

	void update(int index, const ELEM& newValue, int node, int nodeLeft, int nodeRight) {
		if(index < nodeLeft || nodeRight < index) return;
		if(nodeLeft == nodeRight) {
			result[node] = processor.single(newValue);
			return;
		}
		int mid = (nodeLeft + nodeRight) / 2;
		update(index, newValue, node*2, nodeLeft, mid);
		update(index, newValue, node*2+1, mid+1, nodeRight);
		result[node] = processor.combine(result[node*2], result[node*2+1]);
	}

	void update(int index, const ELEM& newValue) {
		update(index, newValue, 1, 0, n-1);
	}

	RESULT query(int left, int right, int node, int nodeLeft, int nodeRight) {
		left = max(left, nodeLeft); right = min(right, nodeRight);
		if(left > right) return processor.null();
		if(left == nodeLeft && right == nodeRight) return result[node];
		int mid = (nodeLeft + nodeRight) / 2;
		return processor.combine(query(left, right, node*2, nodeLeft, mid),
				query(left, right, node*2+1, mid+1, nodeRight));
	}

	RESULT query(int left, int right) {
		return query(left, right, 1, 0, n-1);
	}
};

struct MaxPairTraits {
	typedef int ELEM;
	typedef pair<int,int> RESULT;
	int null() { return numeric_limits<int>::min(); }
	RESULT combine(const RESULT& a, const RESULT& b) {
		int x = max(a.first, b.first);
		int y = min(a.first, b.first), z = max(a.second, b.second);
		return RESULT(x, max(y, z));
	}
	RESULT single(int elem) { return RESULT(elem, null()); }
};

// ranged sum 에 쓰기
struct SumTraits {
	typedef int ELEM;
	typedef int RESULT;
	int null() { return 0; }
	int combine(int a, int b) { return a+b; }
	int single(int elem) { return elem; }
};

// ranged minimum query 에 쓰기
struct MinTraits {
	typedef int ELEM;
	typedef int RESULT;
	int null() { return INT_MAX; }
	int combine(int a, int b) { return min(a, b); }
	int single(int elem) { return elem; }
};

int main() {

	const int MAXN = 100000;
	for(int N = 10; N <= MAXN; N *= 10) {
		vector<int> test(N);
		for(int i = 0; i < N; i++) test[i] = rand() % 1000;
		RMQ rmq(test);
		SegmentTree<MinTraits> rmq2(test);
		const int TESTS = 100000;
		for(int i = 0; i < TESTS; i++) {
			int a = rand() % N;
			int b = rand() % N;
			if(a > b) swap(a,b);
			int A = rmq.query(a,b);
			int B = *min_element(test.begin() + a, test.begin() + b + 1);
			int C = rmq2.query(a,b);
			if(A != B || A != C) {
				printf("fuck\n");
				for(int i = 0; i < N; i++) {
					printf("%d ", test[i]);
				}
				printf("\n");
				printf("a=%d, b=%d, rmq=%d, brute=%d, rmq2=%d\n",
						a,b,A,B,C);
				return 0;
			}
		}
		printf("passed %d tests on N=%d\n", TESTS, N);
	}
	printf("all good.\n");

}
