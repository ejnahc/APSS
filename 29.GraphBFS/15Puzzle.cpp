// WARNING: 필요한 메모리와 시간이 지수적으로 증가한다
// see 15Puzzle.BSearch.cpp

// 게임판의 상태를 표현한다
class State {
    // 인접한 상태들의 목록을 반환한다
    vector<State> getAdjacent() const;
    // map에 State를 넣기 위한 비교 연산자
    bool operator < (const State& rhs) const;
    // 종료 상태와 비교하기 위한 연산자
    bool operator == (const State& rhs) const;
};

typedef map<State, int> StateMap;
// start에서 finish까지 가는 최단 경로의 길이를 반환한다
int bfs(State start, State finish) {
    // 예외: start == finish 일 경우
    if (start == finish) return 0;
    // 각 정점에서의 최단 경로의 길이를 저장하는 Map
    StateMap c;
    // 앞으로 방문할 정점들을 저장한다
    queue<State> q;
    q.push(start);
    c[start] = 0;
    // 너비 우선 탐색
    while (!q.empty()) {
        State here = q.front();
        q.pop();
        int cost = c[here];
        // 인접한 정점들의 번호를 얻어낸다
        vector<State> adjacent = here.getAdjacent();
        for (int i=0; i<adjacent.size(); i++) {
            // 아직 방문하지 않았으면
            if (c.count(adjacent[i]) == 0) {
                // 답을 찾았으면
                if (adjacent[i] == finish)
                    return cost + 1;
                c[adjacent[i]] = cost + 1;
                q.push(adjacent[i]);
            }
        }
    }

    // oops
    return -1;
}