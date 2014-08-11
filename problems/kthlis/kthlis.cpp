#include<algorithm>
#include<cstring>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int MAX = 2000000000+10;
int n;
int cacheLen[501], cacheCnt[501], S[500];

// S[start] 에서 시작하는 증가 부분 수열 중 최대 길이를 반환한다
int lis(int start) {
	// 메모이제이션
	int& ret = cacheLen[start+1];
	if(ret != -1) return ret;
	// 항상 S[start] 는 있기 때문에 길이는 최하 1
	ret = 1;
	for(int next = start+1; next < n; ++next)
		if(start == -1 || S[start] < S[next])
			ret = max(ret, lis(next) + 1);
	return ret;
}

// S[start] 에서 시작하는 최대 증가 부분 수열의 수를 반환한다
int count(int start) {
	// 기저 사례: LIS 의 길이가 1 인 경우
	if(lis(start) == 1) return 1;
	// 메모이제이션
	int& ret = cacheCnt[start+1];
	if(ret != -1) return ret;
	ret = 0;
	for(int next = start+1; next < n; ++next) {
		if((start == -1 || S[start] < S[next]) &&
			lis(start) == lis(next) + 1)
			ret = min<long long>(MAX, (long long)ret + count(next));
	}
	return ret;
}

// S[start] 에서 시작하는 LIS 중 사전 순으로 skip 개 건너뛴 수열을
// lis 에 저장한다
void reconstruct(int start, int skip, vector<int>& lis) {
	// S[start] 는 항상 LIS 에 포함된다
	if(start != -1) lis.push_back(S[start]);
	// 뒤에 올 수 있는 숫자들과 위치의 목록을 만든다
	// (숫자, 숫자의 위치) 의 목록이 된다
	vector<pair<int,int> > followers;
	for(int next = start; next < n; next++)
		if((start == -1 || S[start] < S[next]) &&
			lis(start) == lis(next) + 1)
			followers.push_back(make_pair(S[next], next));
	// 숫자 크기별로 정렬한다
	sort(followers.begin(), followers.end());
	for(int i = 0; i < followers.size(); ++i) {
		// 이 숫자를 뒤에 이어서 만들 수 있는 LIS 의 개수를 본다
		int idx = followers[i].second;
		int cnt = count(idx);
		if(cnt <= skip)
			skip -= cnt;
		else {
			// 다음 숫자는 S[idx] 임을 알았다
			reconstruct(idx, skip, lis);
			break;
		}
	}
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	int k;
    	cin >> n >> k;
    	for(int i = 0; i < n; i++) {
    		cin >> S[i];
    	}
    	memset(cacheLen, -1, sizeof(cacheLen));
    	memset(cacheCnt, -1, sizeof(cacheCnt));
    	//cout << lis(-1)-1 << endl;
    	//cout << count(-1) << endl;
    	vector<int> kth;
    	reconstruct(-1, k-1, kth);
    	cout << kth.size() << endl;
    	for(int i = 0; i < kth.size(); i++) {
    		if(i) cout << ' ';
    		cout << kth[i];
    	}
    	cout << endl;
    }
}

