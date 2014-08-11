#include<cassert>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const double pi = 2.0 * acos(0);

int n;
double y[100], x[100], r[100];
pair<double,double> ranges[100];

void convertToRange() {
	for(int i = 0; i < n; i++) {
		double loc = fmod(2*pi + atan2(y[i], x[i]), 2*pi);
		double range = 2.0 * asin(r[i] / 2.0 / 8.0);
		ranges[i] = make_pair(loc - range, loc + range);
	}
}

void sortRanges() {
}

// [begin,end] 구간을 덮기 위해 선택할 최소한의 구간 수를 반환한다
// ranges 는 시작 위치의 오름차순으로 정렬되어 있다고 가정하자.
int solveLinear(double begin, double end) {

	int used = 0, idx = 0;
	// 덮지 못한 선분이 남아 있는 동안 계속한다
	while(begin < end) {
		// begin 보다 이전에 시작하는 구간 중 가장 늦게 끝나는 구간을 찾는다
		double maxCover = -1;
		while(idx < n && ranges[idx].first <= begin) {
			maxCover = max(maxCover, ranges[idx].second);
			++idx;
		}
		// 덮을 구간을 찾지 못했으면 큰 값을 반환한다
		if(maxCover <= begin)
			return 987654321;
		// 선분의 덮인 부분을 잘라낸다
		begin = maxCover;
		++used;
	}
	return used;
}


// 0 을 덮을 구간을 선택하고 나머지를 선형으로 푼다.
int solveCircular() {
	int ret = 987654321;

	// 각 구간을 시작 위치의 오름차순으로 정렬한다
	sort(ranges, ranges+n);

	// 0 을 덮을 구간을 선택하자.
	for(int i = 0; i < n; ++i)
		if(ranges[i].first <= 0 || ranges[i].second >= 2*pi) {
			// 이 구간이 덮는 부분을 빼고 남는 중심각의 범위는 다음과 같다
			double begin = fmod(ranges[i].second, 2*pi);
			double end = fmod(ranges[i].first + 2*pi, 2*pi);

			// [begin, end] 선분을 주어진 구간을 사용해서 덮는다.
			ret = min(ret, 1 + solveLinear(begin, end));
		}
	return ret;
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	cin >> n;
    	assert(1 <= n && n <= 100);
    	for(int i = 0; i < n; i++) {
    		cin >> y[i] >> x[i] >> r[i];
    		assert(fabs(8.0 - hypot(y[i], x[i]) ) < 1e-8);
    		assert(0 <= r[i] && r[i] <= 16.0);
    	}
    	convertToRange();
    	int ret = solveCircular();
    	if(ret == 987654321)
    		cout << "IMPOSSIBLE" << endl;
		else
	    	cout << ret << endl;
    }
}

