#include<iostream>
#include<cstring>
#include<algorithm>
#include<sstream>
#include<string>
#include<vector>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<cassert>
#include<numeric>
#include<set>
#include<map>
#include<queue>
#include<list>
#include<deque>
using namespace std;

// 길이가 N 인 실수 벡터 A 가 주어질 때, 각 위치에서의 M-이동평균 값을 구한다
vector<double> movingAverage1(const vector<double>& A, int M) {
    vector<double> ret;
    int N = A.size();
    for(int i = M-1; i < N; ++i) {
        // A[i] 까지의 이동평균 값을 구하자.
        double partialSum = 0;
        for(int j = 0; j < M; ++j)
            partialSum += A[i-j];
        ret.push_back(partialSum / M);
    }
    return ret;
}

// 길이가 N 인 실수 벡터 A 가 주어질 때, 각 위치에서의 M-이동평균 값을 구한다
vector<double> movingAverage2(const vector<double>& A, int M) {
    vector<double> ret;
    int N = A.size();
    double partialSum = 0;
    for(int i = 0; i < M-1; ++i)
        partialSum += A[i];
    for(int i = M-1; i < N; ++i) {
        partialSum += A[i];
        ret.push_back(partialSum / M);
        partialSum -= A[i-M+1];
    }
    return ret;
}
bool equal(const vector<double>& a, const vector<double>& b) {
	if(a.size() != b.size()) return false;
	for(int i = 0; i < a.size(); i++) 
		if(a[i] != b[i]) return false;
	return true;
}
int main()
{
	vector<double> A, B;
	{
		istringstream inp("1 2 3 2 1 0 1 2 3");
		double x;
		while(inp >> x) A.push_back(x);
	}
	{
		istringstream inp("1.5 2.5 2.5 1.5 0.5 0.5 1.5 2.5");
		double x;
		while(inp >> x) B.push_back(x);
	}

	vector<double> mv1 = movingAverage1(A, 2);
	vector<double> mv2 = movingAverage2(A, 2);
	assert(equal(B, mv1));
	assert(equal(B, mv2));
	printf("all good.\n");

}

