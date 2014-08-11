#include<set>
#include<cassert>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

// 입력: 정렬되고, 중복이 없는 배열 A
// 반환: q == A[i] 인 i 를 반환한다.  
//       그런 i 가 존재하지 않는 경우에는 -1 을 반환한다.
int linearSearch(const vector<int>& A, int q)
{
	for(int i = 0; i < A.size(); ++i)
	{
		if(A[i] > q) return -1;
		if(A[i] == q) return i;
	}
	return -1;
}

// 입력: 정렬되고, 중복이 없는 배열 A
// 반환: q == A[i] 인 i 를 반환한다.  
//       그런 i 가 존재하지 않는 경우에는 -1 을 반환한다.
int binarySearch(const vector<int>& A, int q)
{
	// 루프 불변 조건: A[lo] < q < A[hi]
	// A[-1] 에는 음의 무한대, A[n] 에는 양의 무한대 값이 들어 있다고 가정한다.
	int lo = -1, hi = A.size();
	while(lo+1 < hi)
	{
		int mid = (lo + hi) / 2;
		if(A[mid] < q)
			lo = mid;
		else if(A[mid] == q)
			return mid;
		else 
			hi = mid;
	}
	return -1;
}

void testCorrectness()
{
	for(int test = 0; test < 100000; ++test)
	{
		int n = rand() % 1000 + 1;
		fprintf(stderr, "%6d/100000 (n=%4d) ..\r", test, n);
		vector<int> A(n);
		for(int i = 0; i < n; ++i)
			A[i] = rand();
		sort(A.begin(), A.end());
		A.erase( unique(A.begin(), A.end()), A.end() );
		// test for elements in the array
		for(int test2 = 0; test2 < 100; ++test2)
		{
			int randomIndex = rand() % n;
			int byLinear = linearSearch(A, A[randomIndex]);
			int byBinary = binarySearch(A, A[randomIndex]);
			assert(randomIndex == byLinear);
			assert(randomIndex == byBinary);
		}
		// test for elements *not* in the array
		for(int test2 = 0; test2 < 100; ++test2)
		{
			int randomIndex = rand() % n;
			if(randomIndex == 0 || A[randomIndex-1] != A[randomIndex]-1)
			{
				int byLinear = linearSearch(A, A[randomIndex]-1);
				int byBinary = binarySearch(A, A[randomIndex]-1);
				assert(byLinear == -1);
				assert(byBinary == -1);
			}
			if(randomIndex == n-1 || A[randomIndex+1] != A[randomIndex]+1)
			{
				int byLinear = linearSearch(A, A[randomIndex]+1);
				int byBinary = binarySearch(A, A[randomIndex]+1);
				assert(byLinear == -1);
				assert(byBinary == -1);
			}
		}
	}
	printf("All tests passed.\n");
}

template<typename FUNC>
double measureTime(const vector<int>& A, const vector<int>& index, FUNC f)
{
	clock_t begin = clock();
	for(int rep = 0; rep < 5000; ++rep)
	{
		for(int i = 0; i < index.size(); ++i)
			f(A, A[index[i]]);
	}
	clock_t end = clock();
	return (end - begin) * 1.0 / CLOCKS_PER_SEC * 1000.0;
}

void testTime()
{
	int n[] = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000, -1 };
	for(int i = 0; n[i] != -1; ++i)
	{
		set<int> s;
		while(s.size() < n[i])
			s.insert(rand());
		vector<int> A(s.begin(), s.end());
		vector<int> index(1000);
		for(int j = 0; j < 1000; ++j)
			index[i] = rand() % n[i];
		double linearTime = measureTime(A, index, linearSearch);
		double binaryTime = measureTime(A, index, binarySearch);
		printf("%d %.10lf %.10lf\n", n[i], linearTime, binaryTime);
	}
}

int main()
{
	testTime();
}
