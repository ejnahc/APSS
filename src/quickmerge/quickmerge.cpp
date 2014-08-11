#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// array[lo..hi] 의 첫 원소를 기준으로 삼은 뒤, 이 배열을
// array[lo..mid-1], array[mid+1..hi] 의 두 구간으로 나눈다.
// 왼쪽 구간의 수들은 모두 array[mid] 보다 작거나 같고, 오른쪽 구간의
// 수들은 모두 array[mid] 보다 커야 한다.
int partition(vector<int>& array, int lo, int hi) {
	int pivot = array[lo], mid = lo;
	// 반복문 불변식: array[lo..mid] 의 수들은 기준보다 작거나 같다.
	// array[mid+1..i-1] 의 수들은 기준보다 크다.
	for(int i = lo+1; i <= hi; ++i) 
		if(array[i] <= pivot) 
			swap(array[i], array[++mid]);
	swap(array[lo], array[mid]);
	return mid;
}

// array[lo..hi] 를 정렬한다.
void quickSort(vector<int>& array, int lo, int hi) {
	if(lo >= hi) return;
	int mid = partition(array, lo, hi);
	quickSort(array, lo, mid-1);
	quickSort(array, mid+1, hi);
}

int main() {

	for(int iter = 0; iter < 10000; iter++) {
		int n = rand() % 50 + 10;
		vector<int> a(n);
		for(int i = 0; i < n; i++) a[i] = rand() % 10000;
		vector<int> b = a, c = a;
		sort(b.begin(), b.end());
		quickSort(c, 0, n-1);
		if(b != c) {
			printf("a:"); for(int i = 0; i < n; i++) printf(" %d", a[i]); printf("\n");
			printf("b:"); for(int i = 0; i < n; i++) printf(" %d", b[i]); printf("\n");
			printf("c:"); for(int i = 0; i < n; i++) printf(" %d", c[i]); printf("\n");
			quickSort(c, 0, n-1);
			return 0;
		}
	}
	printf("all good.\n");

}

