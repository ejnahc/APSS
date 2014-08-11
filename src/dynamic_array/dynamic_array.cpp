#include<set>
#include<cassert>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int M = 100;

class SimpleIntArray
{
	public:
		SimpleIntArray(int initialSize)
		{
			size = capacity = initialSize;
			array = new int[size];
		}
		int getSize() const
		{
			return size;
		}
		int get(int index) const
		{
			return array[index];
		}
		void set(int index, int value)
		{
			array[index] = value;
		}
		void append(int newValue) {
			// 배열 용량이 꽉 찼으면 재할당 받는다
			if(size == capacity) {
				// 용량을 M 만큼 늘린 새 배열을 할당받는다
				int newCapacity = capacity + M;
				int* newArray = new int[newCapacity];
				// 기존의 자료를 복사한다
				for(int i = 0; i < size; ++i)
					newArray[i] = array[i];
				// 기존 배열을 삭제하고, 새 배열로 바꿔치기한다
				if(array) delete [] array;
				array = newArray;
				capacity = newCapacity;

			}
			// 이제 맨 뒤에 새 원소를 추가한다
			array[size++] = newValue;
		}

		int getCapacity() const { return capacity; }

	private:
		int size, capacity;
		int* array;
};

int main()
{
	typedef SimpleIntArray Tested;

	Tested a(10);
	assert(a.getSize() == 10);
	for(int i = 0; i < 10; ++i)
	{
		a.set(i, i);
		assert(a.get(i) == i);
	}
	assert(a.getCapacity() >= a.getSize());
	for(int i = 0; i < 100; ++i)
	{
		a.append(i+101);
		assert(a.getSize() == 10 + i + 1);
		assert(a.get(10 + i) == i+101);
		assert(a.getCapacity() >= a.getSize());
	}
	/*
	a.resize(7);
	assert(a.getSize() == 7);
	for(int i = 0; i < 7; ++i)
		assert(a.get(i) == i);
		*/

}
