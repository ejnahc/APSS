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

// 주어진 배열 A 에서 가장 많이 등장하는 숫자를 반환한다.
// 만약 두 가지 이상 있을 경우 아무 것이나 반환한다.
int majority1(const vector<int>& A) {
    int N = A.size();
    int majority = -1, majorityCount = 0;
    for(int i = 0; i < N; ++i) {
        // A 에 등장하는 A[i] 의 수를 센다
        int V = A[i], count = 0;
        for(int j = 0; j < N; ++j) {
            if(A[j] == V) {
                ++count;
            }
        }
        if(count > majorityCount) {
            majorityCount = count;
            majority = V;
        }
    }
    return majority;
}

// A 가 0 부터 100 사이의 값일 경우 가장 많이 등장하는 숫자를 반환한다.
int majority2(const vector<int>& A) {
    int N = A.size();
    vector<int> count(101, 0);

    for(int i = 0; i < N; ++i) {
        count[A[i]]++;
    }

    int majority = 0;
    for(int i = 1; i <= 100; ++i) {
        if(count[i] > count[majority]) {
            majority = i;
        }
    }
    return majority;
}

int main()
{
    for(int iter = 0; iter < 100000; ++iter)
    {
        vector<int> A;
        for(int i = 0; i < 100; ++i) A.push_back(rand() % 101);
        //for(int i = 0; i < 100; ++i) printf("%d ", A[i]); printf("\n");
        int m1 = majority1(A), m2 = majority2(A);
        //printf("%d %d\n", m1, m2);
        assert(count(A.begin(), A.end(), m1) == count(A.begin(), A.end(), m2));
    }
}


