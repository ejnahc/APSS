#include<cmath>
#include<cstring>
#include<cstdio>
#include<cassert>
#include<iostream>
#include<string>
#include<vector>
using namespace std;


struct SquareMatrix {
	int N;
	vector<vector<double> > v;
	SquareMatrix(int _N);
	~SquareMatrix();
	static SquareMatrix identity(int N);
	SquareMatrix operator * (const SquareMatrix& rhs) const;
	SquareMatrix pow(int n) const;
	double* operator [] (int idx);
};

SquareMatrix::SquareMatrix(int _N) {
	N = _N;
	v.resize(N, vector<double>(N, 0));
}

SquareMatrix::~SquareMatrix() {
}

SquareMatrix SquareMatrix::identity(int N) {
	SquareMatrix ret = SquareMatrix(N);
	for(int i = 0; i < N; i++) ret.v[i][i] = 1;
	return ret;
}

SquareMatrix SquareMatrix::operator * (const SquareMatrix& rhs) const {
	assert(N == rhs.N);

	SquareMatrix ret = SquareMatrix(N);
	for(int k = 0; k < N; k++)
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				ret.v[i][j] += v[i][k] * rhs.v[k][j];
	return ret;
}

SquareMatrix SquareMatrix::pow(int n) const {
	if(n == 0) return identity(N);
	if(n % 2 > 0) return (*this) * pow(n-1);
	SquareMatrix half = pow(n/2);
	return half * half;
}

double* SquareMatrix::operator [] (int idx) {
	return &v[idx][0];
}

SquareMatrix getTransitionMatrix(const vector<int>& pointed, int t) {
	int n = pointed.size();
	SquareMatrix ret(n);
	// 태윤이는 언제나 정확하게 가리킨다
	ret.v[pointed[0]-1][0] = 1;
	// 다른 사람들은 다 확률이 다르다
	for(int pointer = 1; pointer < n; pointer++)
		for(int delta = -t; delta <= t; ++delta)
			ret[(pointed[pointer] - 1 + delta + n) % n][pointer] = 1.0 / (2 * t + 1);
	return ret;
}
int main() {
    int cases;
    scanf("%d", &cases);
    for(int cc = 0; cc < cases; ++cc) {
    	int n, x, m, t;
    	scanf("%d %d %d %d", &n, &x, &m, &t);
    	vector<int> pointed(n);
    	for(int pointer = 0; pointer < n; pointer++) {
    		scanf("%d", &pointed[pointer]);
		}
    	SquareMatrix tr = getTransitionMatrix(pointed, t).pow(x);
    	for(int i = 0; i < m; i++) {
    		int interested;
    		scanf("%d", &interested);
    		--interested;
    		printf("%.10lf ", tr[interested][0]);
    	}
    	printf("\n");
    }
}

