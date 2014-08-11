#include<iostream>
#include<cstring>
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

class WildCardMatcher {
	// 와일드카드와 원문 문자열
	string w, s;
	// match(a,b) 의 계산 결과를 저장한다: 객체가 생성될 때
	// 미리 -1 로 초기화해 둔다
	int cache[101][101];

public:

	// w[a~] 와 s[b~] 을 대응시킬 수 있으면 1, 아니면 0 을 반환한다
	int match(int a, int b) {
		// 기저 사례 확인
		if(a == w.size() && b == s.size()) return 1;
		if(a == w.size()) return 0;
		if(b == s.size()) {
			for(int i = a; i < w.size(); ++i)
				if(w[i] != '*') 
					return 0;
			return 1;
		}
		int& ret = cache[a][b];
		if(ret != -1) return ret;
		// 첫 글자가 '?' 이거나, 원문의 첫 글자와 같으면 다음 글자로
		if(w[a] == '?' || w[a] == s[b])
			ret = match(a+1, b+1);
		// '*' 이면, 이 글자가 원문의 몇 글자와 대응될지를 정한다
		else if(w[a] == '*') {
			for(int i = 0; b <= s.size() - i; ++i) 
				// '*' 가 i글자에 대응되면, 남는 문자열을 (a+1, b+i) 
				// 로 표현할 수 있다.
				if(match(a+1, b+i)) {
					ret = 1;
					break;
				}
			}
			//ret = match(a+1, b) || match(a, b+1);
		}
		else
			ret = 0;
		return ret;
	}


	WildCardMatcher(string w_, string s_) : w(w_), s(s_) {
		CLEAR(cache, -1);
	}
};

int main()
{
	int cases;
	cin >> cases;
	REP(cc,cases)
	{
		string w; vector<string> ret;
		int n;
		cin >> w >> n;
		while(n--)
		{
			string s;
			cin >> s;
			WildCardMatcher matcher(w, s);
			if(matcher.match(0, 0))
				ret.push_back(s);
		}
		sort(all(ret));
		for(int i = 0; i < ret.size(); ++i)
			cout << ret[i] << endl;

	}
}
