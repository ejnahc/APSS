#include<cstring>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int MOD = 1000000007;

int cache[101];

void precalc() {
	cache[0] = cache[1] = 1;
	for(int i = 2; i <= 100; ++i)
		cache[i] = (cache[i-1] + cache[i-2]) % MOD;
}

int tiling(int n) { return cache[n]; }

// 2*width 크기의 사각형을 채우는 비대칭 방법의 수를 반환한다
int asymmetric(int width) {
	if(width % 2 == 1)
		return (tiling(width) - tiling(width/2) + MOD) % MOD;
	int ret = tiling(width);
	ret = (ret - tiling(width/2) + MOD) % MOD;
	ret = (ret - tiling(width/2-1) + MOD) % MOD;
	return ret;
}

int cache2[101];
// 2*width 크기의 사각형을 채우는 비대칭 방법의 수를 반환한다
int asymmetric2(int width) {
	// 기저 사례: 너비가 2 이하인 경우
	if(width <= 2) return 0;
	// 메모이제이션
	int& ret = cache2[width];
	if(ret != -1) return ret;
	ret = asymmetric2(width-2) % MOD; // (a)
	if(width >= 4) ret = (ret + asymmetric2(width-4)) % MOD; // (b)
	ret = (ret + tiling(width-3)) % MOD; // (c)
	ret = (ret + tiling(width-3)) % MOD; // (d)
	return ret;
}

int brute(vector<int>& part, int left) {
	if(left == 0) {
		bool sym = true;
		for(int i = 0; i < part.size(); i++)
			if(part[i] != part[part.size()-1-i])
				sym = false;
		if(sym) return 0;
		return 1;
	}
	int ret = 0;
	for(int p = 1; p <= 2; ++p)
		if(left >= p) {
			part.push_back(p);
			ret += brute(part, left-p);
			part.pop_back();
		}
	return ret;
}

int main() {
    precalc();
    memset(cache2, -1, sizeof(cache2));
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	int n;
    	cin >> n;
    	vector<int> p;
    	cout << n << ' ';
    	cout << asymmetric(n) << " " << asymmetric2(n);
    	if(n <= 20) cout << " " << brute(p, n);
    	cout << endl;
    }
}

