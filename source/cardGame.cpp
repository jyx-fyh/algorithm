//
// Created by ButcherX on 23-11-21.
//
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
//为了不让表过于庞大,删去sumPoints,改为在函数内部计算,这可能大幅度影响时间复杂度
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
    vector<vector<int>> dp;
    int size = cards.size();
    dp.resize(size);
    //用表记录范围和
    vector<vector<int>> sumTable;
    sumTable.resize(size);
    sumTable[0].resize(size);
    sumTable[0][0] = cards[0];
    for(int n = 1; n < size; n++)
    {
        sumTable[n].resize(size);
        sumTable[0][n] = sumTable[0][n-1] + cards[n];
    }
    for(int l = 1; l < size; l++)
    {
        for(int r = l; r < size; r++)
        {
            sumTable[l][r] = sumTable[0][r] - sumTable[0][l-1];
        }
    }
    //建表
    for(int i = 0; i < size; i++)
    {
        dp[i].resize(size);
        for(int k = 0; k < size; k++)
        {
            dp[i][k] = 0;
        }
    }
    //填写已知信息
    for(int i = 0; i < size; i++)
    {
        dp[i][i] = cards[i];
    }
    //按依赖继续填表
    for(int r = 1; r < size; r++)
    {
        for(int l = 0; l < size - 1; l++)
        {
            dp[l][r+l] = std::max(sumTable[l][r+l] - dp[l][r+l-1], sumTable[l][r+l] - dp[l+1][r+l]);
        }
    }
    return std::max(dp[0][size-1], sumTable[0][size-1] - dp[0][size-1]);
}
int main()
{
    vector<int> cards = {5, 7, 4, 5, 8, 1, 6, 0, 3, 4, 6, 1, 7};
    std::cout << cardGame1(cards) << std::endl;
    std::cout << cardGame2(cards) << std::endl;
    std::cout << cardGame3(cards) << std::endl;
    std::cout << cardGame4(cards) << std::endl;
}