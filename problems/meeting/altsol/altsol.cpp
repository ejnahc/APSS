#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

bool solved;
vector<pair<int,int> > meetings;

// 두 구간 a 와 b 가 서로 겹치지 않는지를 확인한다
bool disjoint(const pair<int,int>& a, const pair<int,int>& b) {
	return a.second <= b.first || b.second <= a.first;
}


bool go(int here, vector<int>& selected) {
	if(here == meetings.size()) {
		printf("POSSIBLE\n");
		for(int i = 0; i < selected.size(); i++) {
			int m = selected[i];
			printf("%d %d\n", meetings[m].first, meetings[m].second);
		}
		return true;
	}
	for(int i = 0; i < 2; i++) {
		bool ok = true;
		for(int j = 0; j < selected.size(); j++)
			if(!disjoint(meetings[selected[j]], meetings[here+i])) {
				ok = false;
				break;
			}
		if(!ok) continue;
		selected.push_back(here + i);
		if(go(here + 2, selected)) return true;
		selected.pop_back();
		
	}
	return false;
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	int n;
    	cin >> n;
    	meetings.resize(2*n);
    	for(int i = 0; i < n*2; i++) 
    		cin >> meetings[i].first >> meetings[i].second;
    	vector<int> selected;
    	if(!go(0, selected)) printf("IMPOSSIBLE\n");
    }
}

