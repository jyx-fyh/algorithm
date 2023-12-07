//
// Created by ButcherX on 23-11-30.
//
#include<iostream>
#include<vector>
#include<cmath>
using std::vector;
struct info
{
    double allPath;
    double diePath;
    explicit info(double all = 0, double die = 0):allPath(all), diePath(die){}
    info &operator+=(const info &a){
        allPath += a.allPath;
        diePath += a.diePath;
    }
};
//==================================================================
//使用for循环
info process(vector<int> hurts, int restHit, int restBlood)
{
    info inf;
    if(restHit == 0 || restBlood <= 0)
    {
        inf.allPath++;
        if(restBlood <= 0)
            inf.diePath++;
        return inf;
    }
    for(int i = 0; i < hurts.size(); i++)
        inf += process(hurts, restHit - 1, restBlood - hurts[i]);
    return inf;
}

double killMonster(int blood, int hurt, int hitTime)
{
    vector<int> hurts;
    hurts.resize(hurt + 1);
    for(int i = 0; i <= hurt; i++)
        hurts[i] = i;
    info ret = process(hurts, hitTime, blood);
    return ret.diePath / ret.allPath;
}
//===================================================================
//使用分支递归

int main()
{
    std::cout << killMonster(10, 9, 4) << std::endl;
}
