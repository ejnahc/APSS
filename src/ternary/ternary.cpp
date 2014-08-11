#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 우리가 최대값을 찾고 싶어하는 함수
double f(double x);

// [lo,hi] 구간에서 f(x) 가 최대값을 갖는 x 를 반환한다
double ternary(double lo, double hi) {
	for(int iter = 0; iter < 100; iter++) {
		double a = (2*lo + hi) / 3.0;
		double b = (lo + 2*hi) / 3.0;
		if(f(a) > f(b))
			hi = b;
		else
			lo = a;
	}
	return (lo+hi) / 2.0;
}

double f(double x) {
	return -x*x+4*x-7;
}

int main() {
	cout << ternary(-100,100) << endl;
}

