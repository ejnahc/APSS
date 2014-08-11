#include<cstdio>
#include<algorithm>
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
	// 문자열의 끝에 도달할 때까지 찾으면서 부분 일치를 모두 기록한다.
	while(begin + matched < m) {
		if(N[begin + matched] == N[matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
		}
		else {
			if(matched == 0)
				++begin;
			else {
				begin += max(1, matched - pi[matched-1]);
				matched = pi[matched-1];
			}
		}
	}
	return pi;
}

// s 의 접두사도 되고 접미사도 되는 문자열들의 길이를 반환한다
vector<int> getPrefixSuffix(const string& s) {
	vector<int> ret, pi = getPartialMatch(s);

	int k = s.size();
	while(k > 0) {
		// s[..k-1] 는 답이다
		ret.push_back(k);
		// s[..k-1] 의 접미사도 되고 접두사도 되는 문자열도 답이다
		k = pi[k-1];
	}
	return ret;
}

int main() {
	string s;
	while(cin >> s) {
		vector<int> ret = getPrefixSuffix(s);
		reverse(ret.begin(), ret.end());
    	for(int i = 0; i < ret.size(); i++)
    		printf("%s%d", (i ? " " : ""), ret[i]);
    	printf("\n");

    }
}

