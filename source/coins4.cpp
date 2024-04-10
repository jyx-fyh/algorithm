//
// Created by ButcherX on 24-1-4.
//
#include<vector>
#include<iostream>
using std::vector;
int process(const vector<int> &coins, int rest, int index)
{
    if(rest == 0)//必须置前
        return 0;
    if(index >= coins.size())
        return INT32_MAX;
    int min = INT32_MAX;
    for(int i = 0; i * coins[index] <= rest; i++)
    {
        int ret = process(coins, rest - i * coins[index], index + 1);
        if(ret != INT32_MAX)
            min = min < ret + i ? min : ret + i;
    }
    return min;
}
int coins(const vector<int> &coins, int aim)
{
    return process(coins, aim, 0);
}
///=========================================================
int help(int rest, int index, int size, const vector<vector<int>> &dp)
{
    if(rest == 0)//必须置前
        return 0;
    if(rest < 0 || index >= size)
        return INT32_MAX;
    return dp[rest][index];
}
int coins1(const vector<int> &coins, int aim)
{
    vector<vector<int>> dp(aim + 1, vector<int>(coins.size(), 0));
    for(int rest = 0; rest <= aim; rest++)
    {
        for(int index = coins.size() - 1; index >= 0; index--)
        {
            int min = INT32_MAX;
            for(int i = 0; i * coins[index] <= rest; i++)
            {
                int ret = help(rest - i * coins[index], index + 1, coins.size(), dp);
                if(ret != INT32_MAX)
                    min = min < ret + i ? min : ret + i;
            }
            dp[rest][index] = min;
        }
    }
    return dp[aim][0];
}
///==============================================================
int coins2(const vector<int> &coins, int aim)
{
    vector<vector<int>> dp(aim + 1, vector<int>(coins.size(), 0));
    for(int rest = 0; rest <= aim; rest++)
    {
        for(int index = coins.size() - 1; index >= 0; index--)
        {
            int val = help(rest - coins[index], index, coins.size(), dp);
            dp[rest][index] = std::min(
                    val == INT32_MAX ? INT32_MAX : val + 1,
                    help(rest, index + 1, coins.size(), dp)
                    );
        }
    }
    return dp[aim][0];
}
int main()
{
    vector<int> coin = {1, 2, 3, 14, 11 ,53, 23, 12, 46, 24, 9, 10};
//    std::cout << coins(coin, 200) << std::endl;
    std::cout << coins1(coin, 1000) << std::endl;
    std::cout << coins2(coin, 1000) << std::endl;

}