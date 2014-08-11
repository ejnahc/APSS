#include<cstdio>
#include<cassert>
#include<cmath>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 종료하지 않는다
void infiniteBisection() {
	double lo = 123456123456.1234588623046875;
	double hi = 123456123456.1234741210937500;

	while(fabs(hi - lo) > 2e-7) {
		hi = (lo + hi) / 2.0;
	}

	printf("finished!\n");
}

double f(double x) {
	return cos(x) / (x+1);
}

double bisection(double lo, double hi) {
	double flo = f(lo), fhi = f(hi);

	// 예외 처리: lo 와 hi 중 답이 있는 경우
	if(flo == 0) return lo;
	if(fhi == 0) return hi;

	// 불변 조건: f(lo) < 0 < f(hi)

	if(flo > 0) {
		swap(lo, hi);
		swap(flo, fhi);
	}

	// 불변 조건을 확인한다
	assert(flo < 0 && 0 < fhi);

	//while(/* 종료 조건*/) {
	for(int i = 0; i < 100; i++) {
		double mid = (lo + hi) / 2;
		double fmid = f(mid);
		// f(mid) == 0 이면 mid 를 반환한다
		if(fmid == 0) return mid;

		if(fmid < 0)
			lo = mid;
		else
			hi = mid;
	}

	// 가운데 값을 반환한다
	return (lo + hi) / 2;
}

int main() {
	const double PI = 2.0 * acos(0);
	printf("%.10lf\n", bisection(PI*0.2, PI*1.2));
	infiniteBisection();
}

