#include<cstdio>
#include<cassert>
#include<cstring>
#include<map>
#include<set>
#include<time.h>
#include<algorithm>
#include<stack>
#include<queue>
#include<utility>
#include<cmath>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// amount원을 연 이율 rates퍼센트로 duration월간 한달에 monthlyPayment 로 
// 남았을 때 대출 잔금은?
double balance(double amount, int duration, double rates, double monthlyPayment) {
	double balance = amount;
	for(int i = 0; i < duration; ++i) {
		// 이자가 붙는다
		balance *= (1.0 + (rates / 12.0) / 100.0);
		// 상환액을 잔금에서 제한다
		balance -= monthlyPayment;
	}
	return balance;
}

// amount원을 연 이율 rates퍼센트로 duration월간 갚으려면 한달에
// 얼마씩 갚아야 하나?
double payment(double amount, int duration, double rates) {
	// 불변 조건: 
	// 1. lo원씩 갚으면 duration개월 안에 갚을 수 없다
	// 2. hi원씩 갚으면 duration개월 안에 갚을 수 있다
	double lo = 0, hi = amount * (1.0 + (rates / 12.0) / 100.0);
	for(int iter = 0; iter < 100; ++iter) {
		double mid = (lo + hi) / 2.0;
		if(balance(amount, duration, rates, mid) <= 0)
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	double N, P;
    	int M;
    	cin >> N >> M >> P;
    	cout << payment(N, M, P) << endl;
    }
}

