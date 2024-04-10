//
// Created by ButcherX on 23-11-27.
//
#include<iostream>
#include<string>
#include<vector>
using std::vector;
using std::string;

//==============================================================
//暴力递归-改进
int process(const string &str, int left, int right)
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
int longestPalindromeSubseq(string s)
{
    return process(s, 0, s.length() - 1);
}
///=====================================================================================
//动态规划
int help(const string &str, int left, int right, const vector<vector<int>> &dp)
{
    if(left > right)
        return 0;
    if(left == right)
        return 1;
    return dp[left][right];
}
int longestPalindromeSubseq1(string s)
{
    vector<vector<int>> dp(s.length(), vector<int>(s.length(), 0));
    //left-row,right-col
    for(int c = 0; c < s.length(); c++)
    {
        for(int r = 0; r < s.length() - c; r++)
        {
            //dp[r][r+c]才是我们实际遍历的位置,斜着遍历
            if(s[r] == s[c+r])
            {
                dp[r][c+r] = 2 + help(s, r+1, c+r-1, dp);
                continue;
            }
            dp[r][c+r] = std::max(help(s, r+1, c+r, dp) ,help(s, r, c+r-1, dp));
        }
    }
    return dp[0][s.length()-1];
}
int main()
{
    string str = "fjaslkdflaskldfaksdjhffbgldfaksdjsdiidsaklfudibfaslfmslafksfasdhffbldfaklaskdfaksdjhffbgldfaksdjsdiidsaklfudibfaslfmslafksfasdhffbldfaklaskldfaksdjhffbgldfadfaksdjhffbgldfaksdjsdiidsaklfudibfaslfmslafksfasdhffbldfaklaskldfaksdjhffbgldfadfaksdjhffbgldfaksdjsdiidsaklfudibfaslfmslafksfasdhffbldfaklaskldfaksdjhffbgldfadfaksdjhffbgldfaksdjsdiidsaklfudibfaslfmslafksfasdhffbldfaklaskldfaksdjhffbgldfadfaksdjhffbgldfaksdjsdiidsaklfudibfaslfmslafksfasdhffbldfaklaskldfaksdjhffbgldfadfaksdjhffbgldfaksdjsdiidsaklfudibfaslfmslafksfasdhffbldfaklaskldfaksdjhffbgldfadfaksdjhffbgldfaksdjsdiidsaklfudibfaslfmslafksfasdhffbldfaklaskldfaksdjhffbgldfadfaksdjhffbgldfaksdjsdiidsaklfudibfaslfmslafksfasdhffbldfaklaskldfaksdjhffbgldfadfaksdjhffbgldfaksdjsdiiflibherslkdflibherslkdfllaskldfaksdjhffbguibherfbjadsbfafnnsvfbjadsbfafnnsvin";
    std::cout << longestPalindromeSubseq1(str);
}