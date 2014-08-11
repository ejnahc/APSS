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

// 이 메뉴로 모두가 식사할 수 있는지 여부를 반환한다
bool everybodyCanEat(const vector<int>& menu);

// 요리할 수 있는 음식의 종류 수
int M;

// food 번 요리를 만들까 말까를 결정한다
int selectMenu(vector<int>& menu, int food) {
    if(food == M) {
        if(everybodyCanEat(menu))
            return menu.size();
        return 987654321;
    }
    int ret = selectMenu(menu, food+1);
    menu.push_back(food);
    ret = min(ret, selectMenu(menu, food+1) + 1);
    menu.pop_back();
    return ret;
}

bool everybodyCanEat(const vector<int>& menu)
{
    return false;
}

int main()
{
    int cases;
    scanf("%d", &cases);
    for(int cc = 0; cc < cases; ++cc)
    {
    }
}

