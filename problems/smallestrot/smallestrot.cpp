#include<cassert>
#include<algorithm>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 각 접미사들의 첫 t 글자를 기준으로 한 그룹 번호가 주어질 때,
// 주어진 두 접미사를 첫 2*t 글자를 기준으로 비교한다.
struct Comparator {
	const vector<int>& group;
	int t;

	Comparator(const vector<int>& _group, int _h) : group(_group), t(_h) { }

	bool operator () (int a, int b) {
		// 첫 t 글자가 다르면 이들을 이용해 비교한다
		if(group[a] != group[b]) return group[a] < group[b];
		// 아니라면 S_(a+t) 와 S_(b+t) 의 첫 t 글자를 비교한다
		return group[a + t] < group[b + t];
	}
};


// s 의 접미사 배열을 계산한다
vector<int> getSuffixArray(const string& s) {
	int n = s.size();

	// 각 접미사를 첫 글자를 기준으로 정렬한 뒤, 첫 글자가 같은 것 끼리
	// 그룹으로 묶고 각 접미사가 어떤 그룹에 속하는지를 보여주는 group[] 배열을 만드는..
	// 대신에 group[i] = S_i 의 첫 글자로 하면 같은 효과가 있다.
	vector<int> group(n);
	for(int i = 0; i < n; i++) group[i] = s[i];

	// 결과적으로 접미사 배열이 될 반환값. 이 배열을 lg(n) 번 정렬한다.
	vector<int> perm(n);
	for(int i = 0; i < n; i++) perm[i] = i;

    // group[] 은 첫 t 글자를 기준으로 생성되어 있다
	int t = 1;
	while(t < n) {
		// 첫 2t 글자를 기준으로 perm 을 다시 정렬한다
		Comparator compareUsing2T(group, t);
		stable_sort(perm.begin(), perm.end(), compareUsing2T);

		// 2t 글자가 n 을 넘는다면 이제 접미사 배열 완성!
		t *= 2;
		if(t >= n) break;

		// 2t 글자를 기준으로 한 그룹 정보를 만든다
		vector<int> newGroup(n);
		newGroup[perm[0]] = 0;
		for(int i = 1; i < perm.size(); i++)
			if(compareUsing2T(perm[i-1], perm[i]))
				newGroup[perm[i]] = newGroup[perm[i-1]] + 1;
			else
				newGroup[perm[i]] = newGroup[perm[i-1]];
		group = newGroup;
	}
	return perm;
}

vector<int> getLCP(const string& S, const vector<int>& A) {
	int n = S.size();
	vector<int> height(n), rank(n);
	for(int i = 0; i < n; i++)
		rank[A[i]] = i;
	int h = 0;
	for(int i = 0; i < n; i++)  {
		if(rank[i] > 0) {
			int j = A[rank[i] - 1];
			while(i + h < n && j + h < n && S[i + h] == S[j + h])
				++h;
			height[rank[i]] = h;
			if(h > 0) --h;
		}
	}
	return height;
}

vector<int> getPrefixOverlaps(const string& needle) {
	int n = needle.size();
	// overlap[i] = needle 의 첫 i 글자가 자기 자신과 얼마나 겹치나?
	vector<int> overlap(n+1, -1);
	overlap[0] = overlap[1] = 0;
	for(int i = 2; i <= n; ++i) {
		int candidate = overlap[i-1] + 1;
		while(candidate > 1 && needle[i-1] != needle[candidate-1])
			candidate = overlap[candidate-1] + 1;
		if(candidate == 1 && needle[0] != needle[i-1])
			candidate = 0;
		overlap[i] = candidate;
	}
	return overlap;
}

// haystack 에서 needle 이 출현하는 시작 위치들을 모두 반환한다.
int kmpSearch(const string& haystack, const string& needle) {
	int n = haystack.size(), m = needle.size();

	// pi[] 를 미리 계산한다
	vector<int> pi = getPrefixOverlaps(needle);

	// begin = matched = 0 에서부터 시작하자
	int begin = 0, matched = 0;
	// begin 의 최대값은 n - m
	while(begin <= n - m) {
		// 만약 짚더미의 해당 글자가 바늘의 해당 글자와 같다면
		if(matched < m && haystack[begin + matched] == needle[matched]) {
			++matched;
			// 결과적으로 m 글자가 모두 일치했다면 답에 추가한다
			if(matched == m) return begin;
		}
		else {
			// begin 를 matched - pi[matched] 만큼 옮길 수 있다
			// 예외: matched 가 0 인 경우에도 최소한 1 은 옮겨야 함
			begin += max(1, matched - pi[matched]);
			// begin 를 옮겼다고 처음부터 대응시킬 필요가 없다.
			// pi[matched] 만큼은 이미 대응되어 있음을 알고 있음
			matched = pi[matched];
		}
	}
	printf("can't find %s in %s\n", needle.c_str(), haystack.c_str());
	return -1;
}

// 사전 순으로 가장 앞에 오는 s 의 회전 결과를 구한다
string minShift(const string& s) {
	string s2 = s + s;
	vector<int> a = getSuffixArray(s2);
	for(int i = 0; i < a.size(); i++)
		if(a[i] < s.size())
			return s2.substr(a[i], s.size());
	return "__oops__";
}

int main() {
	int cases;
	cin >> cases;
	for(int i = 0; i < cases; i++) {
		int n;
		string s;
		cin >> n >> s;
		string s2 = s + s;
		vector<int> sufArray = getSuffixArray(s2);
		for(int i = 0; i < sufArray.size(); i++)
			if(sufArray[i] < n) {
				string a = minShift(s);
				string b = s2.substr(sufArray[i], n);
				assert(a == b);
				printf("%d\n", kmpSearch(s2, s2.substr(sufArray[i], n)));
				break;
			}

		/*

		vector<int> lcp = getLCP(s2, sufArray);
		//for(int i = 0; i < sufArray.size(); i++)  printf("sufArray[%d] = %d, string = %s, lcp = %d\n", i, sufArray[i], s2.c_str() + sufArray[i], lcp[i]);
		int ret = -1;
		for(int i = 0; i < sufArray.size(); i++) {
			if(ret != -1 && lcp[i] < n) break;
			if(sufArray[i] >= n) continue;
			if(ret == -1 || ret > sufArray[i])
				ret = sufArray[i];
		}
		printf("%d\n", ret);
		*/
	}
}

