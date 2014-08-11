#include<cstring>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
int n, board[100][100];
int cache[100][100];

bool jump(int y, int x) {
	// 기저 사례: 게임판 밖을 벗어난 경우
	if(y >= n || x >= n) return false;
	// 기저 사례: 마지막 칸에 도착한 경우
	if(y == n-1 && x == n-1) return true;
	int jumpSize = board[y][x];
	return jump(y + jumpSize, x) || jump(y, x + jumpSize);
}

int jump2(int y, int x) {
	if(y >= n || x >= n) return 0;
	if(y == n-1 && x == n-1) return 1;
	int& ret = cache[y][x];
	if(ret != -1) return ret;
	int jumpSize = board[y][x];
	return ret = (jump2(y + jumpSize, x) || jump2(y, x + jumpSize));
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	cin >> n;
    	for(int i = 0; i < n; i++)
    		for(int j = 0; j < n; j++)
    			cin >> board[i][j];
    	memset(cache, -1, sizeof(cache));
    	// cout << (jump(0, 0) ? "YES" : "NO") << endl;
    	cout << (jump2(0, 0) ? "YES" : "NO") << endl;
    }
}

