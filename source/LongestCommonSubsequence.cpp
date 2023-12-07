//
// Created by ButcherX on 23-11-26.
//
#include<string>
#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<queue>
using std::vector;
using std::unordered_multimap;
using std::unordered_map;
using std::unordered_set;
using std::string;
using std::priority_queue;
int process(const string &str, string sub, unordered_map<string, int> &map)
{   //先要
    if(sub.empty())
        return 0;
    if(map.find(sub) != map.end())
        return map[sub];
    int max1 = 0;
    int max2 = 0;
    for(int a = 0; a < sub.length(); a++)
    {
        int preMark = -1;
        int count = 0;
        for(int start = a; start < sub.length(); start++)
        {
            int pos = str.find(sub[start], preMark + 1);
            if(pos == std::string::npos)
                continue;
            count++;
            preMark = pos;
        }
        max1 = max1 > count ? max1 : count;
    }

    if(max1 >= sub.length() - 1)//剪枝
    {
        map.emplace(sub, max1);
        return max1;
    }

    //再选哪些不要
    for(int i = 0; i < sub.length(); i++)
    {
        string copy = sub;
        int ret = process(str, copy.erase(i, 1), map);
        max2 = max2 > ret ? max2 : ret;
    }
    map.emplace(sub, max1 > max2 ? max1 : max2);
    return max1 > max2 ? max1 : max2;
}
int longestCommonSubsequence(string strA, string strB)
{
    unordered_map<string, int> map;
    return process(strA, strB, map);
}
//=======================================================================
//剪枝
int process1(const string &str, string sub, int &max, unordered_map<string, int> &map)
{   //先要
    if(max >= sub.length())//剪枝
        return 0;
    if(sub.empty())
        return 0;
    if(map.find(sub) != map.end())
        return map[sub];
    for(int a = 0; a < sub.length(); a++)
    {
        int preMark = -1;
        int count = 0;
        for(int start = a; start < sub.length(); start++)
        {
            int pos = str.find(sub[start], preMark + 1);
            if(pos == std::string::npos)
                continue;
            count++;
            preMark = pos;
        }
        max = max > count ? max : count;
    }

    //再选哪些不要
    for(int i = 0; i < sub.length(); i++)
    {
        string copy = sub;
        int ret = process1(str, copy.erase(i, 1), max, map);
        max = max > ret ? max : ret; //这里要放在循环里面才能为后续递归剪枝！
    }
    map.emplace(sub, max);
    return max;
}
int longestCommonSubsequence1(string strA, string strB)
{
    unordered_map<string, int> map;
    int max = 0;
    return process1(strA, strB, max, map);
}
//=======================================================================
//我，无耻之徒，这样解
//必须用multimap,行作为key,而同一行可能有多个点
int next(const unordered_multimap<int, int> &map, int row, int col)
{
    int count;
    int max = 0;
    auto point = map.begin();
    while(point != map.end())
    {
        if(point->first > row && point->second > col)
        {
            //注意！这里不是状态转移方程！下面的形参row必须与这里的实参row有关！
            count = 1 + next(map, point->first, point->second);
            max = max > count ? max : count;
        }
        point++;
    }
    return max;
}
int longestCommonSubsequence2(string strA, string strB)
{
    unordered_multimap<int, int> map;
    for(int a = 0; a < strA.length(); a++)
    {
        for(int b = 0; b < strB.length(); b++)
        {
            if(strA[a] == strB[b])
                map.emplace(a, b);
        }
    }
    if(map.size() == 1)//0和1个点无法构成线段,直接返回
        return 1;
    if(map.empty())
        return 0;
    int maxRoute = 0;
    for(auto point = map.begin(); point != map.end(); point++)
    {
        int row = point->first;
        int col = point->second;
        maxRoute = std::max(maxRoute, next(map, row, col));
    }
    return maxRoute + 1; //点的数量比线段多1
}
//====================================================================
//记忆化搜索
int next1(const unordered_multimap<int, int> &map, int row, int col, vector<vector<int>> &memo)
{
    if(memo[row][col] != 0)
        return memo[row][col];
    int count;
    int max = 0;
    auto point = map.begin();
    while(point != map.end())
    {
        if(point->first > row && point->second > col)
        {
            count = 1 + next1(map, point->first, point->second, memo);
            max = max > count ? max : count;
        }
        point++;
    }
    memo[row][col] = max;
    return max;
}
int longestCommonSubsequence3(string strA, string strB)
{
    unordered_multimap<int, int> map;
    vector<vector<int>> memo;
    memo.resize(strA.length());
    for(int i = 0; i < strA.length(); i++)
        memo[i].resize(strB.length());
    for(int a = 0; a < strA.length(); a++)
    {
        for(int b = 0; b < strB.length(); b++)
        {
            if(strA[a] == strB[b])
                map.emplace(a, b);
        }
    }
    if(map.size() == 1)//0和1个点无法构成线段,直接返回
        return 1;
    if(map.empty())
        return 0;
    int maxRoute = 0;
    for(auto point = map.begin(); point != map.end(); point++)
    {
        int row = point->first;
        int col = point->second;
        maxRoute = std::max(maxRoute, next1(map, row, col, memo));
    }
    return maxRoute + 1; //点的数量比线段多1
}
//===========================================================================
//暴力递归->动态规划
int process(const string &strA, const string &strB, int indexA, int indexB)
{
    if(indexA >= strA.length() || indexB >= strB.length())
        return 0;
    if(strA[indexA] == strB[indexB])
        return 1 + process(strA, strB, indexA + 1, indexB + 1);
    int case1 = process(strA, strB, indexA + 1, indexB);
    int case2 = process(strA, strB, indexA, indexB + 1);
    int case3 = process(strA, strB, indexA + 1, indexB + 1);
    return std::max(case1, std::max(case2, case3));
}
int longestCommonSubsequence4(string strA, string strB)
{
    return process(strA, strB, 0, 0);
}
//============================================================================
//动态规划
int longestCommonSubsequence5(string strA, string strB)
{
    vector<vector<int>> dp(strB.length() + 1, vector<int>(strA.length() + 1, -1));
    for(int i = 0; i <= strA.length(); i++)
        dp[strB.length()][i] = 0;
    for(int i = 0; i <= strB.length(); i++)
        dp[i][strA.length()] = 0;
    for(int i = strB.length() - 1; i >= 0; i--)
    {
        for(int k = strA.length() - 1; k >= 0; k--)
        {
            if(strA[k] == strB[i])
            {
                dp[i][k] = 1 + dp[i+1][k+1];
                continue;
            }
            dp[i][k] = std::max(dp[i+1][k],std::max(dp[i][k+1], dp[i+1][k+1]));
        }
    }
    return dp[0][0];
}
//=============================================================================
int main()
{
    string r = "nsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxgl";
    string c = "papmretkborsrurgnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxglnsnupotstmnkfcfavaxgltina";
    int ret = longestCommonSubsequence3(r, c);
    std::cout << ret;
}