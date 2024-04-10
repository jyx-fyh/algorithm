//
// Created by ButcherX on 23-12-9.
//
#include<iostream>
#include<vector>
using std::vector;
#include <chrono>
//每一种都尝试
int knapSackUnlimited(vector<int> weight, vector<int> value, int capacity)
{
    if(capacity < 0)
        return 0;
    int maxVal = 0;
    for(int i = 0; i < weight.size(); i++)
    {
        int val = 0;
        if(weight[i] <= capacity)//容易忽略
            val = value[i] + knapSackUnlimited(weight, value, capacity - weight[i]);
        maxVal = maxVal > val ? maxVal : val;
    }
    return maxVal;
}
//===================================================================
//动态规划
int knapSackUnlimited1(vector<int> weight, vector<int> value, int capacity)
{
    vector<int> dp(capacity + 1, 0);
    for(int c = 0; c <= capacity; c++)
    {
        int maxVal = 0;
        for(int i = 0; i < weight.size(); i++)
        {
            int val = 0;
            if(weight[i] <= c)
                val = value[i] + dp[c - weight[i]];
            maxVal = maxVal > val ? maxVal : val;
        }
        dp[c] = maxVal;
    }
    return dp[capacity];
}

///==========================================================================
//去重
int knapSackUnlimited4(vector<int> weight, vector<int> value, int capacity, int index)
{
    if(capacity < 0 || index >= weight.size())
        return 0;
    int max = 0;
    for(int i = 0; i * weight[index] <= capacity; i++)
    {
        int ret = knapSackUnlimited4(weight, value, capacity - weight[index] * i, index + 1);
        max = max > (i * value[index] + ret) ? max : (i * value[index] + ret);
    }
    return max;
}
//动态规划
int knapSackUnlimited5(vector<int> weight, vector<int> value, int capacity)
{
    vector<vector<int>> dp(capacity + 1, vector<int>(weight.size(), 0));
    for(int c = 0; c <= capacity; c++)
    {
        for(int index = weight.size() - 1; index >= 0; index--)
        {
            int max = 0;
            for(int i = 0; i * weight[index] <= c; i++)
            {
                int ret = index+1 > weight.size() ? 0 : dp[c-weight[index]*i][index+1];
                max = max > (i * value[index] + ret) ? max : (i * value[index] + ret);
            }
            dp[c][index] = max;
        }
    }
    return dp[capacity][0];
}
///===========================================================================
//从左到右
int process(vector<int> weight, vector<int> value, int index, int capacity)
{
    if(index >= weight.size() || capacity < 0)
        return 0;
    int ret1 = process(weight, value, index + 1, capacity);//不要此货物
    int ret2 = 0;
    if(weight[index] <= capacity)//当前容量够,才能要此货物
        ret2 = value[index] + process(weight, value, index, capacity - weight[index]);//要此货物
    return std::max(ret1 , ret2);
}
int knapSackUnlimited2(vector<int> weight, vector<int> value, int capacity)
{
    if(weight.size() != value.size())
        return 0;
    return process(weight, value, 0, capacity);
}
///==========================================================================
int knapSackUnlimited3(vector<int> weight, vector<int> value, int capacity)
{
    vector<vector<int>> dp(weight.size(), vector<int>(capacity + 1, 0));
    int last = weight.size() - 1;

    //特例初始化
    for(int c = 0; c <= capacity; c++)
    {
        if(weight[last] <= c)
            dp[last][c] = value[last];
    }

    //依次打表
    for(int i = weight.size() - 2; i >= 0; i--)
    {
        for(int c = 0; c <= capacity; c++)
        {
            int ret1 = dp[i+1][c];
            int ret2 = 0;
            if(weight[i] <= c)
                ret2 = value[i] + dp[i][c-weight[i]];
            dp[i][c] = std::max(ret1, ret2);
        }
    }
    return dp[0][capacity];
}
int main()
{
    vector<int> value  = {21,43,12,22,12,53,21,34,1};
    vector<int> weight = {14,23,54,33,11,33,7,24,2};
    int capacity = 50;
    std::cout << knapSackUnlimited1(weight, value, capacity) << std::endl;
    std::cout << knapSackUnlimited5(weight, value, capacity) << std::endl;

}