#include<cmath>
#include<cstring>
#include<cassert>
#include<algorithm>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int MAX_N = 1000000;

int n;
bool isPrime[MAX_N];

// 가장 단순한 형태의 에라토스테네스의 체의 구현
// 종료한 뒤 isPrime[i] = i 가 소수인가?
void eratosthenes() {
	memset(isPrime, 1, sizeof(isPrime));

	// 1 은 항상 예외 처리!
	isPrime[0] = isPrime[1] = false;

	int sqrtn = int(sqrt(n));
	for(int i = 2; i <= sqrtn; ++i)
		// 이 수가 아직 지워지지 않았다면
		if(isPrime[i])
			// i 의 배수 j 들에 대해 isPrime[j] = false 로 둔다.
			// i*i 미만의 배수는 이미 지워졌으므로 신경쓰지 않는다.
			for(int j = i*i; j <= n; j += i)
				isPrime[j] = false;
}

// minFactor[i] = i 의 가장 작은 소인수 (i 가 소수인 경우 자기 자신)
int minFactor[MAX_N];

// 에라토스테네스의 체를 수행하면서 소인수분해를 위한 정보도 저장한다
void eratosthenes2() {
	// 1 은 항상 예외 처리
	minFactor[0] = minFactor[1] = -1;

	// 모든 숫자를 처음에는 소수로 표시해 둔다
	for(int i = 2; i <= n; ++i)
		minFactor[i] = i;

	// 에라토스테네스의 체를 수행한다
	int sqrtn = int(sqrt(n));
	for(int i = 2; i <= sqrtn; ++i) {
		if(minFactor[i] == i) {
			for(int j = i*i; j <= n; j += i)
				// 아직 약수를 본 적 없는 숫자인 경우 i 를 써 둔다
				if(minFactor[j] == j)
					minFactor[j] = i;
		}
	}
}

// 2 이상의 자연수 n 을 소인수분해한 결과를 반환한다.
vector<int> factor(int n) {
	vector<int> ret;
	// n 이 1 이 될 때까지 가장 작은 소인수로 나누는 것을 반복한다
	while(n > 1) {
		ret.push_back(minFactor[n]);
		n /= minFactor[n];
	}
	return ret;
}

// 주어진 정수 n 을 소인수분해하는 간단한 알고리즘
vector<int> factorSimple(int n) {
	vector<int> ret;
	int sqrtn = int(sqrt(n));
	for(int div = 2; div <= sqrtn; ++div)
		while(n % div == 0) {
			n /= div;
			ret.push_back(div);
		}
	if(n > 1) ret.push_back(n);
	return ret;
}

int main() {
	n = 1000;

	eratosthenes();
	for(int i = 0; i < 100; i++)
		if(isPrime[i])
			printf("%d ", i);
	printf("\n");

	eratosthenes2();
	for(int i = 1; i < n; ++i) {
		vector<int> a = factor(i);
		vector<int> b = factorSimple(i);
		if(a != b) {
			printf("Factoring %d:\n", i);
			printf("sieve:"); for(int j = 0; j < a.size(); j++) printf(" %d", a[j]); printf("\n");
			printf("naive:"); for(int j = 0; j < b.size(); j++) printf(" %d", b[j]); printf("\n");
			return 0;
		}
	}
	printf("all good.\n");
}

