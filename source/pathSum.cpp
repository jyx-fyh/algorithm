//
// Created by ButcherX on 24-1-2.
//
#include<vector>
#include<climits>
#include<iostream>
using std::vector;
int process(const vector<vector<int>> &matrix, int x, int y)
{
    if(x >= matrix[0].size() || y >= matrix.size())
        return INT_MAX;
    if(x == matrix[0].size() - 1 && y == matrix.size() - 1)
        return matrix[y][x];//可别写成了[x][y]
    int down = process(matrix, x, y + 1);
    int right= process(matrix, x + 1, y);
    return matrix[y][x] + std::min(down, right);
}
int minPathSum(const vector<vector<int>> &matrix)
{
    return process(matrix, 0, 0);
}
///========================================================
int help(const vector<vector<int>> &matrix, const vector<vector<int>> &dp, int x, int y)
{
    if(x >= matrix[0].size() || y >= matrix.size())
        return INT_MAX;
    if(x == matrix[0].size() - 1 && y == matrix.size() - 1)
        return matrix[y][x];
    return dp[y][x];
}
int minPathSum1(const vector<vector<int>> &matrix)
{
    vector<vector<int>> dp(matrix[0].size(), vector<int>(matrix.size(), 0));
    for(int r = matrix.size() - 1; r >= 0; r--)
    {
        for(int c = matrix[0].size() - 1; c >= 0; c--)
        {
            int down = help(matrix, dp, c, r + 1);
            int right= help(matrix, dp, c + 1, r);
            dp[r][c] = matrix[r][c] + std::min(down, right);
        }
    }
    return dp[0][0];
}
///===========================================================

int minPathSum2(const vector<vector<int>> &matrix)
{
    int row = matrix.size() - 1;
    int col = matrix[0].size() - 1;
    vector<int> dp(matrix[0].size(), 0);
    dp[col] = matrix[row][col];
    for(int c = col - 1; c >= 0; c--)
    {
        dp[c] = matrix[row][c] + dp[c+1];
    }
    for(int r = row - 1; r >= 0; r--)
    {
        for(int c = col; c >= 0; c--)
        {
            dp[c] = matrix[r][c] + std::min(dp[c], c == col ? INT_MAX : dp[c+1]);
        }
    }
    return dp[0];
}

int main()
{
    vector<vector<int>> matrix = {
            {21,61,31,18},
            {51,28,63,75},
            {76,52,32,47},
            {12,32,35,24}
    };
    std::cout<< minPathSum(matrix) << std::endl;
    std::cout<< minPathSum1(matrix) << std::endl;
    std::cout<< minPathSum2(matrix) << std::endl;

}