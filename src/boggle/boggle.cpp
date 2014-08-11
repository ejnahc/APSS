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

class Boggle {
	public:
	// 게임판의 정보를 저장한다
	vector<string> board;

	// 5x5 의 보글 게임 판의 해당 위치에서 주어진 단어가 시작하는지를 반환
	bool hasWord(int y, int x, const string& word)
	{
		if(y < 0 || x < 0 || y >= 5 || x >= 5) return false;
		if(board[y][x] != word[0]) return false;
		if(word.size() == 1) return true;
		for(int dx = -1; dx <= 1; ++dx)
			for(int dy = -1; dy <= 1; ++dy)
				if((dx || dy) && hasWord(y+dy, x+dx, word.substr(1)))
					return true;
		return false;
	}
	// CUT HERE
	void run()
	{
		board.push_back("URLPM");
		board.push_back("XPRET");
		board.push_back("GIAET");
		board.push_back("XTNZY");
		board.push_back("HOQRS");
		assert(hasWord(1, 1, "PRETTY"));
		assert(hasWord(2, 0, "GIRL"));
		assert(hasWord(4, 0, "HONEY"));
		assert(!hasWord(1, 1, "PRETTMY"));
		assert(!hasWord(2, 0, "GIRAL"));
	}
};

int main()
{
	Boggle().run();
	printf("all tests passed\n");
}
