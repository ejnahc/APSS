#include<cstdio>
#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 각 회의는 [begin,end) 구간 동안 회의실을 사용한다
int n;
int begin[100], end[100];

int schedule() {
	// 일찍 끝나는 순서대로 정렬한다
	vector<pair<int,int> > order;
	for(int i = 0; i < n; i++)
		order.push_back(make_pair(end[i], begin[i]));
	sort(order.begin(), order.end());

	// earliest: 다음 회의가 시작할 수 있는 가장 빠른 시간
	// selected: 지금까지 선택한 회의의 수
	int earliest = 0, selected = 0;

	for(int i = 0; i < order.size(); ++i) {
		int begin = order[i].second, end = order[i].first;
		if(earliest <= begin) {
			// earliest 를 마지막에 회의가 끝난 시간 이후로 갱신한다
			earliest = end;
			++selected;
		}
	}

	return selected;
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	cin >> n;
    	for(int i = 0; i < n; i++)
    		cin >> begin[i] >> end[i];
    	cout << schedule() << endl;
    }
}

