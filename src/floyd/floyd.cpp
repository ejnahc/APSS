#include<iostream>
#include<algorithm>
#include<sstream>
#include<string>
#include<vector>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<cassert>
#include<numeric>
#include<set>
#include<map>
#include<queue>
#include<list>
#include<deque>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define REP(i,n) FOR(i,0,n)
#define FORE(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define CLEAR(x,with) memset(x,with,sizeof(x))
#define sz size()
typedef long long ll;

const int MAX_V = 100;
const int INF = 987654321;

int V;                           // 정점의 개수
int adj[MAX_V][MAX_V];           // 그래프의 인접 행렬 표현
int C[MAX_V+1][MAX_V][MAX_V];    // 점화식의 답을 저장하는 배열

void floyd_prototype() {
	// C[0] 을 초기화
	for(int i = 1; i <= V; ++i)
		for(int j = 1; j <= V; ++j)
			C[0][i][j] = adj[i][j];

	// C[k-1] 이 있으면 C[k] 의 답을 만들 수 있다
	for(int k = 1; k <= V; ++k)
		for(int u = 1; u <= V; ++u)
			for(int v = 1; v <= V; ++v)
				C[k][u][v] = min(C[k-1][u][v], C[k-1][u][k] + C[k-1][k][v]);
}

void floyd_prototype2() {
	// C[0] 을 초기화
	for(int i = 1; i <= V; ++i)
		for(int j = 1; j <= V; ++j)
			C[0][i][j] = adj[i][j];

	// C[k-1] 이 있으면 C[k] 의 답을 만들 수 있다
	for(int k = 1; k <= V; ++k)
		for(int u = 1; u <= V; ++u)
			for(int v = 1; v <= V; ++v)
				C[k%2][u][v] = min(C[(k-1)%2][u][v], C[(k-1)%2][u][k] + C[(k-1)%2][k][v]);
}

void floyd() {
	for(int k = 1; k <= V; ++k)
	{
		printf("%d\n", k);
		for(int i = 1; i <= V; ++i) //if(adj[i][k] < 987654321)
			for(int j = 1; j <= V; ++j)
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
	}
}

int main()
{
	int cases;
	cin >> cases;
	while(cases--)
	{
		int E;
		cin >> V >> E;
		for(int i = 1; i <= V; ++i)
			for(int j = 1; j <= V; ++j)
				adj[i][j] = 987654321;
		while(E--)
		{
			int a, b, c;
			cin >> a >> b >> c;
			adj[a][b] = adj[b][a] = c;
		}
		floyd();
	}
}
