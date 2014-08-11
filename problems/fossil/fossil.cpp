#include<cmath>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct point {
	double y, x;
};

// 입력에 주어진 볼록 다각형
vector<point> hull1, hull2;

// 위 껍질에 속하는 선분들과 아래 껍질에 속하는 선분들
vector<pair<point,point> > upper, lower;

// hull 이 반시계방향으로 주어지므로, 인접한 두 점에 대해 x 가
// 증가하는 방향이면 아래쪽 껍질, x가 감소하는 방향이면 위쪽 껍질이다.
void decompose(const vector<point>& hull) {
	int n = hull.size();
	for(int i = 0; i < n; i++) {
		if(hull[i].x < hull[(i+1)%n].x)
			lower.push_back(make_pair(hull[i], hull[(i+1)%n]));
		else if(hull[i].x > hull[(i+1)%n].x)
			upper.push_back(make_pair(hull[i], hull[(i+1)%n]));
	}
}

// hull 의 점 중 최소의 x 좌표를 반환한다
double minX(const vector<point>& hull) {
	double ret = 1e20;
	for(int i = 0; i < hull.size(); i++) ret = min(ret, hull[i].x);
	return ret;
}

// hull 의 점 중 최대의 x 좌표를 반환한다
double maxX(const vector<point>& hull) {
	double ret = -1e20;
	for(int i = 0; i < hull.size(); i++) ret = max(ret, hull[i].x);
	return ret;
}

// [a.x, b.x] 구간 안에 x 가 포함되나 확인한다.
bool between(const point& a, const point& b, double x) {
	return (a.x <= x && x <= b.x) || (b.x <= x && x <= a.x);
}

// (a,b) 선분과 주어진 위치의 수직선이 교차하는 위치를 반환한다.
double at(const point& a, const point& b, double x) {
	double dy = b.y - a.y, dx = b.x - a.x;
	// 선분 (a,b) 가 수직인 경우를 따로 처리한다
	if(fabs(dx) < 1e-9) return a.y;
	return a.y + dy * (x - a.x) / dx;
}

// 두 다각형의 교집합을 수직선으로 잘랐을 때 단면의 길이를 반환한다.
double vertical(double x) {
	double minUp = 1e20, maxLow = -1e20;
	// 위 껍질의 선분을 순회하며 최소 y 좌표를 찾는다
	for(int i = 0; i < upper.size(); ++i)
		if(between(upper[i].first, upper[i].second, x))
			minUp = min(minUp, at(upper[i].first, upper[i].second, x));
	// 아래 껍질의 선분을 순회하며 최대 x 좌표를 찾는다
	for(int i = 0; i < lower.size(); ++i)
		if(between(lower[i].first, lower[i].second, x))
			maxLow = max(maxLow, at(lower[i].first, lower[i].second, x));
	//printf("vertical(%.2lf) = %.2lf - %.2lf = %.2lf\n", x, minUp, maxLow, minUp - maxLow);
	return minUp - maxLow;
}

double solve() {

	// 수직선이 두 다각형을 모두 만나는 x 좌표의 범위를 구한다
	double lo = max(minX(hull1), minX(hull2));
	double hi = min(maxX(hull1), maxX(hull2));

	// 예외 처리: 두 다각형이 아예 겹치지 않는 경우
	if(hi < lo) return 0;

	// 삼분 검색
	for(int iter = 0; iter < 100; ++iter) {
		double aab = (lo*2 + hi) / 3.0;
		double abb = (lo + hi*2) / 3.0;
		if(vertical(aab) < vertical(abb))
			lo = aab;
		else
			hi = abb;
		printf("lo %g hi %g\n", lo, hi);
	}
	printf("hi %g\n", hi);
	return max(0.0, vertical(hi));
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	int n, m;
    	cin >> n >> m;
    	hull1.resize(n);
    	hull2.resize(m);
    	for(int i = 0; i < n; i++) cin >> hull1[i].x >> hull1[i].y;
    	for(int i = 0; i < m; i++) cin >> hull2[i].x >> hull2[i].y;
    	upper.clear();
    	lower.clear();
    	decompose(hull1);
    	decompose(hull2);
    	printf("%.10lf\n", max(0.0, solve()));
    }
}

