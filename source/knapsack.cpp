//
// Created by ButcherX on 23-11-22.
//
#include<vector>
#include<iostream>
using std::vector;
//暴力递归
int process1(const vector<int> &weight, const vector<int> &value, int index, bool take, int capacity)
{
    if(index >= weight.size() || capacity < 0)
        return 0;
    if(take)
    {
        if(weight[index] > capacity)
            return 0;
        int ret1 = process1(weight, value, index + 1, true , capacity - weight[index]);
        int ret2 = process1(weight, value, index + 1, false, capacity - weight[index]);
        return value[index] + std::max(ret1, ret2);
    }
    else
    {
        int ret1 = process1(weight, value, index + 1, true , capacity);
        int ret2 = process1(weight, value, index + 1, false, capacity);
        return std::max(ret1, ret2);
    }
}

int knapSack1(vector<int> weight, vector<int> value, int capacity)
{
    if(weight.size() != value.size())
        return 0;
    return std::max(process1(weight, value, 0, true, capacity), process1(weight, value, 0, false, capacity));
}
//============================================================================
//加表
int process2(const vector<int> &weight, const vector<int> &value, int index, bool take, int capacity, vector<vector<vector<int>>> &dp)
{
    if(index >= weight.size() || capacity < 0)
        return 0;
    if(dp[index][capacity][take] != 0)
        return dp[index][capacity][take];
    if(take)
    {
        if(weight[index] > capacity)
            return 0;
        int ret1 = process2(weight, value, index + 1, true , capacity - weight[index], dp);
        int ret2 = process2(weight, value, index + 1, false, capacity - weight[index], dp);
        dp[index][capacity][take] = value[index] + std::max(ret1, ret2);
        return value[index] + std::max(ret1, ret2);
    }
    else
    {
        int ret1 = process2(weight, value, index + 1, true , capacity, dp);
        int ret2 = process2(weight, value, index + 1, false, capacity, dp);
        dp[index][capacity][take] = std::max(ret1, ret2);
        return std::max(ret1, ret2);
    }
}
int knapSack2(vector<int> weight, vector<int> value, int capacity)
{
    if(weight.size() != value.size())
        return 0;
    vector<vector<vector<int>>> dp;
    dp.resize(weight.size());
    for(int i = 0; i < weight.size(); i++)
    {
        dp[i].resize(capacity + 1);///注意+1！！！！
        for(int k = 0; k <= capacity; k++)
        {
            dp[i][k].resize(2);
            dp[i][k][0] = 0;
            dp[i][k][1] = 0;
        }
    }
    int ret = std::max(process2(weight, value, 0, true, capacity, dp), process2(weight, value, 0, false, capacity, dp));
    return ret;
}
//===================================================================================
//动态规划
int knapSack3(vector<int> weight, vector<int> value, int capacity)
{
    if(weight.size() != value.size())
        return 0;
    vector<vector<vector<int>>> dp;
    dp.resize(weight.size());
    for(int i = 0; i < weight.size(); i++)
    {
        dp[i].resize(capacity + 1);///注意+1！！！！
        for(int k = 0; k <= capacity; k++)
        {
            dp[i][k].resize(2);
            dp[i][k][0] = 0;
            dp[i][k][1] = 0;
        }
    }
    int s = weight.size();
    for(int i = 0; i <= capacity; i++)
    {
        if(weight[s-1] <= i)
            dp[s-1][i][1] = value[s-1];
        dp[s-1][i][0] = 0;
    }

    for(int i = s - 2; i >= 0; i--)
    {
        for(int k = 0; k <= capacity; k++)
        {
            dp[i][k][0] = std::max(dp[i+1][k][1], dp[i+1][k][0]);
            if(weight[i] <= k)
                dp[i][k][1] = value[i] + std::max(dp[i+1][k-weight[i]][1], dp[i+1][k-weight[i]][0]);
        }
    }
    return std::max(dp[0][capacity][1], dp[0][capacity][0]);

}
int main()
{
    vector<int> value  = {3, 2, 4,  7,  3, 1, 7};
    vector<int> weight = {5, 6, 3, 19, 12, 4, 2};
    int max = knapSack3(weight, value, 15);
    std::cout<< max;
}
