#include<cassert>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int MAX = 1000000100;

// length[i] = X 나 Y 를 i번 치환한 후의 길이
int length[51];
void precalc() {
	length[0] = 1;
	for(int i = 1; i <= 50; ++i) length[i] = min(MAX, length[i-1] * 2 + 2);
}

const string EXPAND_X = "X+YF";
const string EXPAND_Y = "FX-Y";

// dragonCurve 를 generations 진화시킨 결과에서 skip 번째 문자를 반환한다.
char expand(const string& dragonCurve, int generations, int skip) {
	// 기저 사례
	if(generations == 0) {
		assert(skip < dragonCurve.size());
		return dragonCurve[skip];
	}
	for(int i = 0; i < dragonCurve.size(); ++i)
		// 문자열이 확장되는 경우
		if(dragonCurve[i] == 'X' || dragonCurve[i] == 'Y') {
			if(skip >= length[generations])
				skip -= length[generations];
			else if(dragonCurve[i] == 'X')
				return expand(EXPAND_X, generations-1, skip);
			else
				return expand(EXPAND_Y, generations-1, skip);
		}
		// 확장되진 않지만 건너뛰어야 할 경우
		else if(skip > 0)
			--skip;
	    // 답을 찾은 경우
		else
			return dragonCurve[i];
	return '#';
}

// 초기 문자열 seed 를 generations 세대 진화한 결과를 출력.
void curve(const string& seed, int generations) {
	// 기저 사례
	if(generations == 0) {
		cout << seed;
		return;
	}
	for(int i = 0; i < seed.size(); ++i) {
		if(seed[i] == 'X')
			curve("X+YF", generations-1);
		else if(seed[i] == 'Y')
			curve("FX-Y", generations-1);
		else
			cout << seed[i];
	}
}

int main() {
	for(int i = 0; i < 10; ++i) {
		cout << i << ": ";
		curve("FX", i);
		cout << endl;
	}

    precalc();
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	int n, p, l;
    	cin >> n >> p >> l;
    	--p;
    	for(int i = 0; i < l; ++i)
    		printf("%c", expand("FX", n, p+i));
    	printf("\n");
    }
}

