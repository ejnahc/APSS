#include<cassert>
#include<functional>
#include<vector>
#include<algorithm>
using namespace std;

class IntMaxHeap {
	public:
		IntMaxHeap();
		IntMaxHeap(const vector<int>& contents);
		void insert(int x);
		int extractMax();
		int size() const;
	private:
		vector<int> heap;
};

// x 노드의 부모, 왼쪽, 오른쪽 자손 노드들의 번호를 반환한다
int parentOf(int x) { return (x-1) / 2; }
int leftOf(int x) { return x*2 + 1; }
int rightOf(int x) { return x*2 + 2; }

IntMaxHeap::IntMaxHeap() {
}

IntMaxHeap::IntMaxHeap(const vector<int>& contents) {
}

int IntMaxHeap::size() const {
	return heap.size();
}

void IntMaxHeap::insert(int x) {
	// 텅 빈 구멍을 만든다.
	heap.resize(heap.size() + 1);
	int hole = heap.size() - 1, parent = parentOf(hole);
	while(hole > 0 && heap[parent] < x) {
		// 루프 불변 조건: 
		// 1. hole 이 가리키는 노드는 비어 있고, 루트가 아니다.
		// 2. parent 는 hole 의 부모 노드를 가리킨다.
		// 3. hole 에게 자손이 있다면, 그 자손이 가진 값은 x 보다 작다.
		// 4. parent 가 가진 값은 x 보다 작을 수도 있다.
		heap[hole] = heap[parent];
		hole = parent;
		parent = parentOf(hole);
	}
	heap[hole] = x;
}

int IntMaxHeap::extractMax() {
	int ret = heap[0];				// 결과값을 확보해 둔다.
	heap[0] = heap.back(); 			// 맨 끝에 있는 값을 루트로 옮기고, 맨 마지막 노드를 제거한다.
	heap.pop_back();
	int here = 0;
	while(leftOf(here) < heap.size()) 
		// 루프 불변 조건: heap[here] 는 그 자손보다 작을 수 있지만,
		// 그 외의 위치에서는 모두 힙의 조건이 만족된다. 
		// here 는 트리의 잎 (Leaf) 이 아님.
		
		// 현재 위치, 왼쪽 자손, 오른쪽 자손 중 가장 큰 값을 찾는다.
		int maxNode = here;
		if(heap[leftOf(here)] > heap[here])
			maxNode = leftOf(here);
		// 왼쪽 자손은 존재하더라도, 오른쪽 자손은 존재하지 않을 수도 있다.
		if(rightOf(here) < heap.size() && 
		   heap[rightOf(here)] > heap[maxNode])
			maxNode = rightOf(here);
		// 현재 위치가 가장 크다면 힙의 조건은 모두 만족된다.
		if(maxNode == here) break;
		// 가장 큰 자손과 현재 위치의 값을 교환한다.
		swap(heap[here], heap[maxNode]);
		here = maxNode;
	}
	return ret;
}

int main()
{
	for(int size = 1; size <= 1000; ++size)
	{
		vector<int> rnd;
		IntMaxHeap h;
		for(int i = 0; i < size; ++i)
		{
			rnd.push_back(rand());
			h.insert(rnd[i]);
		}
		sort(rnd.begin(), rnd.end(), greater<int>());
		for(int i = 0; i < size; ++i)
		{
			assert(h.extractMax() == rnd[i]);
		}
	}
}
