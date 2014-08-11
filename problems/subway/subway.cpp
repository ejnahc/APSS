#include<iostream>
#include<string>
#include<vector>
using namespace std;

int n, m;
vector<int> s, v;

long long getBudget(long long speed) {
	long long ret = 0;
	for(int i = 0; i < n; i++)
		if(speed > s[i])
			ret += (speed - s[i] + v[i] - 1) / v[i];
	return ret;
}

long long solve() {
	long long lo = 0, hi = 100001000001LL;
	while(lo + 1 < hi) {
		long long mid = (lo + hi) / 2;
		long long requiredBudget = getBudget(mid);
		if(requiredBudget <= m)
			lo = mid;
		else
			hi = mid;
	}
	return lo;
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	cin >> n >> m;
    	s.resize(n); v.resize(n);
    	for(int i = 0; i < n; i++) cin >> s[i];
    	for(int i = 0; i < n; i++) cin >> v[i];
    	cout << solve() << endl;
    }
}

