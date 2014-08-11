#include<set>
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
	vector<int> group(n+1);
	for(int i = 0; i < n; i++) group[i] = s[i];
	group[n] = -987654321;

	// 결과적으로 접미사 배열이 될 반환값. 이 배열을 lg(n) 번 정렬한다.
	vector<int> perm(n);
	for(int i = 0; i < n; i++) perm[i] = i;

	// group[] 은 첫 t 글자를 기준으로 생성되어 있다
	int t = 1;
	while(t < n) {
		// 첫 2t 글자를 기준으로 perm 을 다시 정렬한다
		Comparator compareUsing2T(group, t);
		sort(perm.begin(), perm.end(), compareUsing2T);

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

int countSubstringsNaive(const string& s) {
	set<string> m;
	for(int i = 0; i < s.size(); i++)
		for(int j = i; j < s.size(); j++)
			m.insert(s.substr(i, j-i+1));
	return m.size();
}

// s[i..] 와 s[j..] 의 공통 접두사의 최대 길이를 계산한다
int commonPrefix(const string& s, int i, int j) {
	int k = 0;
	while(i < s.size() && j < s.size() && s[i] == s[j]) { ++i; ++j; ++k; }
	return k;
}

// s 의 서로 다른 부분 문자열의 수를 센다
int countSubstrings(const string& s) {
	vector<int> a = getSuffixArray(s);
	int ret = 0;
	int n = s.size();
	for(int i = 0; i < a.size(); ++i) {
		int cp = 0;
		if(i > 0) cp = commonPrefix(s, a[i-1], a[i]);
		// a[i] 의 (n - a[i]) 개의 접두사들 중에서 cp 개는 중복이다.
		ret += s.size() - a[i] - cp;
	}
	return ret;
}

int main() {
	string s;
	while(cin >> s) {
		cout << countSubstrings(s) << endl;
	}
	const int ITER = 100000;
	for(int i = 0; i < ITER; i++) {
		int n = rand() % 100 + 1;
		string s;
		for(int j = 0; j < n; j++)
			s += char('a' + rand() % 2);
		int a = countSubstrings(s);
		int b = countSubstringsNaive(s);
		if(a != b) {
			cout << s << " expected " << b << " result " << a << endl;
			break;
		}

	}
	printf("all good.\n");
}

