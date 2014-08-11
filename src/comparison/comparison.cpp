#include<algorithm>
#include<set>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct IntegerSet {
	vector<int> s;
};

bool operator == (const IntegerSet& a, const IntegerSet& b) {
	return a.s == b.s;
}

// a 가 b 의 부분집합이면 true, 아니면 false 를 반환한다
bool isSubset(const IntegerSet& a, const IntegerSet& b) {
	for(int i = 0; i < a.s.size(); i++)
		if(find(b.s.begin(), b.s.end(), a.s[i]) == b.s.end())
			return false;
	return true;
}

// a 가 b 의 부분집합일 때 a 가 항상 앞에 오도록 집합들을 정렬한다
bool operator < (const IntegerSet& a, const IntegerSet& b) {
	// a 와 b 가 같으면 무조건 false
	if(a == b) return false;
	// a 가 b 의 부분집합이면 a 가 앞에 와야 한다
	if(isSubset(a, b)) return true;
	// b 가 a 의 부분집합이면 b 가 앞에 와야 한다
	if(isSubset(b, a)) return false;
	// a 와 b 를 사전순으로 비교해 반환한다
	return lexicographical_compare(a.s.begin(), a.s.end(), b.s.begin(), b.s.end());
}

int main() {
	int n;
	cin >> n;
	vector<IntegerSet> sets(n);
	for(int i = 0; i < n; i++) {
		int m;
		cin >> m;
		vector<int> s(m);
		for(int j = 0; j < m; j++)
			cin >> s[j];
		sets[i].s = s;
	}
	sort(sets.begin(), sets.end());
	for(int i = 0; i < n; i++) {
		printf("{");
		for(int j = 0; j < sets[i].s.size(); j++)
			printf("%s%d", (j ? ", " : ""), sets[i].s[j]);
		printf("}\n");
	}
}

