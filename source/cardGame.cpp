//
// Created by ButcherX on 23-11-21.
//
//https://leetcode.cn/problems/predict-the-winner/?utm_source=LCUS&utm_medium=ip_redirect&utm_campaign=transfer2china
#include<iostream>
#include<deque>
#include<vector>
using std::deque;
using std::vector;
int g(deque<int> cards, int sumPoints);
int f(deque<int> cards, int sumPoints)
{
    if(cards.empty())
        return 0;
    int lpoint = cards.front();
    cards.pop_front();
    int a = sumPoints - g(cards, sumPoints - lpoint);
    cards.push_front(lpoint);
    int rpoint = cards.back();
    cards.pop_back();
    int b = sumPoints - g(cards, sumPoints - rpoint);
    return std::max(a, b);
}

int g(deque<int> cards, int sumPoints)
{
    if(cards.empty())
        return 0;
    int lpoint = cards.front();
    cards.pop_front();
    int a = sumPoints - f(cards, sumPoints - lpoint);
    cards.push_front(lpoint);
    int rpoint = cards.back();
    cards.pop_back();
    int b = sumPoints - f(cards, sumPoints - rpoint);
    return std::max(a, b);
}
int cardGame(deque<int> cards)
{
    int sum = 0;
    for(auto c : cards)
        sum += c;
    int fPoints = f(cards, sum);
    return std::max(fPoints, sum - fPoints);
}
///===============================================================
//改进，添加状态
int g1(const vector<int>& cards, int left, int right, int sumPoints);
int f1(const vector<int>& cards, int left, int right, int sumPoints)
{
    if(left > right)
        return 0;
    int a = sumPoints - g1(cards, left + 1, right, sumPoints - cards[left]);
    int b = sumPoints - g1(cards, left , right - 1, sumPoints - cards[right]);
    return std::max(a, b);
}
int g1(const vector<int>& cards, int left, int right, int sumPoints)
{
    if(left > right)
        return 0;
    int a = sumPoints - f1(cards, left + 1, right, sumPoints - cards[left]);
    int b = sumPoints - f1(cards, left , right - 1, sumPoints - cards[right]);
    return std::max(a, b);
}
int cardGame1(const vector<int>& cards)
{
    int sum = 0;
    for(auto c : cards)
        sum += c;
    int fPoints = f1(cards, 0, cards.size() - 1, sum);
    return std::max(fPoints, sum - fPoints);
}
//===================================================================================
//发现f和g函数完全对称,可以压缩成一个函数
int getMaxPoints(const vector<int>& cards, int left, int right, int sumPoints)
{
    if(left > right)
        return 0;
    int a = sumPoints - getMaxPoints(cards, left + 1, right, sumPoints - cards[left]);
    int b = sumPoints - getMaxPoints(cards, left , right - 1, sumPoints - cards[right]);
    return std::max(a, b);
}
int cardGame2(const vector<int>& cards)
{
    int sum = 0;
    for(auto c : cards)
        sum += c;
    int fPoints = getMaxPoints(cards, 0, cards.size() - 1, sum);
    return std::max(fPoints, sum - fPoints);
}

//===================================================================================
//加表
//为了不让表过于庞大,删去sumPoints,改为在函数内部计算,这可能影响时间复杂度
int getMaxPoints1(const vector<int>& cards, int left, int right, vector<vector<int>> &dp)
{
    if(left > right)
        return 0;
    if(dp[left][right] != 0)
        return dp[left][right];
    int sumPoints = 0;
    for(int i = left; i <= right; i++)
        sumPoints += cards[i];
    int a = sumPoints - getMaxPoints1(cards, left + 1, right, dp);
    int b = sumPoints - getMaxPoints1(cards, left , right - 1, dp);
    dp[left][right] = std::max(a, b);
    return std::max(a, b);
}
int cardGame3(const vector<int>& cards)
{
    vector<vector<int>> dp;
    int size = cards.size();
    dp.resize(size);
    for(int i = 0; i < size; i++)
    {
        dp[i].resize(size);
        for(int k = 0; k < size; k++)
        {
            dp[i][k] = 0;
        }
    }
    int sum = 0;
    for(auto c : cards)
        sum += c;
    int a = getMaxPoints1(cards, 0, size - 1, dp);
    return std::max(a, sum - a);
}
//==================================================================================
//动态规划
int cardGame4(const vector<int>& cards)
{
    vector<vector<int>> dp(cards.size(), vector<int>(cards.size(), 0));
    int size = cards.size();
    //求sumPoints优化:用sumTable记录范围和
    //sumTable[l][r]即为cards在[l,r]范围上的分数和
    vector<vector<int>> sumTable(size, vector<int>(size, 0));
    sumTable[0][0] = cards[0];
    for(int n = 1; n < size; n++)
    {//先求出[0,1],[0,2],[0,3],....,[0,n]范围上的分数和
        sumTable[0][n] = sumTable[0][n-1] + cards[n];
    }
    //再求出[r,l]范围上的分数和
    for(int l = 1; l < size; l++)
    {
        for(int r = l; r < size; r++)
        {
            sumTable[l][r] = sumTable[0][r] - sumTable[0][l-1];
        }
    }

//    //特例初始化
//    for(int i = 0; i < size; i++)
//    {
//        dp[i][i] = cards[i];
//    }

    //按依赖打表
    for(int l = size - 1; l >= 0; l--)
    {
        for(int r = 0; r < size; r++)
        {
            dp[l][r] = std::max(sumTable[l][r] - (l+1 > r ? 0 : dp[l+1][r]), sumTable[l][r] - (l > r-1 ? 0 : dp[l][r-1]));
        }
    }

    return std::max(dp[0][size-1], sumTable[0][size-1] - dp[0][size-1]);
}
int main()
{
    vector<int> cards = {12,43,32,54,72,25,73,34,68,64,42,37,25,18,29,29,18,82};
    std::cout << cardGame1(cards) << std::endl;
    std::cout << cardGame2(cards) << std::endl;
    std::cout << cardGame3(cards) << std::endl;
    std::cout << cardGame4(cards) << std::endl;
}