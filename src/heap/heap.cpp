#include<cassert>
#include<cstdlib>
#include<queue>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

vector<int> heap;

// 정수를 담는 최대 힙 heap 에 새 원소 newValue 를 삽입한다
void push_heap(vector<int>& heap, int newValue) {
	// 힙의 맨 끝에 newValue 를 삽입한다
	heap.push_back(newValue);
	// 현재 newValue 의 위치
	int idx = heap.size() - 1;
	// 루트에 도달하거나 newValue 이상의 원소를 가진 조상을 만날 때까지
	while(idx > 0 && heap[(idx-1)/2] < heap[idx]) {
		swap(heap[idx], heap[(idx-1)/2]);
		idx = (idx-1) / 2;
	}
}

// 정수를 담는 최대 힙 heap 에서 heap[0] 을 제거한다
void pop_heap(vector<int>& heap) {
	// 힙의 맨 끝에서 값을 가져와 루트에 덮어씌운다
	heap[0] = heap.back();
	heap.pop_back();
	int here = 0;
	while(true) {
		int left = here * 2 + 1, right = here * 2 + 2;
		// 리프에 도달한 경우
		if(left >= heap.size()) break;
		// heap[here] 가 내려갈 위치를 찾는다
		int next = here;
		if(heap[next] < heap[left]) next = left;
		if(right < heap.size() && heap[next] < heap[right]) next = right;
		if(next == here) break;
		swap(heap[here], heap[next]);
		here = next;
	}
}

int main() {
	priority_queue<int> a;
	vector<int> b;
	for(int i = 0; i < 1000000; i++) {
		if(i % 10 > 8) {
			for(int i = 0; i < 6; i++) {
				int aa = a.top(); a.pop();
				int bb = b[0]; pop_heap(b);
				assert(aa == bb);
			}
		}
		else {
			int elem = rand() % 100000;
			a.push(elem);
			push_heap(b, elem);
		}
	}
	printf("all good.\n");
}

