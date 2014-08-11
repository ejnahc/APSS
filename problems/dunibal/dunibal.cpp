#include<numeric>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
int n, d, p, q;
double cache[51][101];

// connected[i][j] = 마을 i, j 가 연결되어 있나 여부
// deg[i] = 마을 i 와 연결된 마을의 개수
int connected[51][51], deg[51];

double search(vector<int>& path) {
	// 기저 사례: d일이 지난 경우
	if(path.size() == d+1) {
		// 이 시나리오가 q 에서 끝나지 않는다면 무효
		if(path.back() != q) return 0.0;
		// path 의 출현 확률을 계산한다
		double ret = 1.0;
		for(int i = 0; i + 1 < path.size(); ++i)
			ret /= deg[path[i]];
		return ret;
	}
	double ret = 0;
	// 경로의 다음 위치를 결정한다
	for(int there = 0; there < n; there++)
		if(connected[path.back()][there]) {
			path.push_back(there);
			ret += search(path);
			path.pop_back();
		}
	return ret;
}

double search2(int here, int days) {
	// 기저 사례: d 일이 지난 경우
	if(days == d) return (here == q ? 1.0 : 0.0);
	// 메모이제이션
	double& ret = cache[here][days];
	if(ret > -0.5) return ret;
	ret = 0.0;
	for(int there = 0; there < n; ++there)
		if(connected[here][there])
			ret += search2(there, days+1) / deg[here];
	return ret;
}

double search3(int here, int days) {
	// 기저 사례: 0 일째
	if(days == 0) return (here == p ? 1.0 : 0.0);
	// 메모이제이션
	double& ret = cache[here][days];
	if(ret > -0.5) return ret;
	ret = 0.0;
	for(int there = 0; there < n; ++there)
		if(connected[here][there])
			ret += search3(there, days-1) / deg[there];
	return ret;
}
int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	cin >> n >> d >> p;
    	for(int i = 0; i < n; i++) {
    		for(int j = 0; j < n; j++)
    			cin >> connected[i][j];
    		deg[i] = accumulate(connected[i], connected[i]+n, 0);
		}
		int queries;
		cin >> queries;
		for(int i = 0; i < n; i++)
			for(int j = 0; j <= d; j++)
				cache[i][j] = -1;
		for(int i = 0; i < queries; i++) {
			cin >> q;
			if(i) printf(" ");
			vector<int> path(1, p);
			printf("%.8lf", search3(q, d));
		}
		printf("\n");
    }
}

