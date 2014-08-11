#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 주어진 정수 n 을 소인수분해한다.
vector<int> factor(int n) {
	vector<int> ret;
	for(int div = 2; div * div <= n; ++div)
		while(n % div == 0) {
			n /= div;
			ret.push_back(div);
		}
	if(n > 1) ret.push_back(n);
	return ret;
}

int main() {
	int cases;
	cin >> cases;
	for(int cc = 0; cc < cases; ++cc) {
		int n;
		cin >> n;
		vector<int> ret = factor(n);
		for(int i = 0; i < ret.size(); i++) {
			printf("%d ", ret[i]);
		}
		printf("\n");

	}
}

