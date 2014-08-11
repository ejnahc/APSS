#include<cstring>
#include<iostream>
#include<algorithm>
#include<sstream>
#include<string>
#include<vector>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<cassert>
#include<numeric>
#include<set>
#include<map>
#include<queue>
#include<list>
#include<deque>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define REP(i,n) FOR(i,0,n)
#define FORE(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define CLEAR(x,with) memset(x,with,sizeof(x))
#define sz size()
typedef long long ll;

string W, S;

// 와일드카드 패턴 w 가 문자열 s 에 대응되는지 여부를 반환한다
bool match(const string& w, const string& s) {
	// w[pos] 와 s[pos] 를 맞춰나간다
	int pos = 0;
	while(pos < s.size() && pos < w.size() && (w[pos] == '?' || w[pos] == s[pos]))
		++pos;
	// 더 이상 대응할 수 없으면 왜 while 문이 끝났는지 확인한다
	// 1. 패턴 끝에 도달해서 끝난 경우: 문자열도 끝났어야 참
	if(pos == w.size())
		return pos == s.size();
	// 2. * 를 만나서 끝난 경우: * 에 몇 글자를 대응해야 할지 재귀호출하면서 확인한다
	if(w[pos] == '*') {
		for(int skip = 0; pos+skip <= s.size(); ++skip)
			if(match(w.substr(pos+1), s.substr(pos+skip)))
				return true;
		return false;
	}
	// 3. 이외의 경우에는 모두 대응되지 않는다
	return false;
}

int cache[5001][5001];

// 와일드카드 패턴 W[w..] 가 문자열 S[s..] 에 대응되는지 여부를 반환한다
bool matchMemoized(int w, int s) {
	int& ret = cache[w][s];
	if(ret != -1) return ret;
	// W[w] 와 S[s] 를 맞춰나간다
	while(s < S.size() && w < W.size() && (W[w] == '?' || W[w] == S[s])) {
		++w;
		++s;
	}
	// 더 이상 대응할 수 없으면 왜 while 문이 끝났는지 확인한다
	// 1. 패턴 끝에 도달해서 끝난 경우: 문자열도 끝났어야 참
	if(w == W.size()) return ret = (s == S.size());
	// 2. * 를 만나서 끝난 경우: * 에 몇 글자를 대응해야 할지 재귀호출하면서 확인한다
	if(W[w] == '*') {
		for(int skip = 0; skip+s <= S.size(); ++skip)
			if(matchMemoized(w+1, s+skip))
				return ret = 1;
		return ret = 0;
	}
	// 3. 이외의 경우에는 모두 대응되지 않는다
	return ret = 0;
}
// 와일드카드 패턴 W[w..] 가 문자열 S[s..] 에 대응되는지 여부를 반환한다
bool matchMemoized2(int w, int s) {
	int& ret = cache[w][s];
	if(ret != -1) return ret;
	if(w < W.size() && s < S.size() && (W[w] == '?' || W[w] == S[s]))
		return ret = matchMemoized2(w+1, s+1);
	// 더 이상 대응할 수 없으면 왜 while 문이 끝났는지 확인한다
	// 1. 패턴 끝에 도달해서 끝난 경우: 문자열도 끝났어야 참
	if(w == W.size()) return ret = (s == S.size());
	// 2. * 를 만나서 끝난 경우: * 에 몇 글자를 대응해야 할지 재귀호출하면서 확인한다
	if(W[w] == '*') {
		if(matchMemoized2(w+1, s) ||
			(s < S.size() && matchMemoized2(w, s+1)))
			return ret = 1;
	}
	// 3. 이외의 경우에는 모두 대응되지 않는다
	return ret = 0;
}

int main(int argc, char* argv[])
{
	int cases;
	cin >> cases;
	REP(cc,cases)
	{
		cin >> W;
		vector<string> ret;
		int cc2;
		cin >> cc2;
		while(cc2--)
		{
			cin >> S;
			CLEAR(cache,-1);
			if(argc == 1) {
				if(matchMemoized(0, 0)) ret.push_back(S);
			}
            else {
				if(matchMemoized2(0, 0)) ret.push_back(S);
			}
		}
		sort(all(ret));
		REP(i,ret.sz) cout << ret[i] << endl;
	}
}
