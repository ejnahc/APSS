#include <vector>
#include <stack>

vector<vector<int> > adj;

// 각 정점의 컴포넌트 번호. 컴포넌트 번호는 0부터 시작하며
// 같은 강결합 컴포넌트에 속한 정점들의 컴포넌트 번호가 된다
vector<int> sccId, discovered, finished;
// 정점의 번호를 담는 스택
stack<int> st;

int sccCounter, vertexCounter;

// here를 루트로 하는 서브트리에서 역방향 간선으로 닿을 수 있는 최소의 발견 순서를 반환
int scc(int here) {
    int ret = discovered[here] = vertexCounter++;

    // 스택에 here를 넣는다. here의 후손들은 모두 스택에서 here 후에 들어간다
    st.push(here);

    for (int i=0; i<adj[here].size(); i++) {
        int there = adj[here][i];
        // (here, there)가 트리 간선
        if (discovered[there] == -1)
            ret = min(ret, scc(there));

        // (here, there)가 역행 간선인 경우 선조 정점의 발견 순서를 확인
        else if (discovered[there] < discovered[here]
            && finished[there] != 1)
            ret = min(ret, discovered[there]);
    }

    // here가 강결합 컴포넌트의 루트인지 확인
    if (ret == discovered[here]) {
        // here를 루트로 하는 서브트리에 남아 있는 정점들을 전부 하나의 컴포넌트로 묶는다
        while (true) {
            int t = st.top();
            st.pop();
            sccId[t] = sccCounter;
            if (t == here) break;
        }

        ++sccCounter;
    }

    finished[here] = 1;
    return ret;
}

// tarjan의 SCC 알고리즘
vector<int> tarjanSCC() {
    // 배열과 카운터 초기화
    sccId = discovered = finished = vector<int>(adj.size(), -1);
    sccCounter = vertexCounter = 0;

    // 모든 정점에 대하여 scc()를 호출
    for (int i=0; i<adj.size(); i++)
        if (discovered[i] == -1) scc(i);

    return sccId;
}