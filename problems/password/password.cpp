#include<map>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int TM = 1000*1000*10;

// minFactor[i] = i 의 가장 작은 소인수 (i 가 소수인 경우 자기 자신)
int minFactor[TM+1];

// 에라토스테네스의 체를 수행하면서 소인수분해를 위한 정보도 저장한다
void eratosthenes2() {
	// 1 은 항상 예외 처리
	minFactor[0] = minFactor[1] = -1;

	// 모든 숫자를 처음에는 소수로 표시해 둔다
	for(int i = 2; i <= TM; ++i)
		minFactor[i] = i;

	// 에라토스테네스의 체를 수행한다
	for(int i = 2; i*i <= TM; ++i) {
		if(minFactor[i] == i) {
			minFactor[i] = i;
			for(int j = i*i; j <= TM; j += i)
				// 아직 약수를 본 적 없는 숫자인 경우 i 를 써 둔다
				if(minFactor[j] == j)
					minFactor[j] = i;
		}
	}
}

// minFactorPower[i] = i 의 소인수분해에는 minFactor[i] 의 몇 승이 포함되어 있는가?
int minFactorPower[TM+1];

// factors[i] = i 가 가진 약수의 수
int factors[TM+1];

void getFactorsSmart() {
	factors[1] = 1;
	for(int n = 2; n <= TM; ++n) {
		// 소수인 경우 약수가 두개밖에 없다
		if(minFactor[n] == n) {
			minFactorPower[n] = 1;
			factors[n] = 2;
		}
		// 소수가 아닌 경우, 가장 작은 소인수로 나눈 수 (m) 의
		// 약수의 수를 응용해 n 의 약수의 수를 찾는다
		else {
			int p = minFactor[n];
			int m = n / p;
			// m 이 p 로 더이상 나누어지지 않는 경우
			if(p != minFactor[m]) 
				minFactorPower[n] = 1;
			else
				minFactorPower[n] = minFactorPower[m] + 1;
			int a = minFactorPower[n];
			factors[n] = (factors[m] / a) * (a + 1);
		}
	}
}

void getFactorsBrute() {
	memset(factors, 0, sizeof(factors));
	for(int div = 1; div <= TM; ++div)
		for(int multiple = div; multiple <= TM; multiple += div)
			factors[multiple] += 1;
}

int main(int argc, char* argv[]) {
	if(argc > 1 && argv[1][0] == 'n')
		getFactorsBrute();
	else {
		eratosthenes2();
		getFactorsSmart();
	}
	//for(int i = 2; i <= 20; ++i) printf("factors[%d] = %d\n", i, factors[i]);
	int cases;
	cin >> cases;
	for(int i = 0; i < cases; i++) {
		int n, lo, hi, ret = 0;
		cin >> n >> lo >> hi;
		for(int j = lo; j < hi+1; j++)
			if(factors[j] == n)
				++ret;
		cout << ret << endl;
	}

}

