//
// Created by ButcherX on 23-12-1.
//
#include<vector>
#include<iostream>
using std::vector;
#define NOWAY 1000000
//递归分支
//无法处理0面值,否则无穷递归
int process(const vector<int> &coins, int index, int aim)
{
    if(aim == 0)
        return 0;
    if(index >= coins.size() || aim < 0)
        return NOWAY;
    int a = process(coins, index, aim - coins[index]);
    int b = process(coins, index + 1, aim);
    if(a == NOWAY && b == NOWAY)
        return NOWAY;
    return std::min(a + 1, b);//a+1可能溢出,所以将NOWAY设置为MAX-1
}
//==========================================================
//动态规划-递归分支
//结果发现此方法用INT32_MAX会溢出,所以以后尽量不要使用INT32_MAX,就用-1
int currency(const vector<int> &coins, int aim)
{
    vector<vector<int>> dp(coins.size(), vector<int>(aim + 1, 0));
    int sz = coins.size();
    dp[sz-1][0] = NOWAY;
    for(int a = 1; a <= aim; a++)
    {
        if(a - coins[sz-1] == 0) //上游处理基线条件
            dp[sz-1][a] = 1;
        else if(a - coins[sz-1] < 0) //上游处理基线条件
            dp[sz-1][a] = NOWAY;
        else
            dp[sz-1][a] = dp[sz-1][a-coins[sz-1]] + 1;
    }
    for(int i = sz - 2; i >= 0; i--)
    {
        for(int a = 0; a <= aim; a++)
        {
            int p1 = a - coins[i] < 0 ? NOWAY : a - coins[i];
            if(a - coins[i] < 0) //上游处理基线条件
                p1 = NOWAY;
            else if(a - coins[i] == 0) //上游处理基线条件
                p1 = 0;
            else
                p1 = dp[i][a-coins[i]];
            int p2 = dp[i+1][a];
            if(p1 == NOWAY && p2 == NOWAY)
                dp[i][a] = NOWAY;
            else
                dp[i][a] = std::min(p1 + 1, p2);
        }
    }
    return dp[0][aim];
}
//===========================================================
//for循环
int process1(const vector<int> &coins, int aim)
{
    if(aim == 0)
        return 0;
    if(aim < 0)
        return NOWAY;
    int min = NOWAY;
    for(int i = 0; i < coins.size(); i++)
    {
        int ret = 1 + process1(coins, aim - coins[i]);
        min = min < ret ? min : ret;
    }
    return min;
}
////========================================================================
////========================================================================
////========================================================================

//改为-1
int process2(const vector<int> &coins, int index, int aim)
{
    if(aim == 0)
        return 0;
    if(index >= coins.size() || aim < 0)
        return -1;
    int min;
    int a = process2(coins, index, aim - coins[index]);
    int b = process2(coins, index + 1, aim);
    if(a == -1 && b == -1)
        return -1;
    else if(a != -1 && b != -1)
        min = std::min(a + 1, b);
    else if(a == -1)
        min = b;
    else
        min = a + 1;
    return min;
}
///=============================================================
//改为-1
int currency1(const vector<int> &coins, int aim)
{
    vector<vector<int>> dp(coins.size(), vector<int>(aim + 1, 0));
    int sz = coins.size();
    //初始化最后一行
    dp[sz-1][0] = -1;
    for(int a = 1; a <= aim; a++)
    {
        int min;
        int p1, p2 = -1;
        if(a - coins[sz-1] == 0)
            p1 = 0;
        else if(a - coins[sz-1] < 0)
            p1 = -1;
        else
            p1 = dp[sz-1][a-coins[sz-1]];

        if(p1 == -1)
            min = -1;
        else
            min = p1 + 1;
        dp[sz-1][a] = min;
    }
    //打表
    for(int i = sz - 2; i >= 0; i--)
    {
        for(int a = 0; a <= aim; a++)
        {
            int p1;
            if(a - coins[i] < 0) //上游处理基线条件
                p1 = -1;
            else if(a - coins[i] == 0) //上游处理基线条件
                p1 = 0;
            else
                p1 = dp[i][a-coins[i]];

            int p2 = dp[i+1][a];
            if(p1 == -1 && p2 == -1)
                dp[i][a] = -1;
            else if(p1 != -1 && p2 != -1)
                dp[i][a] = std::min(p1 + 1, p2);
            else if(p1 == -1)
                dp[i][a] = p2;
            else
                dp[i][a] = p1 + 1;
        }
    }
    return dp[0][aim];
}
///=============================================================
//改为-1,for循环
int process3(const vector<int> &coins, int aim)
{
    if(aim == 0)
        return 0;
    if(aim < 0)
        return -1;
    int min = INT32_MAX;
    for(int i = 0; i < coins.size(); i++)
    {
        int ret = process3(coins, aim - coins[i]);
        if(ret != -1)
            min = min < ret + 1 ? min : ret + 1;
    }
    if(min == INT32_MAX)
        min = -1;
    return min;
}
//=================================================================
//process3改动态规划
int currency2(const vector<int> &coins, int aim)
{
    vector<int> dp(aim + 1, 0);
    for(int a = 0; a <= aim; a++)
    {
        int min = INT32_MAX;
        for(int i = 0; i < coins.size(); i++)
        {
            if(a - coins[i] > 0)
                min = min < dp[a-coins[i]] + 1? min : dp[a-coins[i]] + 1;
            else if(a - coins[i] == 0)
                min = 1;
        }
        if(min == INT32_MAX)
            min = -1;
        dp[a] = min;
    }
    return dp[aim];
}
//====================================================================

int main()
{
    vector<int> coins{12, 4, 2};
    std::cout << process2(coins, 0, 500) << std::endl;
    std::cout << currency1(coins, 500) << std::endl;
    std::cout << process3(coins, 500) << std::endl;
    std::cout << currency2(coins, 500) << std::endl;

}