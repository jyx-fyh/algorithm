//
// Created by ButcherX on 23-11-28.
//
#include<vector>
#include<iostream>
using std::vector;
//y轴0~9，x轴0~8
//暴力递归，和robotWalk完全类似
int process(int x, int y, int rest, int a, int b)
{
    if (x < 0 || x > 9 || y < 0 || y > 8)
        return 0;
    if (rest == 0)
        return (x == a && y == b) ? 1 : 0;
    int ways = 0;
    ways += process(x + 2, y + 1, rest - 1, a, b);
    ways += process(x + 1, y + 2, rest - 1, a, b);
    ways += process(x - 1, y + 2, rest - 1, a, b);
    ways += process(x - 2, y + 1, rest - 1, a, b);
    ways += process(x - 2, y - 1, rest - 1, a, b);
    ways += process(x - 1, y - 2, rest - 1, a, b);
    ways += process(x + 1, y - 2, rest - 1, a, b);
    ways += process(x + 2, y - 1, rest - 1, a, b);
    return ways;
}
//====================================================================
//动态规划
int pick(vector<vector<vector<int>>> &dp, int x, int y, int rest)
{
    if (x < 0 || x > 9 || y < 0 || y > 8)
        return 0;
    return dp[x][y][rest];
}
int dp(int a, int b, int k) {
    vector<vector<vector<int>>> dp(10, vector<vector<int>>(9, vector<int>(k + 1, 0)));//注意是k+1
    dp[a][b][0] = 1;
    for (int rest = 1; rest <= k; rest++) {
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 9; y++) {
                int ways = pick(dp, x + 2, y + 1, rest - 1);
                ways += pick(dp, x + 1, y + 2, rest - 1);
                ways += pick(dp, x - 1, y + 2, rest - 1);
                ways += pick(dp, x - 2, y + 1, rest - 1);
                ways += pick(dp, x - 2, y - 1, rest - 1);
                ways += pick(dp, x - 1, y - 2, rest - 1);
                ways += pick(dp, x + 1, y - 2, rest - 1);
                ways += pick(dp, x + 2, y - 1, rest - 1);
                dp[x][y][rest] = ways;
            }
        }
    }
    return dp[0][0][k];
}

int horseWalk(int x, int y, int steps)
{
    return dp(x, y, steps);
}

int main()
{
    std::cout << horseWalk(4, 5, 5);
}