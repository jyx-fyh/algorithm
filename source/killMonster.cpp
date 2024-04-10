//
// Created by ButcherX on 23-11-30.
//
#include<iostream>
#include<vector>
#include<cmath>
using std::vector;
double process(int hurt, int restHit, int restBlood)
{
    if(restHit <= 0)
    {
        if(restBlood <= 0)
            return 1;
        else
            return 0;
    }
    if(restBlood <= 0)
        return pow(hurt + 1, restHit);
    double die = 0;
    for(int h = 0; h <= hurt; h++)
    {
        die += process(hurt, restHit - 1, restBlood - h);
    }
    return die;
}

double killMonster(int blood, int hurt, int hitTime)
{
    double all = pow(hurt + 1, hitTime);
    double die = process(hurt, hitTime, blood);
    return die / all;
}
///================================================================
double help(int restHit, int restBlood, int hurt, const vector<vector<double>> &dp)
{
    if(restHit <= 0)
    {
        if(restBlood <= 0)
            return 1;
        else
            return 0;
    }
    if(restBlood <= 0)
        return pow(hurt + 1, restHit);
    return dp[restHit][restBlood];
}
double killMonster1(int blood, int hurt, int hitTime)
{
    vector<vector<double>> dp(hitTime + 1, vector<double>(blood + 1, 0));
    for(int r = 0; r <= hitTime; r++)
    {
        for(int c = 0; c <= blood; c++)
        {
            double die = 0;
            for(int h = 0; h <= hurt; h++)
            {
                die += help(r-1, c-h, hurt, dp);
            }
            dp[r][c] = die;
        }
    }
    return dp[hitTime][blood] / pow(hurt + 1, hitTime);
}
///===================================================
double killMonster2(int blood, int hurt, int hitTime)
{
    vector<vector<double>> dp(hitTime + 1, vector<double>(blood + 1, 0));
    for(int r = 0; r <= hitTime; r++)
    {
        for(int c = 0; c <= blood; c++)
        {
            dp[r][c] = help(r, c-1, hurt, dp) + help(r-1, c, hurt, dp) - help(r-1 ,c-hurt-1, hurt, dp);
        }
    }
    return dp[hitTime][blood] / pow(hurt + 1, hitTime);
}
///====================================================
double help1(int restHit, int restBlood, int hurt, const vector<vector<double>> &dp)
{
    if(restHit <= 0)
    {
        if(restBlood > 0)
            return 1;
        else
            return 0;
    }
    if(restBlood <= 0)
        return 0;
    return dp[restHit][restBlood];
}
double killMonster3(int blood, int hurt, int hitTime)
{
    vector<vector<double>> dp(hitTime + 1, vector<double>(blood + 1, 0));
    for(int r = 0; r <= hitTime; r++)
    {
        for(int c = 0; c <= blood; c++)
        {
            dp[r][c] = help1(r, c-1, hurt, dp) + help1(r-1, c, hurt, dp) - help1(r-1 ,c-hurt-1, hurt, dp);
        }
    }
    return 1 - dp[hitTime][blood] / pow(hurt + 1, hitTime);
}

int main()
{
    std::cout << killMonster1(30, 10, 7) << std::endl;
    std::cout << killMonster3(30, 10, 7) << std::endl;

}
