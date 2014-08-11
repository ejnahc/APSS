#include<cmath>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>

using namespace std;

// 주어진 자연수 n 이 소수인지 확인한다
bool isPrime(int n) {
	// 예외 처리: 1 과 2 는 예외로 처리한다
	if(n == 1) return false;
	if(n == 2) return true;
	// 2 를 제외한 모든 짝수는 소수가 아니다
	if(n % 2 == 0) return false;
	// 2 를 제외했으니 3 이상의 모든 홀수로 나누어보자
	int sqrtn = int(sqrt(n));
	for(int div = 3; div <= sqrtn; div += 2)
		if(n % div == 0)
			return false;
	return true;
}

int main() {
	cout << isPrime(2147483647) << endl;
	cout << isPrime(2147483647) << endl;
	for(int i = 1; i < 100; i++)
		if(isPrime(i))
			printf("%d ", i);
	printf("\n");
}

