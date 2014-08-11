#include<algorithm>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int n;
int m[10000], e[10000];

int heat() {
	// 어느 순서로 데워야 할지를 정한다
	vector<pair<int,int> > order;
	for(int i = 0; i < n; i++)
		order.push_back(make_pair(-e[i], i));
	sort(order.begin(), order.end());
	// 해당 순서대로 데워먹는 과정을 시뮬레이션한다
	int ret = 0, beginEat = 0;
	for(int i = 0; i < n; i++) {
		int box = order[i].second;
		beginEat += m[box];
		ret = max(ret, beginEat + e[box]);
	}
	return ret;
}

int main() {
    int cases;
    scanf("%d", &cases);
    for(int cc = 0; cc < cases; ++cc) {
    	scanf("%d", &n);
    	for(int i = 0; i < n; i++) scanf("%d", &m[i]);
    	for(int i = 0; i < n; i++) scanf("%d", &e[i]);
    	printf("%d\n", heat());
    }
}

