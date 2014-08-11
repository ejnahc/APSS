#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

void mySort(vector<int>& array) {
	sort(array.begin(), array.end());
}

string toString(const vector<int>& array) {
	return "";
}


int main() {
	while(true) {
		// 임의의 입력을 만든다
		int n = rand() % 100 + 1;
		vector<int> input(n);
		for(int i = 0; i < n; ++i)
			input[i] = rand();

		// 두 개의 복제를 만들어서 하나는 우리의 정렬 함수로, 하나는 표준 라이브러리로 정렬한다
		vector<int> mySorted = input;
		mySort(mySorted);

		vector<int> reference = input;
		sort(reference.begin(), reference.end());

		// 만약 다르면 오류를 내고 종료한다
		if(mySorted != reference) {
			cout << "Mismatch!" << endl;
			cout << "Input: " << toString(input) << endl;
			cout << "Expected: " << toString(reference) << endl;
			cout << "Got: " << toString(mySorted) << endl;
			break;
		}

	}
}

