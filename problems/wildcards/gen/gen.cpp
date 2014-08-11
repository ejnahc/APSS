#include<cstring>
#include<iostream>
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

const int cases = 10;
const char *alphanum = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const int alphanum_len = strlen(alphanum);

const int N[10] = { 4000, 4000, 4000, 4000, 4000,
	4000, 4000, 4000, 4000, 4000 };
//const int N[10] = { 10, 20, 50, 50, 50, 50, 50, 50, 50, 100 };

string generate(const string& w, bool glitch)
{
	// let (1-prob)^w.size() == 0.20
	double prob = pow(0.20, 1.0 / w.size());
	string ret;
	int idx = 0;
	while(idx < w.size() && ret.size() < 5000)
	{
		if(w[idx] == '?')
			ret += alphanum[rand() % alphanum_len];
		else if(w[idx] == '*')
		{
			int len = rand() % 4;
			for(int i = 0; i < len; ++i)
				ret += alphanum[rand() % alphanum_len];
		}
		else
			ret += w[idx];
		++idx;
		if(rand() % 10000 > prob * 10000)
			ret += alphanum[rand() % alphanum_len];
	}
	if(ret.size() > 5000) ret = ret.substr(0, 5000);
	return ret;
}

int main()
{
	srand(1947);
	cout << cases << endl;
	REP(cc,cases)
	{
		int n = N[cc];
		string wildcard;
		for(int i = 0; i < n; ++i)
		{
			int t = rand() % 10;
			if(t == 0)
				wildcard += "*";
			else if(t < 3)
				wildcard += "?";
			else
				wildcard += alphanum[rand() % alphanum_len];
		}
		int strings = rand() % 40 + 10;
		cout << wildcard << endl << strings << endl;
		while(strings--)
		{
			bool glitch = false;
			if(rand() % 3 == 0) glitch = true;
			cout << generate(wildcard, glitch) << endl;
		}
	}
}
