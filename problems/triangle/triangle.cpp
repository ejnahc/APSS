#include<iostream>
#include<string>
#include<vector>
#include<cstring>
using namespace std;

const int MAX_NUMBER = 10;
int n, triangle[100][100];
int cache[100][100][MAX_NUMBER*100+1];
int cache2[100][100];

// (0,0) 에서 (y,x) 까지 내려오는 부분 경로의 합이 sum 일 때
// 이 경로를 맨 아래줄까지 이어서 얻을 수 있는 최대 경로의 합을
// 반환한다
int path(int y, int x, int sum) {
	// 기저 사례: 맨 아래 줄까지 도달했을 경우
	if(y == n-1) return sum + triangle[y][x];

	// 메모이제이션
	int& ret = cache[y][x][sum];
	if(ret != -1) return ret;

	sum += triangle[y][x];
	return ret = max(path(y+1, x+1, sum), path(y+1, x, sum));
}

// (y,x) 위치부터 맨 아래줄까지 내려가면서 얻을 수 있는 최대 경로를 반환한다
int path2(int y, int x) {
	// 기저 사례
	if(y == n-1) return triangle[y][x];

	int& ret = cache2[y][x];
	if(ret != -1) return ret;
	return ret = max(path2(y+1, x), path2(y+1, x+1)) + triangle[y][x];
}

int C[100][100];
int iterative() {
	// 기저 사례를 계산한다
	for(int x = 0; x < n; ++x)
		C[n-1][x] = triangle[n-1][x];
	// 다른 부분을 계산한다
	for(int y = n-2; y >= 0; --y)
		for(int x = 0; x < y+1; ++x)
			C[y][x] = max(C[y+1][x], C[y+1][x+1]) + triangle[y][x];
	return C[0][0];
}

int C2[2][5000];
int iterative2() {
	// 기저 사례를 계산한다
	for(int x = 0; x < n; ++x)
		C2[(n-1)%2][x] = triangle[n-1][x];
	// 다른 부분을 계산한다
	for(int y = n-2; y >= 0; --y)
		for(int x = 0; x < y+1; ++x)
			C2[y%2][x] = max(C2[(y+1)%2][x], C2[(y+1)%2][x+1]) + triangle[y][x];
	return C2[0][0];

}

int countCache[100][100];
// (y, x)에서 시작해서 맨 아래줄까지 내려가는 경로 중 최대 경로의
// 개수를 반환한다.
int count(int y, int x) {
  // 기저 사례: 맨 아래줄에 도달한 경우
   if(y == n-1) return 1;
  // 메모이제이션
   int& ret = countCache[y][x];
   if(ret != -1) return ret;
   ret = 0;
   if(path2(y+1, x+1) >= path2(y+1, x)) ret += count(y+1, x+1);
   if(path2(y+1, x+1) <= path2(y+1, x)) ret += count(y+1, x);
   return ret;
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	memset(cache, -1, sizeof(cache));
    	memset(cache2, -1, sizeof(cache2));
      memset(countCache, -1, sizeof(countCache));
    	cin >> n;
    	for(int i = 0; i < n; i++) {
    		for(int j = 0; j < i+1; j++) {
    			cin >> triangle[i][j];
    		}
    	}
    	// cout << path2(0, 0) << endl;
      cout << count(0, 0) << endl;
      
    	// cout << iterative() << endl;
    	// cout << iterative2() << endl;

    }
}

