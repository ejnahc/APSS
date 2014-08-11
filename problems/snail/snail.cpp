#include<cstring>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
int n, m;
const int MAX_N = 100;
int cache[101][101];

// days 일 동안 climbed 미터를 기어올라 왔다고 할 때,
// m 일 전까지 n미터를 기어올라갈 수 있는 경우의 수
int climb(int days, int climbed) {
	// 기저 사례: m일이 모두 지난 경우
	if(days == m) return climbed >= n ? 1 : 0;
	// 메모이제이션
	int& ret = cache[days][climbed];
	if(ret != -1) return ret;
	return ret = climb(days+1, climbed+1) + climb(days+1, climbed+2);
}

double cache2[MAX_N][MAX_N+1];
// days 일 동안 climbed 미터를 기어올라 왔다고 할 때,
// m 일 전까지 n미터를 기어올라갈 수 있을 확률
double climb2(int days, int climbed) {
	// 기저 사례: m일이 모두 지난 경우
	if(days == m) return climbed >= n ? 1 : 0;
	// 메모이제이션
	double& ret = cache2[days][climbed];
	if(ret >= 0) return ret;
	return ret = 0.5 * climb2(days+1, climbed+1) + 0.5 * climb2(days+1, climbed+2);
}

int main() {
	n = 9;
	m = 5;
	for(int i = 0; i < MAX_N; i++) {
		for(int j = 0; j < MAX_N*2+1; j++) {
			cache2[i][j] = -1;
		}
	}
	cout << climb2(0, 0) << endl;
}

