#include<cstdio>
#include<cstring>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int INF = 987654321;
const int MAXN = 20;

int n, k, m, l;
// prerequisite[i] = i 번째 과목의 선수과목의 집합
int prerequisite[MAXN];
// classes[i] = i 번째 학기에 개설되는 과목의 집합
int classes[10];

int cache[10][1<<MAXN];

// n 의 이진수 표현에서 켜진 비트의 수를 반환한다
int bitCount(int n) {
	return __builtin_popcount(n);
}

// 이번 학기가 semester 이고, 지금까지 들은 과목의 집합이 taken 일 때
// k 개 이상의 과목을 모두 들으려면 몇 학기나 더 있어야 하는가?
int graduate(int semester, int taken) {
	// 기저 사례: k 개 이상의 과목을 이미 들은 경우
	if(bitCount(taken) >= k) return 0;
	// 기저 사례: m 학기가 전부 지난 경우
	if(semester == m) return INF;

	// 메모이제이션
	int& ret = cache[semester][taken];
	if(ret != -1) return ret;
	ret = INF;

	// 이번 학기에 들을 수 있는 과목 중 아직 듣지 않은 과목들을 찾는다
	int canTake = (classes[semester] & ~taken);
	// 선수 과목을 다 듣지 않은 과목들을 걸러낸다
	for(int i = 0; i < n; i++)
		if((canTake & (1 << i)) && (taken & prerequisite[i]) != prerequisite[i])
			canTake &= ~(1 << i);
	// 이 집합의 모든 부분집합을 순회한다
	for(int take = canTake; take > 0; take = ((take - 1) & canTake)) {
		// 한 학기에 l 과목까지만 들을 수 있다
		if(bitCount(take) > l) continue;
		ret = min(ret, graduate(semester+1, taken | take) + 1);
	}

	// 이번 학기에 아무 것도 듣지 않을 경우
	ret = min(ret, graduate(semester+1, taken));
	return ret;
}

int main() {
	int cases;
	cin >> cases;
	for(int cc = 0; cc < cases; ++cc) {
		cin >> n >> k >> m >> l;
		for(int i = 0; i < n; i++) {
			prerequisite[i] = 0;
			int r;
			cin >> r;
			for(int j = 0; j < r; j++) {
				int required;
				cin >> required;
				prerequisite[i] |= (1 << required);
			}
		}
		for(int i = 0; i < m; i++) {
			classes[i] = 0;
			int c;
			cin >> c;
			for(int j = 0; j < c; j++) {
				int open;
				cin >> open;
				classes[i] |= (1 << open);
			}
		}
		memset(cache, -1, sizeof(cache));
		int ret = graduate(0, 0);
		if(ret >= 987654321) ret = -1;
		cout << ret << endl;
	}
}

