#include<cstdio>
#include<string>
#include<cassert>
#include<iostream>
using namespace std;
// 분수 a/b 의 소수 표현을 출력한다
void printDecimal(int a, int b) {
	int iter = 0;
	while(a > 0) {
		if(iter++ == 1) cout << '.';
		cout << a / b;
		a = (a % b) * 10;
	}
}
int main() {
	printDecimal(52, 8);
	cout << " ?= 6.5" << endl;
	printDecimal(521, 8);
	cout << " ?= 65.125" << endl;
	printDecimal(1, 8);
	cout <<" ?= 0.125" << endl;
	printDecimal(2, 4);
	cout <<" ?= 0.5" << endl;
	printDecimal(23, 400);
	cout <<" ?= 0.0575" << endl;
	printDecimal(4712, 400);
	cout <<" ?= 11.78" << endl;
	printDecimal(54, 6);
	cout <<" ?= 9" << endl;
}
