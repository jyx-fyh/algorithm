//
// Created by ButcherX on 23-11-27.
//
#include<iostream>
#include<string>
#include<vector>
using std::vector;
using std::string;
int process(const string &str, int left, int right)
{
    if(left > right)
        return 0;
    if(left == right)
        return 1;
    int count = 0;
    int max = 1;//!!!最少返回1,自对称

    for(int lp = left; lp < right; lp++)
    {
        if(right - lp + 1 <= max)//剪枝!相同字符越多,剪的越多
            break;
        for(int rp = right; rp > lp; rp--)
        {
            if(str[rp] == str[lp])
            {
                count = 2 + process(str, lp + 1, rp - 1);
                break;
            }
        }
        max = max > count ? max : count;
    }
    return max;
}
int longestPalindromeSubseq(string s)
{
    return process(s, 0, s.length() - 1);
}
//==========================================================
//动态规划
int longestPalindromeSubseq1(string s)
{
    vector<vector<int>> dp(s.length(), vector<int>(s.length(), 0));
    //left-row,right-col
    //初始化
    for(int r = 0; r < s.length(); r++)
    {
        for(int c = 0; c < s.length(); c++)
        {
            if(r == c)
                dp[r][c] = 1;
        }
    }
    for(int c = 1; c < s.length(); c++)
    {
        for(int r = 0; r < s.length() - c; r++)
        {
            int count = 1;
            int max = 0;
            //dp[r][r+c]才是我们实际遍历的位置,斜着遍历
            for(int lp = r; lp < c + r; lp++)
            {
                if(c + r - lp + 1 <= max)
                    break;

                for(int rp = c + r; rp > lp; rp--)
                {
                    if(s[rp] == s[lp])
                    {
                        count = 2 + dp[lp+1][rp-1];
                        break;
                    }
                }
                max = max > count ? max : count;
            }
            dp[r][r+c] = max;
        }
    }
    return dp[0][s.length()-1];
}
//==============================================================
//暴力递归-改进
int process2(const string &str, int left, int right)
{
    if(left > right)
        return 0;
    if(left == right)
        return 1;
    if(str[left] == str[right])
        return 2 + process(str, left + 1, right - 1);
    int case1 = process(str, left + 1, right);
    int case2 = process(str, left, right - 1);
    //case3为process(str, left+1, right-1),而它不可能比case1和case2大,故直接忽略
    return std::max(case1, case2);
}
int longestPalindromeSubseq2(string s)
{
    return process(s, 0, s.length() - 1);
}
///=====================================================================================
//动态规划-改进
int longestPalindromeSubseq3(string s)
{
    vector<vector<int>> dp(s.length(), vector<int>(s.length(), 0));
    //left-row,right-col
    //初始化
    for(int r = 0; r < s.length(); r++)
    {
        for(int c = 0; c < s.length(); c++)
        {
            if(r == c)
                dp[r][c] = 1;
        }
    }
    for(int c = 1; c < s.length(); c++)
    {
        for(int r = 0; r < s.length() - c; r++)
        {
            //dp[r][r+c]才是我们实际遍历的位置,斜着遍历
            if(s[r] == s[c+r])
            {
                dp[r][c+r] = 2 + dp[r+1][c+r-1];
                continue;
            }
            dp[r][c+r] = std::max(dp[r+1][c+r], dp[r][c+r-1]);
        }
    }
    return dp[0][s.length()-1];
}
int main()
{
    string str = "123fjaslkdflaskldfnnsvin21";
    std::cout << longestPalindromeSubseq3(str);
}