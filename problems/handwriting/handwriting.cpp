#include<cassert>
#include<cmath>
#include<iostream>
#include<string>
#include<vector>
#include<cstdio>
using namespace std;

string corpus[1001];

int n, m;

// 분류기가 반환한 문장
int R[100];
// T[i][j] = i단어 이후에 j단어가 나올 확률
double T[1001][1001];
// M[i][j] = i단어가 j단어로 분류될 확률
double M[1001][1001];

int choice[102][1002];
double cache[102][1002];

// Q[segment] 이후를 채워서 얻을 수 있는 최대 확률값
// Q[segment-1] == previousMatch 라고 가정한다
double recognize(int segment, int previousMatch) {
	if(segment == n) return 0;
	double& ret = cache[segment][previousMatch];
	if(ret < 0.5) return ret;
	ret = -1e200;
	int& choose = choice[segment][previousMatch];

	// R[segment] 에 대응되는 단어를 찾는다
	for(int thisMatch = 0; thisMatch < m; ++thisMatch) {
		// g(thisMatch) = T(previousMatch, thisMatch) *
		//                M(thisMatch, R[segment])
		double cand = T[previousMatch][thisMatch]
			+ M[thisMatch][R[segment]]
			+ recognize(segment+1, thisMatch);
    if(ret < cand) {
			ret = cand;
			choose = thisMatch;
		}
	}
	return ret;
}

string reconstruct(int segment, int previousMatch) {
	if(segment == n) return "";
	int choose = choice[segment][previousMatch];
  double sol = recognize(segment, previousMatch);
  for(int next = 0; next < m; ++next) {
    if(next != choose) {
      double cand = T[previousMatch][next] + M[next][R[segment]] + recognize(segment+1, next);
      if(fabs(cand - sol) < 1e-6)
        assert(false);
    }
  }
	return corpus[choose] + " " + reconstruct(segment+1, choose);
}

int main() {
	int queries;
	cin >> m >> queries;
	assert(m <= 1000);
	assert(queries <= 100);
	for(int i = 0; i < m; i++) {
		cin >> corpus[i];
	}
	corpus[m] = "";
	for(int i = 0; i < m; i++) {
		cin >> T[m][i];
		T[m][i] = log(T[m][i]);
	}
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < m; j++) {
			cin >> T[i][j];
			T[i][j] = log(T[i][j]);
		}
	}
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < m; j++) {
			cin >> M[i][j];
			M[i][j] = log(M[i][j]);
		}
	}
	while(queries--) {
		cin >> n;
		assert(1 <= n && n <= 100);
		for(int i = 0; i < n; i++) {
			string recognizedWord;
			cin >> recognizedWord;
			for(int j = 0; j < m; ++j)
				if(corpus[j] == recognizedWord) {
					R[i] = j;
					break;
				}
		}

		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m+1; j++) {
				cache[i][j] = 1;
			}
		}

		recognize(0, m);
		string original = reconstruct(0, m);
		printf("%s\n", original.substr(0, original.size()-1).c_str());
	}
}

