//
// Created by ButcherX on 24-1-3.
//
#include<vector>
#include<iostream>
using std::vector;
int process(const vector<int> &coins, int rest, int index)
{
    if(rest == 0)//必须放在下一个if之前,因为可能刚好拿走最后一个硬币时,rest变为0
        return 1;
    if(index >= coins.size() || rest < 0)
        return 0;
    int ret1 = process(coins, rest, index + 1);
    int ret2 = process(coins, rest - coins[index], index + 1);
    return ret1 + ret2;
}
int coins1(const vector<int> &coins, int aim)
{
    return process(coins, aim, 0);
}
//======================================
int help(const vector<int> &coins, const vector<vector<int>> &dp, int rest, int index)
{
    if(rest == 0)
        return 1;
    if(index >= coins.size() || rest < 0)
        return 0;
    return dp[rest][index];
}
int coins2(const vector<int> &coins, int aim)
{
    vector<vector<int>> dp(aim + 1, vector<int>(coins.size(), 0));
    for(int r = 0; r <= aim; r++)
    {
        for(int i = coins.size() - 1; i >= 0; i--)
        {
            int ret1 = help(coins, dp, r, i + 1);
            int ret2 = help(coins, dp, r - coins[i], i + 1);
            dp[r][i] = ret1 + ret2;
        }
    }
    return dp[aim][0];
}
int dp(vector<int> arr, int aim) {
    if (aim == 0) {
        return 1;
    }
    int N = arr.size();
    vector<vector<int>> dp(N + 1, vector<int>(aim + 1, 0));
    dp[N][0] = 1;
    for (int index = N - 1; index >= 0; index--) {
        for (int rest = 0; rest <= aim; rest++) {
            dp[index][rest] = dp[index + 1][rest] + (rest - arr[index] >= 0 ? dp[index + 1][rest - arr[index]] : 0);
        }
    }
    return dp[0][aim];
}
int main()
{
    vector<int> coins = {1, 2, 1, 3, 5, 2, 1, 4, 2, 4, 6, 8, 4, 9, 4, 6, 8, 7};
    std::cout << coins1(coins, 30) << std::endl;
    std::cout << coins2(coins, 30) << std::endl;
    std::cout << dp(coins, 30) << std::endl;

}