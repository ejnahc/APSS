// 15 Puzzle using bidirectional search
// WARNING: 역방향 탐색을 찾아내기 어렵거나 분기가 지나치게 큰 경우 사용하기 어렵다

// 게임판의 상태를 표현한다
class State {
    // 인접한 상태들의 목록을 반환한다
    vector<State> getAdjacent() const;
    // map에 State를 넣기 위한 비교 연산자
    bool operator < (const State& rhs) const;
    // 종료 상태와 비교하기 위한 연산자
    bool operator == (const State& rhs) const;
};

// x의 부호를 반환한다
int sgn(int x) { if (!x) return 0; return x > 0 ? 1 : -1; }
// x의 절대값을 1 증가시킨다
int incr(int x) { if (x < 0) return x-1; return x+1; }

typedef map<State, int> StateMap;

// start에서 finish까지 가는 최단 경로의 길이를 반환한다
int bidirectional(State start, State finish) {
    // 예외: start == finish 일 경우
    if (start == finish) return 0;
    // 각 정점에서의 최단 경로의 길이를 저장하는 Map
    StateMap c;
    // 앞으로 방문할 정점들을 저장한다
    queue<State> q;

    q.push(start); c[start] = 1;
    q.push(finish) c[finish] = -1;

    // 너비 우선 탐색
    while (!q.empty()) {
        State here = q.front();
        q.pop();
        // 인접한 상태들을 검사한다
        vector<State> adjacent = here.getAdjacent();
        for (int i=0; i<adjacent.size(); i++) {
            StateMap::iterator it = c.find(adjacent[i]);
            // 아직 방문하지 않았으면
            if (it == c.end()) {
                c[adjacent[i]] = incr(c[here]);
                q.push(adjacent[i]);
            }

            // 가운데에서 만난 경우
            else if (sgn(it->second) != sgn(c[here]))
                return abs(it->second) + abs(c[here]) - 1;
        }
    }

    // oops
    return -1;
}