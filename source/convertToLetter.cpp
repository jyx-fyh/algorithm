//
// Created by ButcherX on 23-11-22.
//
#include<string>
#include<iostream>
#include<vector>
using std::vector;
using std::string;
//暴力递归
int process(string numStr, int index, bool isTwo)
{
    if(index >= numStr.size() || index < 0)
        return 0;
    if(!isTwo)
    {
        if(numStr[index] == '0')///容易忽略,且必须放在下一个if之前
            return 0;
        if(index == numStr.size() - 1)
            return 1;
        return process(numStr, index + 1, false) + process(numStr, index + 1, true);
    }
    else
    {
        if(index + 1 >= numStr.size())
            return 0;
        if(numStr[index] == '0')///容易忽略
            return 0;
        int num = (numStr[index] - '0') * 10 + numStr[index+1] - '0';
        if(num > 26 || num <= 0)
            return 0;

        if(index == numStr.size() - 2)
            return 1;
        else
            return process(numStr, index + 2, false) + process(numStr, index + 2, true);
    }
}

int convert(string numStr)
{
    int counts = process(numStr, 0, false) + process(numStr, 0, true);
    return counts;
}
//======================================================================
//加表
int process1(string numStr, int index, bool isTwo, vector<vector<int>> &dp)
{
    if(index >= numStr.size() || index < 0)
        return 0;
    if(dp[isTwo][index] != 0)
        return dp[isTwo][index];
    if(!isTwo)
    {
        if(numStr[index] == '0')///容易忽略
            return 0;
        if(index == numStr.size() - 1)
            return 1;
        int count = process1(numStr, index + 1, false, dp) + process1(numStr, index + 1, true, dp);
        dp[isTwo][index] = count;
        return count;

    }
    else
    {
        if(index + 1 >= numStr.size())
            return 0;
        if(numStr[index] == '0')///容易忽略
            return 0;
        int num = (numStr[index] - '0') * 10 + numStr[index+1] - '0';
        if(num > 26 || num <= 0)
            return 0;
        if(index == numStr.size() - 2)
            return 1;
        else
        {
           int count =  process1(numStr, index + 2, false, dp) + process1(numStr, index + 2, true, dp);
           dp[isTwo][index] = count;
           return count;
        }
    }
}
int convert1(string numStr)
{
    vector<vector<int>> dp;
    dp.resize(2);
    for(int i = 0; i < 2; i++)
    {
        dp[i].resize(numStr.size());
        for(int k = 0; k < numStr.size(); k++)
        {
            dp[i][k] = 0;
        }
    }

    int counts = process1(numStr, 0, false, dp) + process1(numStr, 0, true, dp);
    return counts;
}

//=============================================
//动态规划
int convert2(string numStr)
{
    vector<vector<int>> dp;
    dp.resize(2);
    for(int i = 0; i < 2; i++)
    {
        dp[i].resize(numStr.size());
        for(int k = 0; k < numStr.size(); k++)
        {
            dp[i][k] = 0;
        }
    }
    //先填初始量
    int s = numStr.size();
    if(numStr[s-1] != '0')///!!!!
        dp[0][s-1] = 1;
    int num = (numStr[s-2] - '0') * 10 + numStr[s-1] - '0';
    if(num <= 26 && num > 0 && numStr[s-2] != '0')
        dp[1][s-2] = 1;
    if(numStr[s-2] != '0')///!!!!
        dp[0][s-2] = dp[0][s-1] + dp[1][s-1];
    //然后由初始量构建其他
    for(int i = s - 3; i >= 0; i--)
    {
        if(numStr[i] == '0')///!!!
            continue;
        dp[0][i] = dp[0][i+1] + dp[1][i+1];
        num = (numStr[i] - '0') * 10 + numStr[i+1] - '0';
        if(num <= 26 && num > 0)
            dp[1][i] = dp[0][i+2] + dp[1][i+2];
    }
    return dp[0][0] + dp[1][0];
}
int main()
{
    string str = "212121222111112001212111222112112";
    std::cout << convert(str)  << std::endl;
    std::cout << convert1(str) << std::endl;
    std::cout << convert2(str) << std::endl;
}
