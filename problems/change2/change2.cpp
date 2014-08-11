#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 사용 가능한 동전 종류
const int coins[] = { 10, 50, 100, 500 };

// 선택한 동전의 목록을 출력한다
void printChosen(const vector<int>& coins); 

// amount 원을 반환하는 방법을 재귀적으로 모두 찾아 출력한다
// chosen 은 이미 반환한 동전들을 담는다
void changeIncorrect(int amount, vector<int>& chosen) {
  // 기저 사례: 돌려줄 돈이 없다면 출력하고 끝낸다
  if(amount == 0) { printChosen(chosen); return; }
  // 다음에 돌려줄 동전을 선택한다
  for(int i = 0; i < 4; ++i)
    if(amount >= coins[i]) {
      chosen.push_back( coins[i] );
      changeIncorrect(amount - coins[i], chosen);
      chosen.pop_back();
    }
}

// 남아 있는 amount 원을 반환하는 방법을 모두 출력한다
void printChangeIncorrect(int amount) {
  // 이미 선택한 동전들을 담는 벡터
  vector<int> chosen;
  changeIncorrect(amount, chosen);
}


// amount 원을 반환하는 방법을 재귀적으로 모두 찾아 출력한다
// chosen 은 이미 반환한 동전들을 담는다
void changeCorrect(int amount, vector<int>& chosen) {
  // 기저 사례: 더 돌려줄 돈이 없다면 출력하고 끝낸다
  if(amount == 0) { printChosen(chosen); return; }
  // 다음에 돌려줄 동전을 선택한다
  for(int i = 0; i < 4; ++i)
	// 새 동전이 마지막에 선택했던 동전보다 액수가 작아서는 안된다
	if(amount >= coins[i] && (chosen.empty() || chosen.back() <= coins[i])) {
	  chosen.push_back( coins[i] );
	  changeCorrect(amount - coins[i], chosen);
	  chosen.pop_back();
    }
}

// 남아 있는 amount 원을 반환하는 방법을 모두 출력한다
void printChangeCorrect(int amount) {
  // 이미 선택한 동전들을 담는 벡터
  vector<int> chosen;
  changeCorrect(amount, chosen);
}

void printChosen(const vector<int>& coins) {
	for(int i = 0; i < coins.size(); i++) 
		printf("%s%d", (i ? " " : ""), coins[i]);
	printf("\n");
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
		int n;
		cin >> n;
		printChangeIncorrect(n);
		printf("===\n");
		printChangeCorrect(n);
		printf("===\n");

    }
}

