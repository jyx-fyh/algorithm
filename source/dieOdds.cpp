//
// Created by ButcherX on 23-11-30.
//
#include<vector>
#include<iostream>
#include<cmath>
using std::vector;

double process(int row, int col, int rest, int N, int M)
{
    if (row < 0 || row == N || col < 0 || col == M)
        return 0;
    if (rest == 0)
        return 1;
    double up   = process(row - 1, col, rest - 1, N, M);
    double down = process(row + 1, col, rest - 1, N, M);
    double left = process(row, col - 1, rest - 1, N, M);
    double right= process(row, col + 1, rest - 1, N, M);
    return up + down + left + right;
}

double livePosibility1(int row, int col, int k, int N, int M) {
    return 1 - process(row, col, k, N, M) / pow(4, k);
}


double help(vector<vector<vector<double>>>& dp, int N, int M, int r, int c, int rest) {
    if (r < 0 || r == N || c < 0 || c == M) {
        return 0;
    }
    if (rest == 0)
        return 1;
    return dp[r][c][rest];
}
double livePosibility2(int row, int col, int k, int N, int M) {
    vector<vector<vector<double>>> dp(N, vector<vector<double>>(M, vector<double>(k + 1, 0)));


    for (int rest = 1; rest <= k; rest++)
    {
        for (int r = 0; r < N; r++)
        {
            for (int c = 0; c < M; c++)
            {
                dp[r][c][rest] =  help(dp, N, M, r - 1, c, rest - 1);
                dp[r][c][rest] += help(dp, N, M, r + 1, c, rest - 1);
                dp[r][c][rest] += help(dp, N, M, r, c - 1, rest - 1);
                dp[r][c][rest] += help(dp, N, M, r, c + 1, rest - 1);
            }
        }
    }

    return 1 - (double)dp[row][col][k] / pow(4, k);
}




int main()
{
    std::cout << livePosibility1(4, 4, 10, 8, 8) << std::endl;
    std::cout << livePosibility2(4, 4, 15, 30, 30) << std::endl;
    return 0;
}