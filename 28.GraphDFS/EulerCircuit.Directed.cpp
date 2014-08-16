#include <vector>

using namespace std;

// 그래프의 인접 행렬 표현. adj[i][j] = i와 j 사이의 간선의 수
vector<vector<int> > adj;

// *유향* 그래프의 인접 행렬 adj가 주어질 때 오일러 서킷을 계산한다
// 결과로 얻어지는 circuit을 뒤집으면 오일러 서킷이 된다
void getEulerCircuit(int here, vector<int>& circuit) {
    for (int there=0; there<adj.size(); ++there) {
        while (adj[here][there] > 0) {
            adj[here][there]--; // 간선을 지운다.
            getEulerCircuit(there, circuit);
        }
    }

    circuit.push_back(here);
}

// 오일러 트레일 찾기
// a에서 b로 가는 오일러 트레일을 찾으려면, a와 b 사이에 간선 (b, a)를 추가하여 오일러 서킷을 찾는다.
// 그리고 (b, a) 간선을 지워 서킷을 끊으면 우리가 원하는 오일러 트레일을 찾을 수 있다.

vector<int> getEulerTrailOrCircuit() {
    vector<int> circuit;
    // 우선 트레일을 찾아본다: 시작점이 존재하는 경우
    for (int i=0; i<26; ++i) {
        if (outdegree[i] == indegree[i] + 1) {
            getEulerCircuit(i, circuit);
            return circuit;
        }
    }

    // 아니면 서킷이니, 간선에 인접한 아무 정점에서나 시작한다
    for (int i=0; i<26; ++i) {
        if (outdegree[i]) {
            getEulerCircuit(i, circuit);
            return circuit;
        }
    }

    // 모두 실패한 경우 빈 배열을 반환한다
    return circuit;
}