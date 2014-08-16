#include <vector>

// 그래프의 인접 리스트 표현
vector<vector<int> > adj;

// 각 정점의 발견 순서, -1로 초기화한다
vector<int> discovered;

// 각 정점이 절단점인지 여부를 저장한다. false로 초기화한다
vector<bool> isCutVertex;

int counter = 0;

// here를 루트로 하는 서브트리에 있는 절단점을 찾는다
// 반환 값은 해당 서브트리에서 역방향 간선으로 갈 수 있는 정점 중
// 가장 일찍 발견된 정점의 발견 시점으로 한다
// 처음 호출할 때는 isRoot = true로 둔다
int findCutVertex(int here, bool isRoot) {
    // 발견 순서를 기록한다
    discovered[here] = counter++;
    int ret = discovered[here];

    // 루트인 경우의 절단점 판정을 위해 자손 서브트리의 개수를 센다
    int children = 0;
    for (int i=0; i<adj[here].size(); i++) {
        int there = adj[here][i];
        if (discovered[there] == -1) {
            ++children;
            // 이 서브트리에서 갈 수 있는 가장 높은 정점의 번호
            int subtree = findCutVertex(there, false);

            // 그 번호가 자기 자신 이하인 경우 현재 위치가 절단점이다
            if (!isRoot
                && subtree >= discovered[here]) { /*****/
                isCutVertex[here] = true;
            }

            // 가장 일찍 발견된 역방향 간선
            ret = min(ret, subtree);
        } else {
            // 이미 발견한 경우
            ret = min(ret, discovered[there]);
        }
    }

    // 루트인 경우 절단점 판정은 서브트리의 개수로 한다
    if (isRoot) {
        isCutVertex[here] = (children >= 2);
    }

    // 이미 방문한 조상 중 가장 일찍 발견된 정점의 발견시점을 반환
    return ret;
}