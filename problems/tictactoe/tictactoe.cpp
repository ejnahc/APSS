#include<map>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// turn 이 한 줄을 만들었는지를 반환한다
bool isFinished(const vector<string>& board, char turn) {
	return false;
}


// 틱택토 게임판이 주어질 때 [0,19682] 범위의 정수로 변환한다
int bijection(const vector<string>& board) {
	int ret = 0;
	for(int y = 0; y < 3; ++y)
		for(int x = 0; x < 3; x++) {
			ret = ret * 3;
			if(board[y][x] == 'o') ++ret;
			else if(board[y][x] == 'x') ret += 2;
		}
	return ret;
}

// cache[] 는 -2 로 초기화한다
int cache[19683];

// 내가 이길 수 있으면 1 을, 비길 수 있으면 0 을, 지면 -1 을 리턴한다
int canWin(vector<string>& board, char turn) {
	// 기저 사례: 마지막에 상대가 둬서 한줄이 만들어진 경우
	if(isFinished(board, 'o'+'x'-turn)) return -1;
	int& ret = cache[bijection(board)];
	if(ret != -2) return ret;
	// 각 반환값 중 상대가 이기는 결과 (1) 보다 비기는 결과 (0),
	// 비기는 결과보다 상대가 지는 결과 (-1)를 원한다:
	// 모든 반환값의 min 을 취하자
	int minValue = 2;
    for(int y = 0; y < 3; ++y)
    	for(int x = 0; x < 3; ++x) {
    		if(board[y][x] == '.') {
    			board[y][x] = turn;
    			minValue = min(minValue, canWin(board, 'o'+'x'-turn));
    			board[y][x] = '.';
    		}
    	}
    // 플레이할수 없거나, 어떻게 해도 비기는 것이 최선인 경우
    if(minValue == 2 || minValue == 0) return ret = 0;
    // 최선이 상대가 이기는 거라면 난 무조건 지고, 상대가 지는 거라면 난 이긴다
    return ret = -minValue;
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {

    }
}

