//
// Created by ButcherX on 24-1-3.
//
#include<vector>
#include<iostream>
#include<unordered_map>
using std::unordered_map;
using std::vector;
struct info
{
    int value;
    int count;
    explicit info(int _value = 0, int _count = 0):value(_value), count(_count){};
};
int process(const vector<info> &coin, int rest, int index)
{
    if(rest == 0)//必须置前
        return 1;
    if(index >= coin.size())
        return 0;
    int ret = 0;
    for(int i = 0; i * coin[index].value <= rest && i <= coin[index].count; i++)
    {
        ret += process(coin, rest - i * coin[index].value, index + 1);
    }
    return ret;
}
int coins(const vector<int> &coins, int aim)
{
    vector<info> coin;
    unordered_map<int, int> map;
    for(int c : coins)//统计面值及其出现次数
    {
        if(map.find(c) == map.end())
        {
            coin.emplace_back(c, 1);
            map.emplace(c, coin.size() - 1);
        }
        else
            coin[map[c]].count++;
    }
    return process(coin, aim, 0);
}
///===============================================
//动态规划
int help(int rest, int index, int size, const vector<vector<int>> &dp)
{
    if(rest == 0)//必须置前
        return 1;
    if(rest < 0 || index >= size)
        return 0;
    return dp[rest][index];
}
int coins1(const vector<int> &coins, int aim)
{
    vector<info> coin;
    unordered_map<int, int> map;
    vector<vector<int>> dp(aim + 1, vector<int>(coins.size(), 0));
    for(int c : coins)//统计面值及其出现次数
    {
        if(map.find(c) == map.end())
        {
            coin.emplace_back(c, 1);
            map.emplace(c, coin.size() - 1);
        }
        else
            coin[map[c]].count++;
    }

    for(int rest = 0; rest <= aim; rest++)
    {
        for(int index = coin.size() - 1; index >= 0; index--)
        {
            int ret = 0;
            for(int i = 0; i * coin[index].value <= rest && i <= coin[index].count; i++)
                ret += help(rest - i * coin[index].value, index + 1, coin.size(), dp);
            dp[rest][index] = ret;
        }
    }
    return dp[aim][0];
}

///==================================================
int coins2(const vector<int> &coins, int aim)
{
    vector<info> coin;
    unordered_map<int, int> map;
    vector<vector<int>> dp(aim + 1, vector<int>(coins.size(), 0));
    for(int c : coins)//统计面值及其出现次数
    {
        if(map.find(c) == map.end())
        {
            coin.emplace_back(c, 1);
            map.emplace(c, coin.size() - 1);
        }
        else
            coin[map[c]].count++;
    }

    for(int rest = 0; rest <= aim; rest++)
    {
        for(int index = coin.size() - 1; index >= 0; index--)
        {
            dp[rest][index] = help(rest, index + 1, coin.size(), dp)
                            + help(rest - coin[index].value, index, coin.size(), dp)
                            - help(rest - (coin[index].count + 1) * coin[index].value, index + 1, coin.size(), dp);
        }
    }
    return dp[aim][0];
}
int main()
{
    vector<int> coin = {1,2,1,1,2,1,2,2,3,3,3,3,4,5,5,5,6,6,7,7,8,9};
    std::cout << coins1(coin, 20) << std::endl;
    std::cout << coins(coin, 20) << std::endl;
    std::cout << coins2(coin, 20) << std::endl;


}