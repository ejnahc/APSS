#include<cstdio>
#include<cassert>
#include<cstring>
#include<map>
#include<set>
#include<time.h>
#include<algorithm>
#include<stack>
#include<queue>
#include<utility>
#include<cmath>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// adj[][]는 floyd() 의 수행 결과
int V, adj[200][200];

// 간선 (a,b) 를 추가했을 때 그래프의 최단 거리 배열 adj를
// 적절히 갱신한다. 간선이 아무런 의미가 없을 경우 false를
// 반환한다.
bool update(int a, int b, int c) {	
	if(adj[a][b] <= c) return false;
	for(int x = 0; x < V; ++x) 
		for(int y = 0; y < V; ++y) 
			// x~y 최단경로가 (a,b)를 이용하려면
			// x~a-b~y 혹은 x~b-a~y 의 형태를 가져야 한다.
			adj[x][y] = min(adj[x][y], 
					min(adj[x][a] + c + adj[b][y],
						adj[x][b] + c + adj[a][y]));
	return true;
}


void display() {
	for(int i = 0; i < V; ++i) {
		for(int j = 0; j < V; ++j) 
			printf("%d ", adj[i][j]);
		printf("\n");
	}
	printf("===\n");
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	int M, N;
    	cin >> V >> M >> N;
    	for(int i = 0; i < V; ++i) 
    		for(int j = 0; j < V; ++j) 
    			if(i == j)
    				adj[i][j] = 0;
				else
					adj[i][j] = 987654321;
		for(int i = 0; i < M; ++i) {
			int a, b, c;
			cin >> a >> b >> c;
			adj[a][b] = adj[b][a] = min(adj[a][b], c);
		}
		for(int k = 0; k < V; ++k) 
			for(int i = 0; i < V; ++i) 
				for(int j = 0; j < V; ++j) 
					adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
		//display();
		int meaningless = 0;
		for(int i = 0; i < N; ++i) {
			int a, b, c;
			cin >> a >> b >> c;
			if(!update(a, b, c))
				++meaningless;

			//display();
			
		}
		cout << meaningless << endl;
    }
}

