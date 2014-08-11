#include<iostream>
#include<cstring>
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

class ApplePick {
public:
	int k;
	vector<int> weights;
    // 현재까지 고른 사과들의 무게는 currentWeight 일 때
	// i번 사과 이후부터 j개의 사과를 고르고 그 중 제일 좋은 답을 반환한다.
	int bestPick(int i, int j, int currentWeight) {
		if(j == 0) return currentWeight > k ? 0 : currentWeight;
		if(i == weights.size()) return 0;

		return max(
			bestPick(i+1, j, currentWeight),
			bestPick(i+1, j-1, currentWeight + weights[i])
		);
	}
};

// 전체 사과의 수
int N;

// 지금까지 선택한 사과들이 picked 에 주어질 때, 추가로 A개의 사과를 고르는 모든 경우의 수를 출력
void generate(vector<int>& picked, int A)
{	
	// 기저 사례: 더 고를 사과가 없는 경우, 고른 사과들의 명단을 출력하고 종료한다
	if(A == 0) 
	{
		for(int i = 0; i < picked.size(); ++i) 
		{
			cout << picked[i] << " ";
		}
		cout << endl;
	}
	else
	{
		int firstApple = 0;

		// 이미 고른 사과가 있다면 마지막에 고른 것 다음 사과부터 고른다
		if(!picked.empty())
			firstApple = picked.back() + 1;

		// 이번에 고를 사과의 번호를 결정한다
		for(int i = firstApple; i < N; ++i) 
		{
			picked.push_back(i);
			generate(picked, A-1);
			picked.pop_back();
		}
	}
}

int main()
{
	vector<int> e;
	N = 5;
	generate(e,3);


	ApplePick pick;
	pick.weights.push_back(7);
	pick.weights.push_back(4);
	pick.weights.push_back(5);
	pick.weights.push_back(6);
	pick.k = 12;
	assert(pick.bestPick(0, 2, 0) == 12);
	pick.k = 13;
	assert(pick.bestPick(0, 2, 0) == 13);
	pick.k = 14;
	assert(pick.bestPick(0, 2, 0) == 13);
}
