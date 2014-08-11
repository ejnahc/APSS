#include<cassert>
#include<cstdio>
#include<stack>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 각 판자의 높이를 저장하는 배열
vector<int> h;

// 스택을 사용한 O(n) 해법
int solveStack() {
	// 남아 있는 판자들의 위치들을 저장한다
	stack<int> remaining;
	h.push_back(0);

	int ret = 0;
	for(int i = 0; i < h.size(); ++i) {
		// 남아 있는 판자들 중 오른쪽 끝 판자가 h[i] 보다 높다면
		// 이 판자의 최대 사각형은 i 에서 끝난다.
		while(!remaining.empty() && h[remaining.top()] >= h[i]) {
			int j = remaining.top();
			remaining.pop();

			int width = -1;
			// j 번째 판자 왼쪽에 판자가 하나도 안 남아 있는 경우,
			// left[j] = -1, 아닌 경우 left[j] = 남아 있는 판자 중
			// 가장 오른쪽에 있는 판자의 번호 가 된다.
			if(remaining.empty())
				width = i;
			else
				width = (i - remaining.top() - 1);
			ret = max(ret, h[j] * width);
		}
		remaining.push(i);
	}
	return ret;
}

// h[left..right] 구간에서 찾아낼 수 있는 가장 큰 사각형의 넓이를 반환한다
int solve(int left, int right) {
	// 기저 사례: 판자가 하나밖에 없는 경우
	if(left == right) return h[left];

	// [left,mid], [mid+1,right] 의 두 구간으로 문제를 분할한다
	int mid = (left + right) / 2;
	// 분할한 문제를 각개격파
	int ret = max(solve(left, mid), solve(mid+1, right));
	// 부분 문제 3: 두 부분에 모두 걸치는 사각형 중 가장 큰 것을 찾는다.
	int lo = mid, hi = mid+1;
	int height = min(h[lo], h[hi]);
	// [mid,mid+1] 만 포함하는 너비 2인 사각형을 고려한다
	ret = max(ret, height * 2);
	// 사각형이 입력 전체를 덮을 때까지 확장해 나간다
	while(left < lo || hi < right) {
		// 항상 높이가 더 높은 쪽으로 확장한다
		if(hi < right && (lo == left || h[lo-1] < h[hi+1])) {
			++hi;
			height = min(height, h[hi]);
		}
		else {
			--lo;
			height = min(height, h[lo]);
		}
		// 확장한 후 사각형의 넓이
		ret = max(ret, height * (hi - lo + 1));
	}
	return ret;
}

int n;
// 판자의 높이를 담은 배열 h[] 가 주어질 때 사각형의 최대 너비를 반환한다
int bruteForce(const vector<int>& h) {
	int ret = 0;
	int N = h.size();
	for(int left = 0; left < N; left++) {
		int minHeight = h[left];
		for(int right = left; right < N; right++) {
			minHeight = min(minHeight, h[right]);
			ret = max(ret, (right - left + 1) * minHeight);
		}
	}
	return ret;
}

int main() {
    int cases;
    cin >> cases;
    while(cases--) {
    	cin >> n;
    	h.resize(n);
    	for(int i = 0; i < n; i++) {
    		cin >> h[i];
    	}
    	//cout << bruteForce(h) << endl;
    	// int sol1 = solve(0, n-1);
    	int sol2 = solveStack();
    	// if(sol1 != sol2) {

    	// 	printf("solve %d solveStack %d\n", sol1, sol2);
    	// }
    	// assert(sol1 == sol2);
    	cout << sol2 << endl;
    }
}

