#include<algorithm>
#include<map>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int n, m;
// canEat[person] = person 이 먹을 수 있는 음식들의 번호
// eaters[food] = food 를 먹을 수 있는 친구들의 번호
vector<int> canEat[50], eaters[50];

int best;
// chosen: 지금까지 선택한 음식의 수
// edible: 이 중 각 친구가 먹을 수 있는 음식의 수
void search(vector<int>& edible, int chosen) {
	// 간단한 가지치기
	if(chosen >= best) return;

	// 아직 먹을 음식이 없는 첫 번째 친구를 찾는다
	int first = 0;
	while(first < n && edible[first] > 0) ++first;

	// 모든 친구가 먹을 음식이 있는 경우 종료한다
	if(first == n) { best = chosen; return; }

	// 이 친구가 먹을 수 있는 음식을 하나 만든다
	for(int i = 0; i < canEat[first].size(); ++i) {
		int food = canEat[first][i];
		for(int j = 0; j < eaters[food].size(); ++j) edible[eaters[food][j]]++;
		search(edible, chosen+1);
		for(int j = 0; j < eaters[food].size(); ++j) edible[eaters[food][j]]--;
	}
}

int solve() {
	vector<int> edible(n, 0);
	best = m;
	search(edible, 0);
	return best;
}

int greedy() {
	// greedy
	vector<int> satisfied(n, 0);
	int selected = 0;
	while(true) {
		if(find(satisfied.begin(), satisfied.end(), 0) == satisfied.end()) break;
		int bestFood = -1, bestBet = -1;
		for(int food = 0; food < m; ++food) {
			int canSatisfy = 0;
			for(int i = 0; i < eaters[food].size(); i++) {
				int person = eaters[food][i];
				if(satisfied[person] == 0) {
					canSatisfy++;
				}
			}
			if(canSatisfy >= bestBet) {
				bestFood = food;
				bestBet = canSatisfy;
			}
		}
		++selected;
		for(int i = 0; i < eaters[bestFood].size(); i++) {
			int person = eaters[bestFood][i];
			satisfied[person]++;
		}

	}
	return selected;
}

// food: 이번에 고려해야 할 음식의 번호
// edible: 지금까지 고른 음식 중 각 친구가 먹을 수 있는 음식의 수
// chosen: 지금까지 고른 음식의 수
void slowSearch(int food, vector<int>& edible, int chosen) {
	// 간단한 가지치기
	if(chosen >= best) return;

	// 기저 사례: 모든 음식에 대해 만들지 여부를 결정했으면,
	// 모든 친구가 음식을 먹을 수 있는지 확인하고 그렇다면 최적해를 갱신한다
	if(food == m) {
		if(find(edible.begin(), edible.end(), 0) == edible.end())
			best = chosen;
		return;
	}

	// food 음식을 만들지 않는 경우
	slowSearch(food+1, edible, chosen);

	// food 를 만드는 경우
	for(int j = 0; j < eaters[food].size(); ++j) edible[eaters[food][j]]++;
	slowSearch(food+1, edible, chosen+1);
	for(int j = 0; j < eaters[food].size(); ++j) edible[eaters[food][j]]--;
}

int solve2() {
	best = m;
	//greedy();
	vector<int> edible(n, 0);
	slowSearch(0, edible, 0);
}

int main(int argc, char* argv[]) {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	cin >> n >> m;
    	for(int i = 0; i < 50; i++) {
    		canEat[i].clear();
    		eaters[i].clear();
    	}
    	map<string,int> names;
    	for(int i = 0; i < n; i++) {
    		string name;
    		cin >> name;
    		names[name] = i;
		}


    	for(int food = 0; food < m; food++) {
    		int sz;
    		cin >> sz;
    		for(int j = 0; j < sz; j++) {
    			string name;
    			cin >> name;
    			int eater = names[name];
    			eaters[food].push_back(eater);
    			canEat[eater].push_back(food);
			}
    	}

    	string algo = "search1";
    	if(argc > 1) algo = argv[1];

    	if(algo == "search1")
	    	cout << solve() << endl;
		else if(algo == "slowSearch")
	    	cout << solve2() << endl;
		else if(algo == "greedy")
			cout << greedy() << endl;
		else {
			printf("Unknown algo %s\n", algo.c_str());
			break;
		}

    }
}

