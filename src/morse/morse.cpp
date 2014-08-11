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
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long ll;

// K 의 최대값 +100. 오버플로우를 막기 위해 이보다 큰 값은 구하지 않는다
const int M = 1000000000+100;
struct MorseDict {
    int bino[201][201];
    MorseDict() {
        // 생성자에서 미리 이항계수를 계산한다
        memset(bino, 0, sizeof(bino));
        for(int i = 0; i <= 200; ++i) {
            bino[i][0] = bino[i][i] = 1;
            for(int j = 1; j < i; ++j)
                bino[i][j] = min(M, bino[i-1][j-1] + bino[i-1][j]);
        }
    }

    // n개의 -, m개의 o 로 구성된 신호 중 k번째 신호를 반환한다 
    // (k 는 0 부터 시작)
    string getKthSignal(int n, int m, int k) {
        if(n == 0 && m == 0) return "";
        // - 로 시작하는 신호의 수
        int dashes = bino[n+m-1][n-1];
        if(n > 0 && k < dashes)
            return "-" + getKthSignal(n-1, m, k);
        return "o" + getKthSignal(n, m-1, k - dashes);
    }
};

int main()
{
    MorseDict dict;
    for(int i = 0; i < 10; ++i)
        cout << dict.getKthSignal(2, 3, i) << endl;
}
