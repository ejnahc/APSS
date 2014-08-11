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

// 트리의 정보
int n;
vector<int> child[100000];
// 트리의 번호와 일련 번호 사이의 대응 관계
int no2serial[100000], serial2no[100000];
// 각 노드가 trip 에 처음 등장하는 위치, 그리고 각 노드의 깊이
int locInTrip[100000], depth[100000];
// 다음 일련 번호
int nextSerial;

void traverse(int here, int d, vector<int>& trip) {
	// traverse() 가 처음 방문하자마자 일련 번호를 부여한다.
	// 이렇게 하면 항상 부모는 자손보다 작은 일련 번호를 갖게 된다.
	no2serial[here] = nextSerial;
	serial2no[nextSerial] = here;
	++nextSerial;

	// 깊이 계산
	depth[here] = d;

	// trip 에 현재 노드의 일련 번호를 추가한다
	locInTrip[here] = trip.size();
	trip.push_back(no2serial[here]);

	// 모든 자식 노드를 방문
	for(int i = 0; i < child[here].size(); i++)  {
		traverse(child[here][i], d+1, trip);

		// 자식노드를 방문하고 현재 노드로 돌아올 때마다 다시 추가하기
		trip.push_back(no2serial[here]);
	}
}

// 트리를 순회하며 각종 필요한 정보를 계산하고, RMQ 구간 트리를
// 만들어 반환한다.
RMQ* prepareRMQ() {
	nextSerial = 0;
	// 순회 과정에서 만나는 점들의 일련 번호를 담는다
	vector<int> trip;
	traverse(0, 0, trip);
	return new RMQ(trip);
}

// u 와 v 사이의 거리를 계산한다
int distance(RMQ* rmq, int u, int v) {
	// trip[] 배열에서 u 와 v 의 첫 출현 위치를 찾는다
	int lu = locInTrip[u], lv = locInTrip[v];
	if(lu > lv) swap(lu, lv);
	// rmq 는 u 와 v 의 최소 공통 조상의 일련번호를 반환한다
	int lca = serial2no[rmq->query(lu, lv)];
	return depth[u] + depth[v] - 2 * depth[lca];
}

int main() {
	int cases;
	scanf("%d", &cases);
	while(cases--) {
		int queries;
		scanf("%d %d", &n, &queries);
		for(int i = 0; i < n; i++) child[i].clear();
		for(int i = 1; i < n; i++) {
			int parent;
			scanf("%d", &parent);
			child[parent].push_back(i);
		}

		RMQ* rmq = prepareRMQ();
		for(int i = 0; i < queries; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			printf("%d\n", distance(rmq, a, b));
		}
		delete rmq;
	}
}
