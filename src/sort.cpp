#include<algorithm>
#include<cassert>
#include<vector>
using namespace std;

void selectionSort(vector<int>& A)
{
	for(int i = 0; i < A.size(); ++i)
	{
		int minIndex = i;
		for(int j = i+1; j < A.size(); ++j)
			if(A[minIndex] > A[j])
				minIndex = j;
		swap(A[i], A[minIndex]);
	}
}

void insertionSort(vector<int>& A)
{
	for(int i = 0; i < A.size(); ++i)
	{
		int val = A[i], j = i-1;
		while(j >= 0 && A[j] > val)
		{
			A[j+1] = A[j];
			--j;
		}
		A[j+1] = val;
	}
}

template<typename T>
void testCorrectness(T func)
{
	for(int tests = 1; tests <= 1000; ++tests)
	{
		int n = (tests + 1) / 10;
		vector<int> ret(n);
		for(int i = 0; i < n; ++i)
			ret[i] = rand() % 100;
		vector<int> A = ret, B = ret;
		sort(A.begin(), A.end());
		func(B);
		assert(A == B);
	}
}

int main()
{
	testCorrectness(selectionSort);
	testCorrectness(insertionSort);
}
