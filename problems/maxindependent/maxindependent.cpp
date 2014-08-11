#include<cassert>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int MAXN = 25;
int n;
// explodes[i] 는 i 와 같이 두었을 때 폭발하는 물질의 집합
int explodes[MAXN];

// 주어진 집합이 안정적인지 확인한다
bool isStable(int set) {
	for(int i = 0; i < n; ++i)
		if((set & (1<<i)) && (set & explodes[i]))
			return false;
	return true;
}

// 모든 안정적인 집합의 수를 센다
int countStableSet() {
	int ret = 0;
	// 모든 집합을 만들어 보자
	for(int set = 1; set < (1<<n); ++set) {
		// 우선 안정적이 아니라면 셀 필요가 없다.
		if(!isStable(set)) continue;
		// 극대 안정 집합인지 확인하기 위해, 넣을 수 있는 다른 물질이 있나 확인한다
		bool canExtend = false;
		for(int add = 0; add < n; ++add)
			// add 가 집합에 포함되어 있지 않고, set 에 add 를 넣어도 안정적이라면
			if((set & (1 << add)) == 0 && (explodes[add] & set) == 0) {
				canExtend = true;
				break;
			}
		if(!canExtend)
			++ret;
	}
	return ret;
}

// 어떤 부분집합을 본 적이 있는지 표시한다
bool seen[1<<MAXN];

int countStableSet2() {
	int ret = 0;
	memset(seen, 0, sizeof(seen));
	// 꽉 찬 집합부터 시작해서 밑으로 내려온다
	for(int set = (1<<n)-1; set > 0; --set) {
		// 이 집합이 어떤 극대 안정 집합의 부분 집합이거나, 안정적이지 않은 경우 무시한다
		if(seen[set] || !isStable(set)) continue;
		// 이 집합의 모든 집합을 앞으로 무시한다
		for(int subset = (set - 1) & set; subset > 0; subset = (subset - 1) & set)
			seen[subset] = true;
		++ret;
	}
	return ret;
}

int main(int argc, char* argv[]) {
	const int TRIALS = 20;
	srand(12743);
	n = MAXN;
	memset(explodes, 0, sizeof(explodes));
	for(int i = 0; i < n; i++)
		for(int j = 0; j < i; j++)
			if(rand()%3 == 0) {
				explodes[i] |= (1<<j);
				explodes[j] |= (1<<i);
			}
	for(int it = 0; it < TRIALS; ++it) {
		//clock_t timer1 = clock();
		int a = countStableSet();
		printf("."); fflush(stdout);

	}

	printf("\n");

}

