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

// array[index] = element 인 첫 i 를 반환한다.
int firstIndex(const vector<int>& array, int element) {
    for(int i = 0; i < array.size(); ++i)
        if(array[i] == element)
            return i;
    return -1;
}

int main()
{
    int cases;
    scanf("%d", &cases);
    for(int cc = 0; cc < cases; ++cc)
    {
    }
}

