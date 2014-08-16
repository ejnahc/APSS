#include <vector>

// 그래프의 인접 리스트 표현
vector<vector<int> > adj;

// discovered[i] : i번 정점의 발견 순서
// finished[i] : dfs(i) 가 종료되었으면 1, 아니면 0
vector<int> discovered, finished;

// 지금까지 발견한 정점의 수
int counter;

void dfs2(int here) {
    discovered[here] = counter++;

    // 모든 인접 정점을 순회하면서
    for (int i=0; i<adj[here].size(); i++) {
        int there = adj[here][i];
        cout << "(" << here << "," << there << ") is a ";

        // 아직 방문한 적이 없다면 방문한다.
        if (discovered[there] == -1) {
            cout << "tree edge" << endl;
            dfs2(there);
        }

        // 순방향 간선 : 만약 there가 here보다 늦게 발견됐으면 there는 here의 후손이다.
        else if (discovered[here] < discovered[there])
            cout << "forward edge" << endl;

        // 역방향 간선 : 만약 dfs2(there) 가 아직 종료하지 않았으면 there는 here의 선조다
        else if (finished[there] == 0)
            cout << "back edge" << endl;

        // 이 외의 경우는 모두 교차 간선이다
        else
            cout << "cross edge" << endl;
    }

    finished[here] = 1;
}