#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct MemorizingPI {
    // 외울 숫자
    string N;
    
    // N[a] ~ N[b] 까지의 숫자 조각의 난이도를 반환한다
    int classify(int a, int b) {
        // 숫자 조각을 가져온다
        string M = N.substr(a, b-a+1);
        
        // 첫 글자만으로 이루어진 문자열과 같으면 난이도는 1
        if(M == string(M.size(), M[0])) return 1;
        
        // 등차수열인지 검사한다
        bool progressive = true;
        for(int i = 0; i < M.size()-1; ++i)
            if(M[i+1] - M[i] != M[1] - M[0])
                progressive = false;
        // 등차수열이고 공차가 1 이면 난이도는 2
        if(progressive && abs(M[1] - M[0]) == 1) return 2;

        // 두 수가 번갈아 등장하는지 확인한다
        bool alternating = true;
        for(int i = 0; i < M.size(); ++i)
            if(M[i] != M[i%2])
                alternating = false;

        // 두 수가 번갈아 등장하면 난이도는 4
        if(alternating) return 4;
        
        // 공차가 1 아닌 등차수열의 난이도는 5
        if(progressive) return 5;

        // 이외는 모두 난이도 10
        return 10;
    }

    // minDifficulty() 함수의 반환값을 저장하는 캐시
    // 모두 -1 로 초기화되어 있어야 한다
    vector<int> cache;

    // N 을 i번째 글자부터 적절히 쪼갰을 때 최소의 난이도를 반환
    int minDifficulty(int i)
    {
        // 이미 문자열의 끝에 도달했으면 난이도는 0
        if(i == N.size()) return 0;

        // 저장된 값이 있으면 반환한다
        int& ret = cache[i];
        if(ret != -1) return ret;

        ret = 99999; 
        for(int j = 3; j <= 5; ++j)
            if(i + j <= N.size())          
                ret = min(ret, minDifficulty(i + j) + classify(i, i + j - 1));

        return ret;
    }

    // 주어진 문제를 해결
    int solve() {
        // 캐시를 초기화: 모든 값을 -1 로 채운다
        cache.assign(N.size(), -1);
        return minDifficulty(0);
    }
};

int main()
{
	int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc)
	{
        MemorizingPI pi;
        cin >> pi.N;
        cout << pi.solve() << endl;
	}
}
