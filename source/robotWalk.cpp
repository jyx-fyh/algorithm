//
// Created by ButcherX on 23-11-18.
//
#include<iostream>
#include<unordered_map>
#include<vector>
using std::vector;
using std::unordered_multimap;
//暴力递归
void process(int n, int start, int aim, int step, int &counts)
{
    if(start <= 0 || start > n)
        return;
    if(step == 0)
    {
        if(start == aim)
        {
            counts++;
            return;
        }
        else
            return;
    }
    process(n, start - 1, aim, step - 1, counts);//向左走
    process(n, start + 1, aim, step - 1, counts);//向右走
}

int robotWalk(int n, int start, int aim, int step)
{
    int counts = 0;
    process(n, start, aim, step, counts);
    return counts;
}
//动态规划-前置要求-修改返回值传递方式
int process1(int n, int start, int aim, int step)
{
    if(start <= 0 || start > n)
        return 0;
    if(step == 0)
    {
        if(start == aim)
        {
            return 1;
        }
        else
            return 0;
    }
    return process1(n, start - 1, aim, step - 1) + process1(n, start + 1, aim, step -1);
}

int robotWalk1(int n, int start, int aim, int step)
{
    return process1(n, start, aim, step);
}

//动态规划-加表
int process2(int n, int start, int aim, int step, vector<vector<int>> &map)
{
    if(start <= 0 || start > n)
        return 0;
    if(map[start][step] != 0)
        return map[start][step];
    if(step == 0)
    {
        if(start == aim)
            return 1;
        else
            return 0;
    }
    int count = process2(n, start - 1, aim, step - 1, map) + process2(n, start + 1, aim, step -1, map);
    map[start][step] = count;
    return count;
}

int robotWalk2(int n, int start, int aim, int step)
{
    vector<vector<int>> map;
    map.resize(n + 1); ///注意+1！！！
    for(int i = 0; i <= n; i++)
    {
        map[i].resize(step + 1);
        for(int k = 0; k <= step; k++)
        {
            map[i][k] = 0;
        }
    }
    return process2(n, start, aim, step, map);
}

//动态规划-递归转递推


int robotWalk3(int n, int start, int aim, int step) {
    vector<vector<int>> map;
    map.resize(n + 1);
    for (int i = 0; i <= n; i++) {
        map[i].resize(step + 1);
        for (int k = 0; k <= step; k++) {
            map[i][k] = 0;
        }
    }
    map[aim][0] = 1;
    for (int c = 1; c <= step; c++) {
        map[1][c] = map[2][c - 1];
        for (int r = 2; r <= n - 1; r++) {
            map[r][c] = map[r - 1][c - 1] + map[r + 1][c - 1];
        }
        map[n][c] = map[n - 1][c - 1];
    }
    return map[start][step];
}

int main()
{
//    std::cout << robotWalk (20, 4, 9, 31) << std::endl;
    std::cout << robotWalk2(20, 4, 9, 30) << std::endl;
    std::cout << robotWalk3 (20, 4, 9, 30) << std::endl;

}