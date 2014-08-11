#include<algorithm>
#include<cassert>
#include<cstdio>
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

// a 의 접미사이면서 b 의 접두사인 문자열의 최대 길이를 구한다
int maxOverlap(const string& a, const string& b) {
	int n = a.size(), m = b.size();
	vector<int> pi = getPartialMatch(b);
	// begin = matched = 0 에서부터 시작하자
	int begin = 0, matched = 0;
	while(begin < n) {
		// 만약 짚더미의 해당 글자가 바늘의 해당 글자와 같다면
		if(matched < m && a[begin + matched] == b[matched]) {
			++matched;
			if(begin + matched == n)
				return matched;
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
	return 0;
}

int main() {
	string s;
	while(cin >> s) {
		string sr = s;
		reverse(sr.begin(), sr.end());
		if(sr == s)
			cout << s << endl;
		else {
			int ov = maxOverlap(s, sr);
			cout << s << sr.substr(ov) << endl;
		}
	}

}

