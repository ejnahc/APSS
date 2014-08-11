#include<cassert>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

// 분수 a/b 보다 같거나 큰 최소의 자연수를 반환한다
int ceil(int a, int b) {
	return (a + b - 1) / b;
}

// 마법의 약 레시피와 이미 넣은 재료의 양이 주어질 때, 더 넣을 재료의 양을 구한다
vector<int> solve(const vector<int>& recipe, const vector<int>& put) {
	int n = recipe.size();
	// 모든 recipe[] 의 최대공약수를 구한다
	int b = recipe[0];
	for(int i = 1; i < n; i++) b = gcd(b, recipe[i]);
	// 최소한 b/b = 1 배는 만들어야 하므로, a 의 초기값을 b 로 둔다
	int a = b;
	// X 를 직접 구하는 대신 ceil(put[i] * b, recipe[i]) 의 최대값을 구한다
	for(int i = 0; i < n; i++)
		a = max(a, ceil(put[i] * b, recipe[i]));
	// a/b 배 분량을 만들면 된다
	vector<int> ret(n);
	for(int i = 0; i < n; i++)
		ret[i] = recipe[i] * a / b - put[i];
	return ret;
}

// 마법의 약 레시피와 이미 넣은 재료의 양이 주어질 때, 더 넣을 재료의 양을 구한다
vector<int> solveSimulation(const vector<int>& recipe, vector<int> put) {
	vector<int> oa = put;
	int n = recipe.size();
	vector<int> ret(n);
	// 각 재료를 최소한 recipe 에 적힌 만큼은 넣어야 한다
	for(int i = 0; i < n; i++) {
		ret[i] = max(recipe[i] - put[i], 0);
		put[i] += ret[i];
	}
	// 비율이 전부 맞을 때까지 재료를 계속 추가하자
	int iter = 0;
	while(true) {
		++iter;
		// 냄비에 재료를 더 넣지 않아도 될 때까지 반복한다
		bool ok = true;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j) {
				// i 번째 재료에 의하면 모든 재료는 put[i] / recipe[i] = X 배 이상은 넣어야 한다.
				// 따라서 put[j] 는 recipe[j] * X 이상의 정수가 되어야 한다.
				int required = (put[i] * recipe[j] + recipe[i] - 1) / recipe[i];
				// 더 넣어야 하는가?
				if(required > put[j]) {
					ret[j] += required - put[j];
					put[j] = required;
					ok = false;
				}
			}
		if(ok) break;
	}
	fprintf(stderr, "%d iterations.\n", iter);
	if(iter == 228) {
		for(int i = 0; i < n; i++) fprintf(stderr, "%d ", recipe[i]); fprintf(stderr, "\n");
		for(int i = 0; i < n; i++) fprintf(stderr, "%d ", oa[i]); fprintf(stderr, "\n");
	}
	return ret;
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	int n;
    	cin >> n;
    	vector<int> recipe(n);
    	vector<int> put(n);
    	for(int i = 0; i < n; i++) cin >> recipe[i];
    	for(int i = 0; i < n; i++) cin >> put[i];

    	vector<int> ret = solve(recipe, put);
    	vector<int> ret2 = solveSimulation(recipe, put);
    	assert(ret == ret2);
    	for(int i = 0; i < n; i++)
    		printf("%s%d", (i ? " " : ""), ret[i]);
    	printf("\n");
    }
}

