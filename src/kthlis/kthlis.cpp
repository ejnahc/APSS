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

const int M = 0x7fffffff;

struct KthLIS {
    // A: LIS 를 찾을 수열
    // L: getMaxLength() 의 반환값을 저장하는 캐시
    // C: countLIS() 의 반환값을 저장하는 캐시
    vector<int> A, L, C;

    KthLIS(const vector<int>& a) {
        A = a;
        L.assign(A.size(), -1);
        C.assign(A.size(), -1);
    }

    // A[i] 에서 시작하는 LIS 의 길이를 반환한다
    int getMaxLength(int i) {
        int& ret = L[i]; if(ret != -1) return ret;
        ret = 1;
        for(int j = i+1; j < A.size(); ++j)
            if(A[i] < A[j])
                ret = max(ret, getMaxLength(j) + 1);
        return ret;
    }

    // A[i] 에서 시작하는 LIS 의 개수를 반환한다
    int countLIS(int i) {
        int& ret = C[i]; if(ret != -1) return ret;
        if(getMaxLength(i) == 1)
            return ret = 1;
        long long cnt = 0;
        for(int j = i+1; j < A.size(); ++j)
            if(A[i] < A[j] && getMaxLength(i) == getMaxLength(j) + 1)
                cnt = min<long long>(M, cnt + countLIS(j));
        return ret = cnt;
    }

    // A[i] 에서 시작하는 K번째 LIS 를 반환한다
    void printKthLIS(int i, int k) {
        if(i > 0) cout << A[i] << " ";
        // 뒤에 올 수 있는 숫자들과 위치들의 목록을 만든다
		// (숫자, 숫자의 위치) 의 쌍이 된다
        vector<pair<int, int> > followers;
        for(int j = i+1; j < A.size(); ++j)
            if(A[i] < A[j] && getMaxLength(i) == getMaxLength(j) + 1)
                followers.push_back(make_pair(A[j], j));
        sort(followers.begin(), followers.end());
        for(int j = 0; j < followers.size(); ++j) {
            int loc = followers[j].second;
            if(countLIS(loc) <= k)
                k -= countLIS(loc);
            else {           
                printKthLIS(loc, k);
                break;
            }
        }
    }
};

int main()
{
        int cases;
        cin >> cases;
        REP(cc,cases)
        {
            int n, k;
            cin >> n >> k;
            vector<int> t(n+1);
            t[0] = 0;
            for(int i = 0; i < n; ++i)
                cin >> t[i+1];
            KthLIS kl(t);
            cout << kl.getMaxLength(0) - 1 << endl;
            kl.printKthLIS(0, k-1);
            cout << endl;

        }
}

