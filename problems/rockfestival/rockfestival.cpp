#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	int n, l;
    	cin >> n >> l;
    	vector<int> cost(n);
    	for(int i = 0; i < n; i++) cin >> cost[i];
    	double ret = 1e20;
    	for(int i = 0; i + l <= n; ++i) {
    		int sum = 0;
    		for(int j = i; j < n; j++) {
    			sum += cost[j];
    			if(j - i + 1 >= l)
    				ret = min(ret, sum / double(j - i + 1));
			}
    	}
    	printf("%.10lf\n", ret);
    }
}

