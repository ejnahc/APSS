#include<cstdio>
#include<cassert>
#include<cstring>
#include<map>
#include<set>
#include<time.h>
#include<algorithm>
#include<stack>
#include<queue>
#include<utility>
#include<cmath>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 단일 변수 다항식 p의 계수가 주어질 때 미분한 결과 p' 의 계수를 반환한다
vector<double> differentiate(const vector<double>& poly) {
	// n차 방정식이다~
	int n = poly.size() - 1;
	vector<double> q(n);
	for(int i = 1; i <= n; ++i) {
		// poly[i]*x^i 를 미분하면 i*poly[i]*x^(i-1) 이 된다
		q[i-1] = i * poly[i];
	}
	return q;
}

// 1차 혹은 2차 방정식을 푼다
vector<double> solveNaive(const vector<double>& poly) {
	int n = poly.size() - 1;
	if(n == 1) {
		double a = poly[1], b = poly[0];
		// ax + b = 0
		if(fabs(a) < 1e-8) return vector<double>();
		return vector<double>(1, -b / a);
	}
	double a = poly[2], b = poly[1], c = poly[0];
	double d = b*b - 4*a*c;
	vector<double> ret;
	if(d >= 0) {
		double sqrtd = sqrt(d);
		ret.push_back((-b - sqrtd) / (2*a));
		if(sqrtd > 1e-8)
			ret.push_back((-b + sqrtd) / (2*a));
	}
	return ret;
}

// 다항식 f(x) 의 계수 poly가 주어질 때, f(x0) 를 반환한다
double evaluate(const vector<double>& poly, double x0) {
	double ret = poly.back();
	for(int i = int(poly.size())-2; i >= 0; --i) 
		ret = ret * x0 + poly[i];
	return ret;
}

// 방정식의 해의 절대값은 L이하여야 한다
const double L = 25;

vector<double> solve(const vector<double>& poly) {
	int n = poly.size() - 1;
	// 기저 사례: 2차 이하의 방정식들은 풀 수 있다
	if(n <= 2) return solveNaive(poly);

	// 방정식을 미분해서 n-1차 방정식을 얻는다
	vector<double> derivative = differentiate(poly);
	vector<double> sols = solve(derivative);
	// 이 극점들 사이를 하나하나 검사하며 근이 있나 확인한다.
	sols.insert(sols.begin(), -L-1);
	sols.insert(sols.end(), L+1);
	vector<double> ret;
	for(int i = 0; i+1 < sols.size(); ++i) {
		double x1 = sols[i], x2 = sols[i+1];
		double y1 = evaluate(poly, x1), y2 = evaluate(poly, x2);
		// f(x1) 과 f(x2) 의 부호가 같은 경우 답은 없다
		if(y1*y2 > 0) continue;
		// 불변 조건: f(x1) <= 0 < f(x2)
		if(y1 > y2) { swap(y1, y2); swap(x1, x2); }
		// 이분법을 사용하자
		for(int iter = 0; iter < 100; ++iter) {
			double mx = (x1 + x2) / 2;
			double my = evaluate(poly, mx);
			if(y1*my > 0) {
				y1 = my;
				x1 = mx;
			}
			else {
				y2 = my;
				x2 = mx;
			}
		}
		ret.push_back((x1 + x2) / 2);
	}
	sort(ret.begin(), ret.end());
	return ret;
}

int main() {
	int n, cc = 0;
	while(cin >> n) {
		if(n == 0) break;
		vector<double> coef(n+1);
		for(int i = 0; i <= n; ++i) 
			cin >> coef[n-i];
		vector<double> sols = solve(coef);
		printf("Equation %d:", ++cc);
		for(int i = 0; i < sols.size(); ++i)
			printf(" %.4lf", sols[i]);
		printf("\n");

	}
	/*
	   int cases;
	   cin >> cases;
	   for(int cc = 0; cc < cases; ++cc) {
	   int n;
	   cin >> n;
	   vector<double> coef(n+1);
	   for(int i = 0; i < n+1; ++i) 
	   cin >> coef[i];
	   vector<double> sols = solve(coef);
	   for(int i = 0; i < sols.size(); ++i)
	   printf("%s%.12lf", (i ? " " : ""), sols[i]);
	   printf("\n");
	   }
	   */
}

