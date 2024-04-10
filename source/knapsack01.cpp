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
//===============================================================================================
//去掉take参数，这样memo表就可以压缩为二维数组
int process4(const vector<int> &weight, const vector<int> &value, int index, int capacity)
{
    if(index >= weight.size() || capacity < 0)//capacity可以为0
        return 0;
    int ret1 = process4(weight, value, index + 1, capacity);//不要此货物
    int ret2 = 0;
    if(weight[index] <= capacity)//当前容量够,才能要此货物
        ret2 = value[index] + process4(weight, value, index + 1, capacity - weight[index]);//要此货物
    return std::max(ret1 , ret2);
}
int knapSack4(vector<int> weight, vector<int> value, int capacity)
{
    if(weight.size() != value.size())
        return 0;
    return process4(weight, value, 0, capacity);
}
///============================================================================
int knapSack5(vector<int> weight, vector<int> value, int capacity)
{
    vector<vector<int>> dp(weight.size(), vector<int>(capacity + 1, 0));
    int last = weight.size() - 1;
    for(int c = 0; c <= capacity; c++)
    {
        if(weight[last] <= c)
            dp[last][c] = value[last];
    }
    for(int i = weight.size() - 2; i >= 0; i--)
    {
        for(int c = 0; c <= capacity; c++)
        {
            int ret1 = dp[i+1][c];
            int ret2 = 0;
            if(weight[i] <= c)
                ret2 = value[i] + dp[i+1][c-weight[i]];
            dp[i][c] = std::max(ret1, ret2);
        }
    }
    return dp[0][capacity];
}
///==========================================================
//不做特例初始化，统一处理
int help(int index, int capacity, int size, const vector<vector<int>> &dp)
{
    if(index >= size || capacity < 0)
        return 0;
    return dp[index][capacity];
}
int knapSack6(vector<int> weight, vector<int> value, int capacity)
{
    vector<vector<int>> dp(weight.size(), vector<int>(capacity + 1, 0));
    for(int i = weight.size() - 1; i >= 0; i--)
    {
        for(int c = 0; c <= capacity; c++)
        {
            int ret1 = help(i+1, c, weight.size(), dp);
            int ret2 = 0;
            if(weight[i] <= c)
                ret2 = value[i] + help(i+1, c-weight[i], weight.size(), dp);
            dp[i][c] = std::max(ret1, ret2);
        }
    }
    return dp[0][capacity];
}
int main()
{
    vector<int> value  = {3, 2, 4,  7,  3, 1, 7, 1, 45, 24, 13, 53, 24, 63};
    vector<int> weight = {5, 6, 3, 19, 12, 4, 2, 1, 21, 32, 43, 35, 15, 5};
    int max = knapSack6(weight, value, 60);
    std::cout<< max;
}
