#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int n, k;
int l[5000], m[5000], g[5000];


// 결정 문제: dist 지점까지 가면서 k 개 이상의 표지판을 만날 수 있는가?
bool decision(int dist) {
	int ret = 0;
	for(int i = 0; i < n; i++)
		// i 번째 도시 표지판을 하나 이상 보게 되는가?
		if(dist >= l[i] - m[i])
			ret += (min(dist, l[i]) - (l[i] - m[i])) / g[i] + 1;
	return ret >= k;
}

// k번째 표지판을 만나는 지점의 위치를 계산한다
int optimize() {
	// 반복문 불변 조건: !decision(lo) && decision(hi)
	int lo = -1, hi = 8030001;
	while(lo+1 < hi) {
		int mid = (lo + hi) / 2;
		if(decision(mid))
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	cin >> n >> k;
    	for(int i = 0; i < n; i++)
    		cin >> l[i] >> m[i] >> g[i];
    	cout << optimize() << endl;
    }
}

