//
// Created by ButcherX on 23-11-30.
//
#include<vector>
#include<iostream>
using std::vector;
//本题有个疑惑：当bob死亡后，余下的步伐还要不要继续走，应该是需要的
//但为了展示全局(引用)变量在动态规划中的坏处,下面的代码没有继续走
//暴力递归
int process(const vector<vector<int>> &map, int &allPath, int row, int col, int rest)
{
    if(row >= map.size() || row < 0 || col >= map[0].size() || col < 0)
    {
        allPath++;
        return 1;
    }
    if(rest == 0)//不可前置
    {
        allPath++;
        return 0;
    }
    int diePath = 0;
    diePath += process(map, allPath, row + 1, col, rest - 1);
    diePath += process(map, allPath, row - 1, col, rest - 1);
    diePath += process(map, allPath, row, col + 1, rest - 1);
    diePath += process(map, allPath, row, col - 1, rest - 1);
    return diePath;
}

double dieOdds(int R, int C, int x, int y, int k)
{
    vector<vector<int>> map(R, vector<int>(C, 0));
    int allPath = 0;
    int diePath;
    diePath = process(map, allPath, x, y, k);
    double odds = (double)diePath / (double)allPath;
    return odds;
}

///======================================================================
//动态规划
double dieOdds1(int R, int C, int x, int y, int k)
{
    vector<vector<vector<int>>> dp(R,vector<vector<int>>(C, vector<int>(k + 1, 0)));///k+1!!!
    int allPath = 0;
    for(int i = 0; i < dp.size(); i++)
    {
        for(int k = 0; k < dp[i].size(); k++)
        {
            dp[i][k][0] = 0;
            allPath++;
        }
    }
    for(int rest = 1; rest <= k; rest++)
    {
        for(int r = 0; r < dp.size(); r++)
        {
            for(int c = 0; c < dp[r].size(); c++)
            {
                int diePath = 0;
                if(r + 1 >= dp.size()) //递归是在下游处理越界,此处必须上游处理越界情况
                    diePath++, allPath++;
                else
                    diePath += dp[r+1][c][rest-1];
                if(r - 1 < 0)
                    diePath++, allPath++;
                else
                    diePath += dp[r-1][c][rest-1];
                if(c + 1 >= dp[r].size())
                    diePath++, allPath++;
                else
                    diePath += dp[r][c+1][rest-1];
                if(c - 1 < 0)
                    diePath++, allPath++;
                else
                    diePath += dp[r][c-1][rest-1];
                dp[r][c][rest] = diePath;
            }
        }
    }

    return (double)dp[x][y][k] / (double)allPath;
}
//=========================================================================
//不要引用，改进版
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

info process3(const vector<vector<int>> &map, int row, int col, int rest)
{
    info inf;
    if(row >= map.size() || row < 0 || col >= map[0].size() || col < 0)
    {
        inf.allPath = 1;
        inf.diePath = 1;
        return inf;
    }
    if(rest == 0)//不可前置
    {
        inf.allPath = 1;
        return inf;
    }
    inf += process3(map, row + 1, col, rest - 1);
    inf += process3(map, row - 1, col, rest - 1);
    inf += process3(map, row, col + 1, rest - 1);
    inf += process3(map, row, col - 1, rest - 1);
    return inf;
}

double dieOdds3(int R, int C, int x, int y, int k)
{
    vector<vector<int>> map(R, vector<int>(C, 0));
    info inf;
    inf = process3(map, x, y, k);
    double odds = inf.diePath / inf.allPath;
    return odds;
}
//===================================================================
//进一步改动态规划
double dieOdds4(int R, int C, int x, int y, int k)
{
    vector<vector<vector<info>>> dp(R,vector<vector<info>>(C, vector<info>(k + 1)));///k+1!!!
    for(int i = 0; i < dp.size(); i++)
    {
        for(int k = 0; k < dp[i].size(); k++)
        {
            info inf(1, 0);
            dp[i][k][0] = inf;
        }
    }
    for(int rest = 1; rest <= k; rest++)
    {
        for(int r = 0; r < dp.size(); r++)
        {
            for(int c = 0; c < dp[r].size(); c++)
            {
                info inf;
                if(r + 1 >= dp.size())
                    inf.allPath++, inf.diePath++;
                else
                    inf += dp[r+1][c][rest-1];
                if(r - 1 < 0)
                    inf.allPath++, inf.diePath++;
                else
                    inf += dp[r-1][c][rest-1];
                if(c + 1 >= dp[r].size())
                    inf.allPath++, inf.diePath++;
                else
                    inf += dp[r][c+1][rest-1];
                if(c - 1 < 0)
                    inf.allPath++, inf.diePath++;
                else
                    inf += dp[r][c-1][rest-1];
                dp[r][c][rest] = inf;
            }
        }
    }
    return (double)dp[x][y][k].diePath / (double)dp[x][y][k].allPath;
}
int main()
{
    std::cout << dieOdds4(2, 2, 1, 1, 30);
}