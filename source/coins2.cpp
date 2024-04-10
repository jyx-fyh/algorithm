//
// Created by ButcherX on 24-1-3.
//
#include<vector>
#include<iostream>
using std::vector;
int process(const vector<int> &coins, int rest, int index)
{
    if(rest == 0)//必须置前
        return 1;
    if(index >= coins.size())
        return 0;
    int ret = 0;
    for(int i = 0; i * coins[index] <= rest; i++)
    {
        ret += process(coins, rest - i * coins[index], index + 1);
    }
    return ret;
}
int coins(const vector<int> &coins, int aim)
{
    return process(coins, aim, 0);
}
///==================================================
//动态规划
int help(int size, int rest, int index, const vector<vector<int>> &dp)
{
    if(rest == 0)//必须置前
        return 1;
    if(rest < 0 || index >= size)
        return 0;
    return dp[rest][index];
}
int coins1(const vector<int> &coins, int aim)
{
    vector<vector<int>> dp(aim + 1, vector<int>(coins.size(), 0));
    for(int rest = 0; rest <= aim; rest++)
    {
        for(int index = coins.size() - 1; index >= 0; index--)
        {
            int ret = 0;
            for(int i = 0; i * coins[index] <= rest; i++)
            {
                ret += help(coins.size(), rest - i * coins[index], index + 1, dp);
            }
            dp[rest][index] = ret;
        }
    }
    return dp[aim][0];
}
///============================================
//斜率优化
int coins2(const vector<int> &coins, int aim)
{
    vector<vector<int>> dp(aim + 1, vector<int>(coins.size(), 0));
    for(int rest = 0; rest <= aim; rest++)
    {
        for(int index = coins.size() - 1; index >= 0; index--)
        {
            dp[rest][index] = help(coins.size(), rest-coins[index], index, dp)  + help(coins.size(), rest, index+1, dp);
        }
    }
    return dp[aim][0];
}



int main()
{
    vector<int> coin = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << coins1(coin, 45) << std::endl;
    std::cout << coins(coin, 45) << std::endl;
    std::cout << coins2(coin, 45) << std::endl;

}