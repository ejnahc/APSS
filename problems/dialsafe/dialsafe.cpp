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

// N 에서 자기 자신을 찾으면서 나타나는 부분 일치를 이용해
// pi[] 를 계산한다.
// pi[i] = N[..i] 의 접미사도 되고 접두사도 되는 문자열의 최대 길이
vector<int> getPartialMatch(const string& N) {
	int m = N.size();
	vector<int> pi(m, 0);

	// KMP 로 자기 자신을 찾는다

	// N 을 N 에서 찾는다. begin=0 이면 자기 자신을 찾아버리니까 안됨!
	int begin = 1, matched = 0;
	// 비교할 문자가 N 의 끝에 도달할 때까지 찾으면서 부분 일치를 모두 기록한다.
	while(begin + matched < m) {
		if(N[begin + matched] == N[matched]) {
			++matched;
			pi[begin+matched-1] = matched;
		}
		else {
			if(matched == 0)
				++begin;
			else {
				begin += matched - pi[matched-1];
				matched = pi[matched-1];
			}
		}
	}
	return pi;
}

// "짚더미" H 의 부분 문자열로 "바늘" N 이 출현하는 시작 위치들을 모두 반환한다.
vector<int> kmpSearch(const string& H, const string& N) {
	int n = H.size(), m = N.size();
	vector<int> ret;

	// pi[] 를 미리 계산한다
	// pi[i] = N[..i] 의 접미사도 되고 접두사도 되는 문자열의 최대 길이
	vector<int> pi = getPartialMatch(N);

	// begin = matched = 0 에서부터 시작하자
	int begin = 0, matched = 0;
	// begin 의 최대값은 n - m
	while(begin <= n - m) {
		// 만약 짚더미의 해당 글자가 바늘의 해당 글자와 같다면
		if(matched < m && H[begin + matched] == N[matched]) {
			++matched;
			// 결과적으로 m 글자가 모두 일치했다면 답에 추가한다
			if(matched == m) ret.push_back(begin);
		}
		else {
			// 예외: matched 가 0 인 경우에는 다음 칸에서부터 계속
			if(matched == 0)
				++begin;
			else {
				// begin 를 matched - pi[matched-1] 만큼 옮길 수 있다
				begin += matched - pi[matched-1];
				// begin 를 옮겼다고 처음부터 다시 비교할 필요가 없다.
				// 옮긴 후에도 pi[matched-1] 만큼은 항상 일치하기 때문이다.
				matched = pi[matched-1];
			}
		}
	}
	return ret;
}


int shifts(const string& original, const string& next) {
  return kmpSearch(original + original, next)[0];
}

int main() {
  int cases;
  cin >> cases;
  for(int cc = 0; cc < cases; ++cc) {
    string current, next;
    int n;
    cin >> n;
    cin >> current;
    int ret = 0;
    for(int i = 0; i < n; ++i) {
      cin >> next;
      if(i % 2 == 1)
        ret += shifts(current, next);
      else
        ret += shifts(next, current);
      current = next;
    }
    cout << ret << endl;

  }
}

