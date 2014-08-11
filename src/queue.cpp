#include<cassert>
#include<vector>
using namespace std;

class CircularIntQueue {
	private:
		vector<int> queue;
		int head, tail;
	public:
		CircularIntQueue() {
			queue.resize(20);    // 일단 크기 고정
			head = tail = 0; // enqueue 했을 때 head == tail 이 되도록
		}
		int front() const {
			return queue[head];
		}
		void dequeue() {
			assert(head != tail); // 큐가 비어 있지 않아야 함
			head = (head + 1) % queue.size(); // head 를 1칸 증가
		}
		void enqueue(int newValue) {
			if((tail + 1) % queue.size() == head) {
				// 배열 공간이 꽉 차 있으므로, 동적 배열의 크기를 늘려야 함
				assert(false);
			}
			queue[tail] = newValue;
			tail = (tail + 1) % queue.size();
		}
};


int main()
{
	CircularIntQueue q;
	for(int iterate = 0; iterate < 100; ++iterate)
	{
		for(int i = 0; i < 19; ++i)
			q.enqueue(i+iterate);
		for(int i = 0; i < 19; ++i)
		{
			int val = q.front();
			q.dequeue();
			assert(val == i+iterate);
		}
	}
	
}
