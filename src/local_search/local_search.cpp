#include<iostream>
#include<cstring>
#include<algorithm>
#include<sstream>
#include<string>
#include<vector>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<cassert>
#include<numeric>
#include<set>
#include<map>
#include<queue>
#include<list>
#include<deque>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define REP(i,n) FOR(i,0,n)
#define FORE(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define CLEAR(x,with) memset(x,with,sizeof(x))
#define sz size()
typedef long long ll;

// d 에 있는 수 전체를 x 로 표현했을 때의 오차
double evaluate(double x, const vector<double>& d)
{
	double ret = 0;
	REP(i,d.sz) ret += (x-d[i])*(x-d[i]);
	return ret;
}

// d 에 있는 수 전체를 표현할 숫자를 반환
double quantize(const vector<double>& d)
{
	double guess = d[0];
	double delta = *max_element(d.begin(), d.end()) - *min_element(d.begin(), d.end());
	double currentError = evaluate(guess, d);
	delta /= 10;	
	while(delta > 1e-8)
	{
//		printf("delta = %.8lf\n", delta);
		while(true) {
			double errorA = evaluate(guess + delta, d);
			double errorB = evaluate(guess - delta, d);
//			printf("guess = %.8lf, errorA %.8lf, errorB %.8lf, current %.8lf\n", guess, errorA, errorB, currentError);
			if(errorA < currentError)
			{
				currentError = errorA;
				guess += delta;
			}
			else if(errorB < currentError)
			{
				currentError = errorB;
				guess -= delta;
			}
			else 
				break;
		}
		delta *= 0.1;
	}
	return guess;
}

int main()
{
	vector<double> d;
	int n;
	cin >> n;
	d.resize(n);
	REP(i,n) cin >> d[i];
	cout << quantize(d) << endl;
}
