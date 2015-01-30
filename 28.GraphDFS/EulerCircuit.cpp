#include <vector>

using namespace std;

// 그래프의 인접 행렬 표현. adj[i][j] = i와 j 사이의 간선의 수
vector<vector<int> > adj;

// 무향 그래프의 인접 행렬 adj가 주어질 때 오일러 서킷을 계산한다
// 결과로 얻어지는 circuit을 뒤집으면 오일러 서킷이 된다

// 주의! 오일러 서킷임을 보장하지 않음.
// 조건 1: circuit[0] == circuit[circuit.size()-1] 인지 체크.
// 조건 2: degree가 odd인 vertice가 있는지 확인.
void getEulerCircuit(int here, vector<int>& circuit) {
    for (int there=0; there<adj.size(); ++there) {
        while (adj[here][there] > 0) {
            adj[here][there]--;
            adj[there][here]--; // 양 쪽 간선을 모두 지운다.
            getEulerCircuit(there, circuit);
        }
    }

    circuit.push_back(here);
}

// 오일러 트레일 찾기
// a에서 b로 가는 오일러 트레일을 찾으려면, a와 b 사이에 간선 (b, a)를 추가하여 오일러 서킷을 찾는다.
// 그리고 (b, a) 간선을 지워 서킷을 끊으면 우리가 원하는 오일러 트레일을 찾을 수 있다.
