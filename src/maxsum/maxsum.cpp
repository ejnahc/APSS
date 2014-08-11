#include<cassert>
#include<limits>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int MIN = numeric_limits<int>::min();

// A[]의 연속된 부분 구간의 최대 합을 구한다. 시간 복잡도: O(n^3)
int inefficientMaxSum(const vector<int>& A) {
	int N = A.size(), ret = MIN;
	for(int i = 0; i < N; ++i) 
		for(int j = i; j < N; ++j) {
			// 구간 A[i..j] 의 합을 구한다
			int sum = 0;
			for(int k = i; k <= j; k++) 
				sum += A[k];
			ret = max(ret, sum);
		}
	return ret;
}

// A[]의 연속된 부분 구간의 최대 합을 구한다. 시간 복잡도: O(n^2)
int betterMaxSum(const vector<int>& A) {
	int N = A.size(), ret = MIN;
	for(int i = 0; i < N; ++i) {
		int sum = 0;
		for(int j = i; j < N; ++j) {
			// 구간 A[i..j] 의 합을 구한다
			sum += A[j];
			ret = max(ret, sum);
		}
	}
	return ret;
}

// A[lo..hi]의 연속된 부분 구간의 최대 합을 구한다. 시간 복잡도: O(nlgn)
int fastMaxSum(const vector<int>& A, int lo, int hi) {
	// 기저 사례: 구간의 길이가 1 일 경우
	if(lo == hi) return A[lo];
	// 배열을 A[lo..mid], A[mid+1..hi] 의 두 조각으로 나눈다.
	int mid = (lo + hi) / 2;
	// 두 부분에 모두 걸쳐 있는 최대 합 구간을 찾는다. 이 구간은 
	// A[i..mid] 와 A[mid+1..j] 형태를 갖는 구간의 합으로 이루어진다.
	// A[i..mid] 형태를 갖는 최대 구간을 찾는다.
	int left = MIN, right = MIN, sum = 0;
	for(int i = mid; i >= lo; --i) {
		sum += A[i];
		left = max(left, sum);
	}
	// A[mid+1..j] 형태를 갖는 최대 구간을 찾는다.
	sum = 0;
	for(int j = mid+1; j <= hi; ++j) {
		sum += A[j];
		right = max(right, sum);
	}
	// 최대 구간이 두 조각 중 하나에만 속해 있는 경우의 답을 재귀호출로 찾는다.
	int single = max(fastMaxSum(A, lo, mid), fastMaxSum(A, mid+1, hi));
	// 두 경우 중 최대값을 반환한다.
	return max(left + right, single);
}

// A[]의 연속된 부분 구간의 최대 합을 구한다. 시간 복잡도: O(n)
int fastestMaxSum(const vector<int>& A) {
	int N = A.size(), ret = MIN, psum = 0;
	for(int i = 0; i < N; ++i) {
		psum = max(psum, 0) + A[i];
		ret = max(psum, ret);
	}
	return ret;
}

int fastMaxSumAdapter(const vector<int>& A) {
	return fastMaxSum(A, 0, A.size()-1);
}

void check(const vector<int>& array) {
	int A = inefficientMaxSum(array);
	int B = betterMaxSum(array);
	int C = fastMaxSumAdapter(array);
	int D = fastestMaxSum(array);
	if(!(A == B && B == C && C == D)) {
		printf("array =");
		for(int i = 0; i < array.size(); i++)
			printf(" %d", array[i]);
		printf("\n");
		printf("A %d B %d C %d D %d\n", A, B, C, D);
		assert(false);
	}
}

struct RNG {
	unsigned seed;
	RNG(unsigned seed = 1983) : seed(seed) {}
	unsigned next() {
		unsigned ret = seed;
		seed = ((seed * 214013u) + 2531011u);
		return ret;
	}
};
struct Generator {
	int n;
	RNG rng;
	Generator(int n): n(n), rng(1983 + n) {
		rng.next();
	}
	vector<int> generate() {
		vector<int> ret(n);
		for(int i = 0; i < n; i++) {
			int nxt = rng.next();
			ret[i] = nxt % 100000 - 50000;
		}
		return ret;
	}
};

void test() {
	Generator gen(50);
	for(int i = 0; i < 100; i++) {
		const vector<int> A = gen.generate();
		check(A);
	}
}

#include <sys/time.h>

double getTime() {
	timeval tv; 
	gettimeofday(&tv, 0); 
	return tv.tv_sec + tv.tv_usec * 1e-6;
}

template<typename T>
double measure(T solver, int n, int repeat) {
	double sum = 0;
	Generator gen(n);
	for(int i = 0; i < repeat; i++) {
		double start = getTime();
		solver(gen.generate());
		sum += getTime() - start;
	}
	return sum / repeat;
}

template<typename T>
void run(const char* testName, T solver) {
	int canSolveWithin1Sec = 10;
	while(true) {
		double time = measure(solver, canSolveWithin1Sec, 1);
		printf("%s,%d,%.4lf\n", testName, canSolveWithin1Sec, time);
		if(time >= 1.0) break;
		canSolveWithin1Sec *= 2;
	}
}

int main() {
	test();
	printf("all good.\n");
	run("N^3", inefficientMaxSum);
	run("N^2", betterMaxSum);
	run("NlgN", fastMaxSumAdapter);
	run("N", fastestMaxSum);
}

