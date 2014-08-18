// 15 Puzzle using Iteratively Deepening Search

// 게임판의 상태를 표현한다
class State {
    // 인접한 상태들의 목록을 반환한다
    vector<State> getAdjacent() const;
    // map에 State를 넣기 위한 비교 연산자
    bool operator < (const State& rhs) const;
    // 종료 상태와 비교하기 위한 연산자
    bool operator == (const State& rhs) const;

    // 휴리스틱을 위한 값
    // 모든 타일에 대해 현재 위치와 목표 위치 사이의 맨해튼 거리를 더한다
    // Manhattan distance: |x1-x2| + |y1-y2|
    int estimate() const;
};

int best;

// 깊이 우선 탐색
void dfs(State here, const State& finish, int steps) {
    // 지금까지 구한 최적해보다 더 좋을 가능성이 없으면 버린다
    // if (steps >= best) return;
    if (steps + here.estimate() >= best) return;
    // 목표 상태에 도달한 경우
    if (here == finish) { best = steps; return; }
    // 인접 상태들을 깊이 우선 탐색으로 구한다
    vector<State> adjacent = here.getAdjacent();
    for (int i=0; i<adjacent.size(); i++)
        dfs(adjacent[i], finish, steps+1);
}

// 점점 깊어지는 탐색
int ids(State start, State finish, int growthStep) {
    for (int limit=4; 1; limit+=growthStep) {
        best = limit+1;
        dfs(start, finish, 0);
        if (best <= limit) return best;
    }

    return -1;
}