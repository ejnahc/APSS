#include<fstream>
#include<time.h>
#include<cstdio>
#include<algorithm>
#include<utility>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int boardH, boardW;
int covered[50][50];
vector<string> board;
int blockSize;

// 블록의 각 회전된 형태를 상대 좌표의 목록으로 저장해 둔다
vector<vector<pair<int,int> > > rotations;

// 2차원 배열 arr 을 시계방향으로 90도 돌린 결과를 반환한다
vector<string> rotate(const vector<string>& arr) {
	vector<string> ret(arr[0].size(), string(arr.size(), ' '));
	for(int i = 0; i < arr.size(); i++)
		for(int j = 0; j < arr[0].size(); j++)
			ret[j][arr.size()-i-1] = arr[i][j];
	return ret;
}

// block 의 4가지 회전 형태를 만들고 이들을 상대 좌표의 목록으로 변환한다.
void generateRotations(vector<string> block) {
	rotations.clear();
	rotations.resize(4);
	for(int rot = 0; rot < 4; rot++) {
		int originY = -1, originX = -1;
		for(int i = 0; i < block.size(); i++)
			for(int j = 0; j < block[i].size(); j++)
				if(block[i][j] == '#') {
					if(originY == -1) {
						originY = i;
						originX = j;
					}
					rotations[rot].push_back(make_pair(i - originY, j - originX));
				}
		// 블록을 시계 방향으로 90도 회전한다
		block = rotate(block);
	}
	// 4가지 회전 형태 중 중복이 있을 경우 이를 제거한다
	sort(rotations.begin(), rotations.end());
	rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());
	blockSize = rotations[0].size();
}

// (y,x) 를 (0,0) 으로 해서 cells 로 표현된 블록을 내려놓거나, 들어올린다.
// delta 가 1 이면 내려놓고, -1 이면 들어올린다.
// 블록이 검은 칸이나 다른 블록과 겹치거나 게임판 밖으로 나가면 false 를 반환한다.
bool set(int y, int x, const vector<pair<int,int> >& cells, int delta) {
	bool ok = true;
	for(int i = 0; i < cells.size(); i++) {
		int cy = y + cells[i].first, cx = x + cells[i].second;
		if(cy < 0 || cx < 0 || cy >= boardH || cx >= boardW)
			ok = false;
		else {
			covered[cy][cx] += delta;
			if(covered[cy][cx] > 1) ok = false;
		}
	}
	return ok;
}

int best;

// placed: 지금까지 놓은 블록의 수
// blanks: 남은 빈칸의 수
void search(int placed, int blanks) {
	// 빈칸 중 가장 윗줄 왼쪽에 있는
	int y = -1, x = -1;
	for(int i = 0; i < boardH; i++) {
		for(int j = 0; j < boardW; j++)
			if(covered[i][j] == 0) {
				y = i;
				x = j;
				break;
			}
		if(y != -1) break;
	}
	// 기저 사례: 게임판의 모든 칸을 처리한 경우
	if(y == -1) {
		best = max(best, placed);
		return;
	}

	// 가지치기
	int upperBound = blanks / blockSize + placed;
	if(upperBound <= best) return;

	// 이 칸을 덮는다
	for(int i = 0; i < rotations.size(); i++) {
		if(set(y, x, rotations[i], 1))
			search(placed+1, blanks - blockSize);
		set(y, x, rotations[i], -1);
	}

	// 이 칸을 덮지 않고 막아 둔다
	covered[y][x]++;
	search(placed, blanks - 1);
	covered[y][x]--;
}

int solve() {
	int blanks = 0;
	for(int i = 0; i < boardH; i++)
		for(int j = 0; j < boardW; j++)
			if(board[i][j] == '.')
				++blanks;
	best = 0;
	for(int i = 0; i < boardH; i++) {
		for(int j = 0; j < boardW; j++)
			covered[i][j] = (board[i][j] == '#' ? 1 : 0);
	}

	//clock_t begin = clock();
	search(0, blanks);
	//double elapsed = (clock() - begin) * 1.0 / CLOCKS_PER_SEC;
	//fprintf(stderr, "%d,%d,%.4lf\n", blanks, blockSize, elapsed);
	return best;
}

int main() {
	/*
	   ifstream inp("samples.txt");
	   int s;
	   set<int> samples;
	   while(inp >> s) samples.insert(s);
	   */

	int cases;
	cin >> cases;
	for(int cc = 0; cc < cases; ++cc) {
		int blockH, blockW;
		cin >> boardH >> boardW >> blockH >> blockW;
		board.resize(boardH);
		vector<string> block(blockH);

		for(int i = 0; i < boardH; i++)
			cin >> board[i];
		for(int i = 0; i < blockH; i++)
			cin >> block[i];
		/*
		   if(samples.count(cc)) {
		   fprintf(stderr, "%d %d %d %d\n", boardH, boardW, blockH, blockW);
		   for(int i = 0; i < boardH; i++)
		   fprintf(stderr, "%s\n", board[i].c_str());
		   for(int i = 0; i < blockH; i++)
		   fprintf(stderr, "%s\n", block[i].c_str());
		   }*/

		generateRotations(block);
		cout << solve() << endl;
	}
}

