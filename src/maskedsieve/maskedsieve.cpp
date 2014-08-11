#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int MAX_N = 256*1024*1024;
int n;
unsigned char sieve[(MAX_N + 7) / 8];

inline bool isPrime(int k) {
	return sieve[k >> 3] & (1 << (k & 7));
}

inline void setComposite(int k) {
	sieve[k >> 3] &= ~(1 << (k & 7));
}

// 비트마스크를 사용하는 에라토스테네스의 체의 구현
// 이 함수를 수행하고 난 뒤, isPrime() 을 이용해 각 수가 소수인지 알 수 있다.
void eratosthenes() {
	memset(sieve, 255, sizeof(sieve));

	setComposite(0);
	setComposite(1);

	int sqrtn = int(sqrt(n));
	for(int i = 2; i <= sqrtn; ++i)
		// 이 수가 아직 지워지지 않았다면
		if(isPrime(i))
			// i 의 배수 j 들에 대해 isPrime[j] = false 로 둔다.
			// i*i 미만의 배수는 이미 지워졌으므로 신경쓰지 않는다.
			for(int j = i*i; j <= n; j += i)
				setComposite(j);
}

int main() {
	n = MAX_N;
	eratosthenes();
	for(int i = 0; i < 100; i++)
		if(isPrime(i))
			printf("%d ", i);
	printf("\n");
}

