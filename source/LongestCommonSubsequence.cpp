//
// Created by ButcherX on 23-11-26.
//
#include<string>
#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<queue>
#include<utility>
using std::pair;
using std::vector;
using std::unordered_multimap;
using std::unordered_map;
using std::unordered_set;
using std::string;
using std::priority_queue;
int process(const string &str, string sub, unordered_map<string, int> &memo)
{   //先全要
    if(sub.empty())
        return 0;
    if(memo.find(sub) != memo.end())
        return memo[sub];
    vector<int> record;
    int preMark = -1;
    for(int i = 0; i < sub.length(); i++)
    {
        int pos = str.find(sub[i], preMark + 1);//从preMark下一个开始查询
        if(pos == std::string::npos)
            continue;
        record.push_back(i);
        preMark = pos;
    }

    int max = record.size();
    //再选哪些不要
    for(auto p : record)
    {
        string copy = sub;
        int ret = process(str, copy.erase(p, 1), memo);
        max = max > ret ? max : ret;
    }
    memo.emplace(sub, max);
    return max;
}
int longestCommonSubsequence(string strA, string strB)
{
    unordered_map<string ,int> memo;
    return process(strA, strB, memo);
}
//=======================================================================
//我，无耻之徒，这样解
int next(const vector<vector<bool>> &points, int row, int col)
{
    if(row >= points.size() || col >= points[0].size())
        return 0;
    int count;
    int max = 0;
    for(int r = row; r < points.size(); r++)
    {
        for(int c = col; c < points[0].size(); c++)
        {
            if(points[r][c])
            {
                count = 1 + next(points, r + 1, c + 1);
                max = max > count ? max : count;
                break;
            }
        }
    }
    return max;
}
int longestCommonSubsequence2(string strA, string strB)
{
    vector<vector<bool>> points(strA.size(), vector<bool>(strB.size(), false));
    for(int a = 0; a < strA.length(); a++)
    {
        for(int b = 0; b < strB.length(); b++)
        {
            if(strA[a] == strB[b])
                points[a][b] = true;
        }
    }
    return next(points, 0, 0);
}
//====================================================================

//记忆化搜索
int next1(const vector<vector<bool>> &points, int row, int col, vector<vector<int>> &memo)
{
    if(row >= points.size() || col >= points[0].size())
        return 0;
    if(memo[row][col] != 0)
        return memo[row][col];
    int count;
    int max = 0;
    int preCol = INT32_MAX;
    for(int r = row; r < points.size(); r++)
    {
        for(int c = col; c < points[0].size(); c++)
        {
            if(c < preCol && points[r][c])
            {
                count = 1 + next1(points, r + 1, c + 1, memo);
                max = max > count ? max : count;
                preCol = c;
                break;
            }
        }
    }

    memo[row][col] = max;
    return max;
}
int longestCommonSubsequence3(string strA, string strB)
{
    vector<vector<bool>> points(strA.size(), vector<bool>(strB.size(), false));
    vector<vector<int>> memo(strA.size(), vector<int>(strB.size(), 0));
    for(int a = 0; a < strA.length(); a++)
    {
        for(int b = 0; b < strB.length(); b++)
        {
            if(strA[a] == strB[b])
                points[a][b] = true;
        }
    }
    return next1(points, 0, 0, memo);
}
//===========================================================================

//===========================================================================
//暴力递归->动态规划
int process1(const string &strA, const string &strB, int indexA, int indexB, vector<vector<int>> &memo)
{
    if(indexA < 0 || indexB < 0)
        return 0;
    if(memo[indexA][indexB] != 0)
        return memo[indexA][indexB];
    if(strA[indexA] == strB[indexB])
    {
        memo[indexA][indexB] =  1 + process1(strA, strB, indexA - 1, indexB - 1, memo);
        return memo[indexA][indexB];
    }
    int case1 = process1(strA, strB, indexA - 1, indexB, memo);
    int case2 = process1(strA, strB, indexA, indexB - 1, memo);
    memo[indexA][indexB] = std::max(case1, case2);;
    return std::max(case1, case2);
}
int longestCommonSubsequence6(string strA, string strB)
{
    vector<vector<int>> memo(strA.size(), vector<int>(strB.size(), 0));
    return process1(strA, strB, strA.length() - 1, strB.length() - 1, memo);
}

//============================================================================
//动态规划
int longestCommonSubsequence5(string strA, string strB)
{
    vector<vector<int>> dp(strA.length(), vector<int>(strB.length(), 0));
    for(int a = 0; a < strA.length(); a++)
    {
        for(int b = 0; b < strB.length(); b++)
        {
            if(strA[a] == strB[b])
            {
                dp[a][b] = 1 + ((a - 1 < 0 || b - 1 < 0) ? 0 : dp[a-1][b-1]);//注意边界处理
                continue;
            }
            dp[a][b] = std::max(a - 1 < 0 ? 0 : dp[a-1][b], b - 1 < 0 ? 0 : dp[a][b-1]);//注意边界处理
        }
    }
    return dp[strA.length()-1][strB.length()-1];
}
//=============================================================================
int main()
{
    string r = "fdasadfasfafasdoijnjviohiuqhfuqbdsdasadfasfafasdoijnjviohiuqhfuqbdsdasadfasfafasdoijnjviohiuqhfuqbdsafbhuabsdnsmcsdfasad";
    string c = "fhadsoiifnffasdfadsfasdfiuhdasiufdasadfasfafasdoijnjviohiuqhfuqbdsdasadfasfafasdoijnjviohiuqhfuqbdsdasadfasfafasdoijnjviohiuqhfuqbdsbiubqwuyefjbadwu";
    int ret = longestCommonSubsequence5(r, c);
    std::cout << ret;
}