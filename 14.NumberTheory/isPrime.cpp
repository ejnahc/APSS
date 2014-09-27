// 주어진 자연수 n이 소수인지 판별한다. O(sqrt(n))
bool isPrime(int n) {
	// 예외 처리
	if (n <= 1) return false;
	else if (n == 2) return true;

	// 2를 제외한 모든 짝수는 소수가 아님
	if (n % 2 == 0) return false;

	// 2를 제외했으니 3 이상의 모든 홀수로 나누어 보자
	int sqrtn = int(sqrt(n));
	for (int div=3; div<=sqrtn; div+=2) {
		if (n % div == 0)
			return false;
	}

	return true;
}


// 에라토스테네스의 체
int n;
bool isPrime[MAX_N+1];

void eratosthenes() {
	memset(isPrime, 1, sizeof(isPrime));

	isPrime[0] = isPrime[1] = false;
	int sqrtn = int(sqrt(n));

	for (int i=2; i<=sqrtn; ++i) {
		if (isPrime[i]) {
			for (int j=i*i; j<=n; j+=i)
				isPrime[j] = false;
		}
	}
}