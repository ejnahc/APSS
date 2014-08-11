#include<cstdio>
#include<cassert>
#include<cstring>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int n;
int older[200], younger[200];
int cache[200][101];

int satisfy(int toy, int toOlder) {
	// 기저 사례: 모든 장난감을 다 나눠줬을 때
	if(toy == 2*n) { assert(toOlder == 0); return 0; }

	int& ret = cache[toy][toOlder];
	if(ret != -1) return ret;
	ret = 0;
	// 형에게 주는 경우
	if(toOlder > 0) ret = max(ret, satisfy(toy+1, toOlder-1) + older[toy]);
	// 동생에게 주는 경우
	if(toOlder != 2*n-toy) ret = max(ret, satisfy(toy+1, toOlder) + younger[toy]);
	return ret;
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	cin >> n;
    	for(int i = 0; i < 2*n; i++) cin >> older[i];
    	for(int i = 0; i < 2*n; i++) cin >> younger[i];
    	memset(cache, -1, sizeof(cache));
    	cout << satisfy(0, n) << endl;
    }
}

