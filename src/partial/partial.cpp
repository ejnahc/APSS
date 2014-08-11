#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cassert>
#include<numeric>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int n, a[1000], b[1000];

// 주어진 벡터 a 의 부분합을 계산한다.
vector<int> partialSum(const vector<int>& a) {
	vector<int> ret(a.size());
	ret[0] = a[0];
	for(int i = 1; i < a.size(); i++)
		ret[i] = ret[i-1] + a[i];
	return ret;
}

// 어떤 벡터의 부분합 psum[] 이 주어질 때, 원래 벡터의 a 부터 b 까지의 합을 구한다.
int rangeSum(const vector<int>& psum, int a, int b) {
	return psum[b] - (a ? psum[a-1] : 0);
}

// A[] 의 제곱의 부분 합 벡터 sqpsum, A[] 의 부분 합 벡터 psum 이 주어질 때
// A[a..b] 의 분산을 반환한다
double variance(const vector<int>& sqpsum, const vector<int>& psum, int a, int b) {
	// 우선 해당 구간의 평균을 계산한다
	double mean = rangeSum(psum, a, b) / double(b - a + 1);

	double ret = rangeSum(sqpsum, a, b) - 2 * mean * rangeSum(psum, a, b) + (b - a + 1) * mean * mean;
	return ret / (b - a + 1);
}

// 정수 배열 A 가 주어질 때, 합이 0 에 가장 가까운 구간의 구간합의 절대값을 계산한다.
int smallestInterval(const vector<int>& A) {
	// A 의 길이가 1 일때는 예외 처리한다.
	if(A.size() == 1) return abs(A[0]);

	// 부분합을 구하고 정렬한다.
	vector<int> psum = partialSum(A);
	sort(psum.begin(), psum.end());

	// 결과값은 인접한 부분합 중 최소 차이가 된다.
	int ret = psum[1] - psum[0];
	for(int i = 2; i < psum.size(); ++i)
		ret = min(ret, psum[i] - psum[i-1]);
	return ret;
}

double sqr(double x) { return x*x; }

int grid[100][100], gridPartialSum[100][100];

// 어떤 2차원 배열 A[][] 의 부분합 psum[][] 이 주어질 때,
// A[y1,x1] 과 A[y2,x2] 을 양 끝으로 갖는 부분 배열의 합을 반환한다.
int gridSum(const vector<vector<int> >& psum, int y1, int x1, int y2, int x2) {
	int ret = psum[y2][x2];
	if(y1 > 0) ret -= psum[y1-1][x2];
	if(x1 > 0) ret -= psum[y2][x1-1];
	if(y1 > 0 && x1 > 0) ret += psum[y1-1][x1-1];
	return ret;
}

int main() {
	cin >> n;
	vector<int> A(n), A2(n);
	for(int i = 0; i < n; i++) {
		cin >> A[i];
		A2[i] = A[i] * A[i];
	}
	vector<int> psum(n), sqpsum(n);
	partial_sum(A.begin(), A.end(), psum.begin());
	partial_sum(A2.begin(), A2.end(), sqpsum.begin());

	for(int i = 0; i < n; i++)
		for(int j = i; j < n; j++) {
			double sum = 0;
			for(int k = i; k < j+1; k++)
				sum += A[k];
			double mean = sum / (j - i + 1);
			double var = 0;
			for(int k = i; k < j+1; k++)
				var += sqr(mean - A[k]);
			var /= (j - i + 1);
			printf("var %g\n", var);
			printf("variance %g\n", variance(sqpsum, psum, i, j));
			assert(fabs(var - variance(sqpsum, psum, i, j)) < 1e-8);
		}

}

