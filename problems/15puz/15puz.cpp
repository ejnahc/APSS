#include<cstring>
#include<hash_map>
#include<cstdlib>
#include<cstdio>
#include<cassert>
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<map>
using namespace std;
using namespace __gnu_cxx;

const int dy[4] = { 0, 1, 0, -1 };
const int dx[4] = { 1, 0, -1, 0 };

typedef unsigned long long uint64;

// 64비트 정수를 4비트 정수 16개의 배열로 사용하기 위한 함수들

// idx 번째 숫자를 val 로 바꾼다. val 은 [0,15] 의 정수
uint64 setArray(uint64 array, int idx, uint64 val) {
	return (array & ~(15ULL << (4 * idx))) | (val << (4*idx));
}

// idx 번째 숫자를 반환한다. 반환값은 [0,15] 의 정수
int getArray(uint64 array, int idx) {
	return (array >> (4*idx)) & 15;
}

// 게임판의 상태를 표현한다
struct State {
	// 빈 칸의 좌표
	int by, bx;
	// 각 칸에 씌인 숫자를 저장한다
	uint64 tiles;
	// 현재 estimate
	int estimate;

	State() {
	}

	// 게임판의 상태로부터 생성
	State(const int board[4][4]) {
		tiles = 0;
		for(int y = 3; y >= 0; --y)
			for(int x = 3; x >= 0; --x) {
				tiles = (tiles * 16) + board[y][x];
				if(board[y][x] == 0) {
					by = y;
					bx = x;
				}
			}
		estimate = calcEstimate();
	}

	// 빈 칸의 좌표와 각 칸에 씌인 숫자로부터 생성
	State(int by, int bx, uint64 tiles, int estimate): 
		by(by), bx(bx), tiles(tiles), estimate(estimate) {
	}

	inline int manhattan(uint64 tiles, int y, int x) const {
		int num = getArray(tiles, y * 4 + x);
		if(num == 0) return 0;
		int ord = (num + 15) % 16;
		return abs(y - ord / 4) + abs(x - ord % 4);
	}

	// 현재 상태에서 목표 상태까지 필요한 움직임의 하한을 계산한다
	// 각 숫자에 대해 현재 위치와 최종 위치 사이의 맨해튼 거리의 합을 계산한다
	int calcEstimate() const {
		int ret = 0;
		for(int y = 0; y < 4; ++y)
			for(int x = 0; x < 4; ++x) {
				ret += manhattan(tiles, y, x);
				/*
				// (y,x) 에 있는 수 num 을 구한다
				int num = get(y, x);
				if(num == 0) continue;
				// num 이 최종적으로 가야 할 위치를 계산한다
				int ord = (num + 15) % 16;
				ret += abs(y - ord / 4) + abs(x - ord % 4);
				*/
			}
		return ret;
	}

	int getEstimate() const {
		return estimate;
	}

	// 인접한 상태들의 목록을 반환한다
	vector<State> getAdjacent() const {
		vector<State> ret;
		for(int k = 0; k < 4; k++)
			if(canMove(k))
				ret.push_back(move(k));
		return ret;
	};

	// 빈칸을 direction 방향으로 움직일 수 있는지 여부를 반환
	bool canMove(int direction) const {
		int blankY = by + dy[direction];
		int blankX = bx + dx[direction];
		return 0 <= blankY && blankY < 4 && 0 <= blankX && blankX < 4;
	}

	// 빈칸을 direction 방향으로 움직인 결과 상태를 반환한다
	State move(int direction) const {
		int y1 = by, x1 = bx;
		int y2 = y1 + dy[direction], x2 = x1 + dx[direction];
		int v1 = get(y1, x1), v2 = get(y2, x2);
		uint64 newtiles = setArray(tiles, y1*4+x1, v2);
		newtiles = setArray(newtiles, y2*4+x2, v1);
		return State(y2, x2, newtiles, 
				estimate - manhattan(tiles, y2, x2) + manhattan(newtiles, y1, x1));
	}

	// (y,x) 좌표의 숫자를 반환한다
	int get(int y, int x) const {
		return getArray(tiles, y * 4 + x);
	}

	bool operator < (const State& rhs) const {
		return tiles < rhs.tiles;
	}

	bool operator == (const State& rhs) const {
		return tiles == rhs.tiles;
	}
};

namespace __gnu_cxx {
	template<> 
	struct hash<State> {
		size_t operator() (const State& s) const {
			return s.tiles;
		}
	};
}

typedef map<State,int> StateMap;
//typedef hash_map<State,int> StateMap;

const int goal[4][4] = { { 1,2,3,4 }, { 5,6,7,8 }, { 9,10,11,12 }, { 13,14,15,0 } };

// start 에서 finish 까지 가는 최단 경로의 길이를 반환한다
int bfs(State start, State finish) {
    // 예외: start == finish 인 경우
    if(start == finish) return 0;

	// 각 정점까지의 최단 경로의 길이를 저장한다.
	StateMap c;
	// 앞으로 방문할 정점들을 저장한다
	queue<State> q;

	q.push(start);
	c[start] = 0;

	int maxQs = 0;

	// 너비 우선 탐색
	while(!q.empty()) {
		maxQs = max<int>(maxQs, q.size());
		State here = q.front();
		q.pop();

		int cost = c[here];
		// 인접한 정점들의 번호를 얻어낸다
		vector<State> adjacent = here.getAdjacent();
		for(int i = 0; i < adjacent.size(); ++i)
			if(c.count(adjacent[i]) == 0) {
				// 답을 찾았나?
				if(adjacent[i] == finish) {
					fprintf(stderr, "result %d max qs %d visited states %d\n", cost + 1,
							maxQs, c.size());
					return cost + 1;
				}
				c[adjacent[i]] = cost + 1;
				q.push(adjacent[i]);
			}
	}
	// 답을 찾지 못한 경우
	return -1;
}

const int SAMPLE_UPTO = 26;
void generate() {
	vector<long long> seen(SAMPLE_UPTO+1);
	State sampled[SAMPLE_UPTO+1];

	StateMap c;
	queue<State> q;
	State start(goal);
	q.push(start);
	c[start] = 0;
	int ld = 0;
	while(!q.empty()) {
		State here = q.front();
		q.pop();

		int distance = c[here];
		seen[distance]++;
		if(rand() % seen[distance] == 0)
			sampled[distance] = here;
		if(distance != ld) {
			printf("Sampled %Ld states in distance %d.\n", seen[ld], ld);			
			for(int i = 0; i < 16; i++) 
				printf("%d ", sampled[ld].get(i / 4, i % 4));
			printf("\n");
			ld = distance;
		}
		if(distance == SAMPLE_UPTO) continue;

		// 인접한 정점들의 번호를 얻어낸다
		vector<State> adjacent = here.getAdjacent();
		for(int i = 0; i < adjacent.size(); ++i)
			if(c.count(adjacent[i]) == 0) {
				c[adjacent[i]] = c[here] + 1;
				q.push(adjacent[i]);
			}
	}
}

// x 의 부호를 반환한다
int sgn(int x) { if(x < 0) return -1; if(x > 0) return 1; return 0; }
// x 의 절대값을 1 증가시킨다
int incr(int x) { if(x < 0) return x-1; return x+1; }

const int DEPTH_LIMIT = 60;
// start 에서 finish 까지 가는 최단 경로의 길이를 반환한다
int bidirectional(State start, State finish) {
    // 예외: start == finish 인 경우
    if(start == finish) return 0;

	// 각 정점까지의 최단 경로의 길이를 저장한다.
	StateMap c;
	
	// 앞으로 방문할 정점들을 저장한다
	queue<State> q;

	q.push(start);
	c[start] = 1;
	q.push(finish);
	c[finish] = -1;

	int maxQs = 0;

	// 너비 우선 탐색
	while(!q.empty()) {
		maxQs = max<int>(maxQs, q.size());
		State here = q.front();
		q.pop();

		int cost = c[here];
		if(abs(cost) * 2 + 1 > DEPTH_LIMIT) return -1;

		// 인접한 정점들의 번호를 얻어낸다
		vector<State> adjacent = here.getAdjacent();
		for(int i = 0; i < adjacent.size(); ++i) {
			StateMap::iterator it = c.find(adjacent[i]);
			if(it == c.end()) {
				c[adjacent[i]] = incr(cost);
				q.push(adjacent[i]);
			}
			// 가운데서 만난 경우
			else if(sgn(it->second) != sgn(cost)) {
				fprintf(stderr, "result %d maxqs %d visited states %d\n",
					abs(it->second) + abs(cost) - 1,
					maxQs,
					c.size());

				return abs(it->second) + abs(cost) - 1;
			}
		}
	}
	// 답을 찾지 못한 경우
	return -1;
}

StateMap cache;

int best, visited = 0;

// 깊이 우선 탐색
void dfs(State here, const State& finish, int steps) {
	// 지금까지 구한 최적해보다 더 좋을 가능성이 없으면 버린다
	//if(steps >= best) return;
	if(steps + here.getEstimate() >= best) return;
	// 목표 상태에 도달한 경우
	if(here == finish) { best = steps; return; }
	++visited;
	// 인접 상태들을 깊이 우선 탐색으로
	vector<State> adjacent = here.getAdjacent();
	for(int i = 0; i < adjacent.size(); ++i)
		dfs(adjacent[i], finish, steps+1);
}

// 점점 깊어지는 탐색
int ids(State start, State finish, int growthStep) {
	visited = 0;
	for(int limit = 4; ; limit += growthStep) {
		best = limit+1;
		dfs(start, finish, 0);
		if(best <= limit) {
			fprintf(stderr, "result %d visited states %d\n",
					best, visited);
			return best;
		}
	}
	return -1;
}

// 깊이 우선 탐색
void memoizingDFS(State here, const State& finish, int steps) {
	// 지금까지 구한 최적해보다 더 좋을 가능성이 없으면 버린다
	//if(steps >= best) return;
	if(steps + here.getEstimate() >= best) return;

	// 목표 상태에 도달한 경우
	if(here == finish) { best = steps; return; }
	StateMap::iterator it = cache.find(here);
	if(it != cache.end()) {
		best = min(best, steps + it->second);
		return;
	}

	// 인접 상태들을 깊이 우선 탐색으로
	vector<State> adjacent = here.getAdjacent();
	for(int i = 0; i < adjacent.size(); ++i)
		memoizingDFS(adjacent[i], finish, steps+1);
}

void fillCache(State start, int cacheLevels) {
	queue<State> q;
	q.push(start);
	cache[start] = 0;
	while(!q.empty()) {
		State here = q.front();
		q.pop();
		int cost = cache[here];
		if(cost == cacheLevels) break;

		vector<State> adjacent = here.getAdjacent();
		for(int i = 0; i < adjacent.size(); ++i)
			if(cache.count(adjacent[i]) == 0) {
				cache[adjacent[i]] = cost + 1;
				q.push(adjacent[i]);
			}
	}
	fprintf(stderr, "Precalculated final %d moves: %d states\n", cacheLevels, int(cache.size()));
}

int memoizedIds(State start, State finish, int cacheLevels, int growthStep) {
	if(cacheLevels > 0 && cache.size() == 0)
		fillCache(finish, cacheLevels);

	for(int limit = 4; ; limit += growthStep) {
		best = limit+1;
		memoizingDFS(start, finish, 0);
		if(best <= limit) return best;
	}
	return -1;
}
int solve(const int board[4][4], string algo) {
	// 시작 상태와 목표 상태의 정점 번호를 계산한다
	State start(board);
	State finish(goal);
	//assert(estimate(finish) == 0);

	if(algo == "BFS") return bfs(start, finish);
	if(algo == "BIDIR") return bidirectional(start, finish);
	if(algo == "IDS") return ids(start, finish, 1);
	if(algo == "BIDS1") return memoizedIds(start, finish, 19, 1);
	if(algo == "BIDS2") return memoizedIds(start, finish, 19, 2);
	if(algo == "BIDS3") return memoizedIds(start, finish, 19, 3);
	if(algo == "BIDS4") return memoizedIds(start, finish, 19, 4);
	if(algo == "BIDS5") return memoizedIds(start, finish, 19, 5);
	printf("algorithm [%s] not found\n", algo.c_str());
	return -1;
}
int main(int argc, char* argv[]) {
	if(argc == 2 && strcmp(argv[1], "GENERATE") == 0) generate();
	//test();
	int cases;
	cin >> cases;
	for(int cc = 0; cc < cases; ++cc) {
		int board[4][4];
		int by, bx;
		for(int y = 0; y < 4; y++)
			for(int x = 0; x < 4; x++)
				cin >> board[y][x];

		cout << solve(board, argc == 1 ? "BFS" : argv[1]) << endl;
	}
}
