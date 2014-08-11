#include<cassert>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
using namespace std;

const double PI = 2.0 * acos(0.0);

// theta 만큼 기울였을 때 카드를 덮는 최소 사각형의 높이를 반환한다
double cardWidth(double cardW, double cardH, double theta) {
	return cos(theta) * cardW + cos(PI/2 - theta) * cardH;
}

// theta 만큼 기울였을 때 카드를 덮는 최소 사각형의 너비를 반환한다
double cardHeight(double cardW, double cardH, double theta) {
	return sin(theta) * cardW + cos(theta) * cardH;
}

// 봉투와 카드의 크기가 주어질 때, 카드를 최대 90도 기울여서 봉투에
// 들어갈 수 있나 확인한다
double fit(double envW, double envH, double cardW, double cardH) {
	// 기울일 이유가 없는 경우: 봉투의 긴 변이 카드의 긴 변보다 길면 그냥 집어넣는다
	if(max(cardW, cardH) <= max(envW, envH)) return min(cardW, cardH) <= min(envW, envH);

	// 반복문 불변 조건을 만족시키려면 카드 한 변의 길이는 봉투의 너비 이상이고,
	// 다른 변의 길이는 봉투의 너비 미만이어야 한다. 이 제약에서 벗어나는 경우를 확인하자.
	// 위 조건을 통과했기 때문에, 이미 한 변은 봉투의 너비보다 길다.
	// 봉투의 너비가 카드의 두 변보다 모두 짧은 경우: 기울여도 소용없다.
	if(envW < min(cardW, cardH)) return false;

	double lo = 0, hi = PI / 2.0;
	// 불변 조건을 강제한다
	if(cardW <= envW) swap(lo, hi);

	// 반복문 불변 조건: cardWidth(hi) <= envW < cardWidth(lo)
	for(int iter = 0; iter < 100; ++iter) {
		double mid = (lo + hi) / 2;
		if(cardWidth(cardW, cardH, mid) <= envW)
			hi = mid;
		else
			lo = mid;
	}
	return cardHeight(cardW, cardH, hi) <= envH;
}

bool solve(double envW, double envH, double cardW, double cardH) {
	// (a), (b) 의 두 경우를 각각 시도한다
	return fit(envW, envH, cardW, cardH) || fit(envW, envH, cardH, cardW);
}

int main() {
	int cases;
	cin >> cases;
	for(int cc = 0; cc < cases; ++cc) {
		double envW, envH, cardW, cardH;
		cin >> envW >> envH >> cardW >> cardH;
		bool yes = solve(envW, envH, cardW, cardH);
		cout << (yes ? "YES" : "NO") << endl;
		if(yes) assert(solve(envW-1e-7, envH-1e-7, cardW, cardH));
		if(!yes) assert(!solve(envW+1e-7, envH+1e-7, cardW, cardH));
	}
}

