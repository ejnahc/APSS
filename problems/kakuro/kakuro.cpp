#include<cassert>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int INF = 987654321;
const int WHITE = 1;
const int BLACK = 0;

int maskSum[1024], maskLen[1024];
void calcMasks() {
	memset(maskSum, 0, sizeof(maskSum));
	memset(maskLen, 0, sizeof(maskLen));
	for(int mask = 0; mask < 1024; mask++) {
		for(int i = 0; i < 10; i++)
			if(mask & (1<<i)) {
				maskSum[mask] += i;
				maskLen[mask]++;
			}
	}
}

// mask 에 속한 원소들의 개수를 반환한다
int setSize(int mask) { return maskLen[mask]; }
// mask 에 속한 원소들의 합을 반환한다
int setSum(int mask) { return maskSum[mask]; }

// len 칸의 합이 sum 이고, 이 칸들에 이미 쓰인 수의 집합이 known 일 때
// 나머지 칸에 들어갈 수 있는 숫자의 집합을 반환한다
int getCandidates(int len, int sum, int known) {
	int allSets = 0;
	// 1~9 의 부분집합을 모두 생성하고, 그 중
	for(int set = 0; set < 1024; set += 2)
		// known 을 포함하고, 크기가 len 이며, 합이 sum 인 집합을 모두 찾는다
		if((set & known) == known && setSize(set) == len && setSum(set) == sum)
			allSets |= set;
	// known 에 이미 속한 숫자들은 답에서 제외한다
	return allSets & ~known;
}

// candidates[len][sum][known] = getCandidates(len, sum, known)
int candidates[10][46][1024];

// candidates[][][] 를 미리 계산해 둔다
void generateCandidates() {
	// 우선 전부 0 으로 초기화
	memset(candidates, 0, sizeof(candidates));
	// 1~9 의 부분집합을 전부 생성한다
	for(int set = 0; set < 1024; set += 2) {
		// 집합의 크기와 원소의 합을 계산해 둔다
		int l = setSize(set), s = setSum(set);

		// set 의 모든 부분집합에 대해 candidates[][][] 를 업데이트한다
		int subset = set;
		while(true) {
			// 숫자 l 개의 합이 s 이고, 이미 subset 숫자가 쓰여 있을 때
			// 전체 숫자의 집합이 set 이 되도록 나머지 숫자를 채워넣을 수 있다
			candidates[l][s][subset] |= (set & ~subset);
			if(subset == 0) break;
			subset = (subset - 1) & set;
		}
	}
}

const int MAXN = 55;

// 게임판의 정보
// color: 각 칸의 색깔 (0 = 검은 칸 혹은 힌트 칸, 1 = 흰 칸)
// value: 각 흰 칸에 쓴 숫자 (아직 쓰지 않은 칸은 0)
// hint: 각 칸에 해당하는 두 힌트의 번호
int n, color[MAXN][MAXN], value[MAXN][MAXN], hint[MAXN][MAXN][2];

// 각 힌트의 정보
// sum: 힌트 칸에 쓰인 숫자
// length: 힌트 칸에 해당하는 흰 칸의 수
// known: 힌트 칸에 해당하는 흰 칸에 쓰인 숫자들의 집합
int q, sum[MAXN*MAXN], length[MAXN*MAXN], known[MAXN*MAXN];

// (y,x) 에 val 을 쓴다
void put(int y, int x, int val) {
	for(int h = 0; h < 2; h++)
		known[hint[y][x][h]] += (1<<val);
	value[y][x] = val;
}

// (y,x) 에 쓴 val 을 지운다
void remove(int y, int x, int val) {
	for(int h = 0; h < 2; h++)
		known[hint[y][x][h]] -= (1<<val);
	value[y][x] = 0;
}

// 힌트 번호가 주어질 때 후보의 집합을 반환한다
int getCandHint(int hint) {
	return candidates[length[hint]][sum[hint]][known[hint]];
}

// 좌표가 주어질 때 해당 칸에 들어갈 수 있는 후보의 집합을 반환한다
int getCandCoord(int y, int x) {
	return getCandHint(hint[y][x][0]) & getCandHint(hint[y][x][1]);
}

void printSolution() {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++)
			printf("%s%d", (j ? " " : ""), value[i][j]);
		printf("\n");
	}
}

bool search() {
	// 들어갈 수 있는 수의 종류가 최소인 칸을 찾아보자
	int y = -1, x = -1, minCands = 1023;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if(color[i][j] == WHITE && value[i][j] == 0) {
				int cands = getCandCoord(i, j);
				if(setSize(minCands) > setSize(cands)) {
					minCands = cands;
					y = i; x = j;
				}
			}

	// 이 칸에 들어갈 숫자가 없으면 실패!
	if(minCands == 0) return false;

	// 모든 칸이 채워졌으면 출력하고 종료한다
	if(y == -1) {
		printSolution();
		return true;
	}

	// 숫자를 하나씩 채워보자
	for(int val = 1; val <= 9; ++val)
		if(minCands & (1<<val)) {
			put(y, x, val);
			if(search()) return true;
			remove(y, x, val);
		}

	return false;
}

void read() {
	cin >> n;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			cin >> color[i][j];

	memset(hint, -1, sizeof(hint));

	cin >> q;
	int dy[2] = { 0, 1 };
	int dx[2] = { 1, 0 };
	for(int i = 0; i < q; i++) {
		int y, x, direction;
		cin >> y >> x >> direction >> sum[i];
		--y; --x;
		length[i] = 0;
		while(true) {
			y += dy[direction]; x += dx[direction];
			if(y >= n || x >= n || color[y][x] == BLACK) break;
			hint[y][x][direction] = i;
			length[i]++;
		}
	}
	memset(known, 0, sizeof(known));
}

int main() {
	calcMasks();
	generateCandidates();

	int cases;
	cin >> cases;
	for(int cc = 0; cc < cases; ++cc) {
		read();
		memset(value, 0, sizeof(value));
		assert(search());
	}
}

