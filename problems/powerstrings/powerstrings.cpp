#include<iostream>
#include<string>
#include<vector>
using namespace std;
vector<int> getPrefixOverlaps(const string& needle) {
	int n = needle.size();
	// overlap[i] = needle 의 첫 i 글자가 자기 자신과 얼마나 겹치나?
	vector<int> overlap(n+1, -1);
	overlap[0] = overlap[1] = 0;
	for(int i = 2; i <= n; ++i) {
		int candidate = overlap[i-1] + 1;
		while(candidate > 1 && needle[i-1] != needle[candidate-1])
			candidate = overlap[candidate-1] + 1;
		if(candidate == 1 && needle[0] != needle[i-1])
			candidate = 0;
		overlap[i] = candidate;
	}
	return overlap;
}

int main() {
    string s;
    while(cin >> s) {
    	if(s[0] == '.') break;
    	vector<int> overlap = getPrefixOverlaps(s);
    	int sz = s.size() - overlap[s.size()];
    	cout << s.size() / sz << endl;
    }
}

