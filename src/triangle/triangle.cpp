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

class Triangle {
public:
    // 삼각형의 크기
    int n;
    // 삼각형의 각 위치에 있는 숫자
    int number[100][100];
    // cache[y][x] = getMaxPath(y,x) 의 계산 결과. 초기값은 -1 
    int cache[100][100];
    // paths[y][x] = countPaths(y,x) 의 계산 결과. 초기값은 -1
    int paths[100][100];

    // (y,x) 에서 시작해서 맨 아래줄까지 내려가는 경로 중 최대 경로의
    // 숫자 합을 반환한다
    int getMaxPath(int y, int x) {
        // 기저 사례: 맨 아래줄이라면 곧장 반환
        if(y == n-1) return number[y][x];
        int& ret = cache[y][x];
        // 답이 저장되어 있다면 곧장 반환
        if(ret != -1) return ret;
        // 계산 후 반환
        return ret = max(getMaxPath(y+1, x), getMaxPath(y+1, x+1)) + number[y][x];
    }

    // (y,x) 에서 시작해서 맨 아래줄까지 내려가는 경로 중 최대 경로의
    // 개수를 반환한다
    int countPaths(int y, int x) 
    {
        // 기저 사례: 현재 위치가 맨 아래줄이라면 경로가 하나밖에 없다
        if(y == n-1) return 1;
        int& ret = paths[y][x]; if(ret != -1) return ret;
        ret = 0;
        if(number[y][x] + getMaxPath(y+1, x+1) == getMaxPath(y, x))
            ret += countPaths(y+1, x+1);
        if(number[y][x] + getMaxPath(y+1, x) == getMaxPath(y, x))
            ret += countPaths(y+1, x);
        return ret;
    }

    Triangle() {
        CLEAR(paths,-1);
        CLEAR(cache,-1);
    }
};

int main()
{
    Triangle t;
    cin >> t.n;
    for(int i = 0; i < t.n; ++i)
        for(int j = 0; j <= i; ++j)
            cin >> t.number[i][j];
    for(int i = 0; i < t.n; ++i)
    {
        for(int j = 0; j <= i; ++j)
            cout << t.getMaxPath(i, j) << " ";
        cout << endl;
    }
    cout << t.countPaths(0, 0) << endl;
}
