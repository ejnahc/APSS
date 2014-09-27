// 주어진 정수 n을 소인수분해한다
vector<int> factorSimple(int n) {
	vector<int> ret;
	int sqrtn = int(sqrt(n));

	for (int div=2; div<=sqrtn; ++div) {
		while (n % div == 0) {
			n /= div;
			ret.push_back(div);
		}
	}

	if (n > 1) ret.push_back(n);
	return ret;
}


// Ten Million
const int TM = 1000 * 1000 * 10;
// minFactor[i] = i의 가장 작은 소인수 (i가 소인수인경우 자기 자신)
int minFactor[TM+1];
// minFactorPower[i] = i의 소인수 분해에는 minFactor[i]의 몇 승이 포함되어 있는가
int minFactorPower[TM+1];
// factors[i] = i가 가진 약수의 수
int factors[TM+1];

void getFactorsSmart() {
	factors[1] = 1;

	// minFactor 채우기
    minFactor[0] = minFactor[1] = -1;
    for (int i=2; i<=TM; i++)
        minFactor[i] = i;

    int sqrtn = int(sqrt(TM));
    for (int i=2; i<=sqrtn; ++i) {
        if (minFactor[i] == i) {
            for (int j=i*i; j<=TM; j+=i) {
                if (minFactor[j] == j)
                    minFactor[j] = i;
            }
        }
    }

    for (int n=2; n<=TM; ++n) {
    	// 소수인 경우 약수가 2개밖에 없다
    	if (minFactor[n] == n) {
    		minFactorPower[n] = 1;
    		factors[n] = 2;
    	}

    	// 소수가 아닌 경우, 가장 작은 소인수로 나눈 수(m)의
    	// 약수의 수를 응용해 n의 약수의 수를 찾는다
    	else {
    		int p = minFactor[n];
    		int m = n / p;

    		// m이 p로 더이상 나누어지지 않는 경우
    		if (p != minFactor[m])
    			minFactorPower[n] = 1;
    		else
    			minFactorPower[n] = minFactorPower[m] + 1;

    		int a = minFactorPower[n];
    		factors[n] = (factors[m] / a) * (a + 1);
    	}
    }
}