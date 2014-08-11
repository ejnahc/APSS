#include<cassert>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// N 에서 자기 자신을 찾으면서 나타나는 부분 일치를 이용해
// pi[] 를 계산한다.
// pi[i] = N[..i] 의 접미사도 되고 접두사도 되는 문자열의 최대 길이
vector<int> getPartialMatchNaive(const string& N) {
	int m = N.size();
	vector<int> pi(m, 0);
	// 단순한 문자열 탐색 알고리즘을 구현한다
	for(int begin = 1; begin < m; ++begin) {
		for(int i = 0; i < m; ++i) {
			if(N[begin + i] != N[i]) break;
			// i + 1 글자가 서로 대응되었다.
			pi[begin + i] = max(pi[begin + i], i + 1);
		}
	}
	return pi;
}

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
vector<int> naiveSearch(const string& H, const string& N) {
  vector<int> ret;
  // 모든 시작 위치를 다 시도해 본다
  for(int begin = 0; begin + N.size() <= H.size(); ++begin) {
    bool matched = true;
    for(int i = 0; i < N.size(); ++i)
      if(H[begin + i] != N[i]) {
        matched = false;
        break;
      }
    if(matched) ret.push_back(begin);
  }
  return ret;
}

// "짚더미" H 의 부분 문자열로 "바늘" N 이 출현하는 시작 위치들을 모두 반환한다.
vector<int> kmpSearch(const string& H, const string& N) {
	int n = H.size(), m = N.size();
	vector<int> ret;

	// pi[] 를 미리 계산한다
	// pi[i] = N[..i] 의 접미사도 되고 접두사도 되는 문자열의 최대 길이
	vector<int> pi = getPartialMatch(N);
	vector<int> pi2 = getPartialMatchNaive(N);
	if(pi != pi2){
		printf("N = %s\n", N.c_str());
		printf("pi ="); for(int i = 0; i < pi.size(); i++) printf(" %d", pi[i]); printf("\n");
		printf("pi2 ="); for(int i = 0; i < pi2.size(); i++) printf(" %d", pi2[i]); printf("\n");
		assert(pi == pi2);
	}

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

vector<int> kmpSearch2(const string& H, const string& N) {
	int n = H.size(), m = N.size();
	vector<int> ret;
	vector<int> pi = getPartialMatch(N);

	// 현재 대응된 글자의 수
	int matched = 0;
	// 짚더미의 각 글자를 순회한다
	for(int i = 0; i < n; ++i) {
		// matched 번 글자와 짚더미의 해당 글자가 불일치할 경우,
		// 현재 대응된 글자의 수를 pi[matched-1] 로 줄인다
		while(matched > 0 && H[i] != N[matched])
			matched = pi[matched-1];
		// 글자가 대응될 경우
		if(H[i] == N[matched]) {
			++matched;
			if(matched == m) {
				ret.push_back(i - m + 1);
				matched = pi[matched-1];
			}
		}
	}

	return ret;
}


/*
vector<int> naiveSearch(const string& H, const string& N) {
	vector<int> ret;
	for(int i = 0; i < H.size(); i++)
		if(H.substr(i, N.size()) == N)
			ret.push_back(i);
	return ret;
}
*/

void printFailFunction(const string& N) {
	vector<int> overlap = getPartialMatch(N);
	vector<int> overlap2 = getPartialMatchNaive(N);
	printf("failure function for N %s:\n", N.c_str());
	for(int i = 0; i < overlap.size(); i++) {
		printf("%s: %d (%s)\n", N.substr(0, i+1).c_str(), overlap[i], N.substr(0, overlap[i]).c_str());
		printf("%s: %d (%s)\n", N.substr(0, i+1).c_str(), overlap2[i], N.substr(0, overlap2[i]).c_str());
	}
}

void testSearch(const string& H, const string& N) {
	//printf("testing H [%s] N [%s]\n", H.c_str(), N.c_str());
	vector<int> a = naiveSearch(H, N);
	vector<int> b = kmpSearch(H, N);
	if(a != b) {
		printf("H [%s] N [%s]\n", H.c_str(), N.c_str());
		printf("naive [");
		for(int i = 0; i < a.size(); i++) printf("%s%d", (i ? ", " : ""), a[i]);
		printf("] kmp [");
		for(int i = 0; i < b.size(); i++) printf("%s%d", (i ? ", " : ""), b[i]);
		printf("]\n");
		//printf("naive %d kmp1 %d kmp2 %d\n", a, b, c);
		assert(false);
	}
}

void testSearch2(const string& H, const string& N) {
	//printf("testing H [%s] N [%s]\n", H.c_str(), N.c_str());
	vector<int> a = kmpSearch(H, N);
	vector<int> b = kmpSearch2(H, N);
	if(a != b) {
		printf("H [%s] N [%s]\n", H.c_str(), N.c_str());
		printf("kmp1 [");
		for(int i = 0; i < a.size(); i++) printf("%s%d", (i ? ", " : ""), a[i]);
		printf("] kmp2 [");
		for(int i = 0; i < b.size(); i++) printf("%s%d", (i ? ", " : ""), b[i]);
		printf("]\n");
		//printf("naive %d kmp1 %d kmp2 %d\n", a, b, c);
		assert(false);
	}
}

string toString(int mask, int len) {
	string ret;
	for(int i = 0; i < len; i++)
		if(mask & (1<<i))
			ret += 'a';
		else
			ret += 'b';
	return ret;
}

void testAll(int h, int n) {
	for(int i = 0; i < (1<<h); i++) {
		string H = toString(i, h);
		for(int j = 0; j < (1<<n); j++) {
			string N = toString(j, h);
			testSearch2(H, N);
		}
	}
}

int main() {
	printFailFunction("aabaabac");
	testSearch2("abaabaabaabbbaabb", "aabaa");
	testSearch2("abaabaabaabbbaabb", "aabb");
	printFailFunction("ababaca");
	printFailFunction("abrabadabra");
	testSearch2("abracadabra", "aca");
	testSearch2("abracadabra", "acba");
	testSearch2("abracadabra", "abr");
	for(int h = 4; h <= 16; ++h) {
		for(int n = 1; n <= 6; n++) {
			testAll(h, n);
			printf("passed h=%d n=%d ..\n", h, n);
		}
	}
	printf("all done.\n");
}

