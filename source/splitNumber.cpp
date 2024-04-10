//
// Created by ButcherX on 23-12-1.
//
#include<vector>
#include<iostream>
using std::vector;
int process(vector<int> vec, int left, int right)
{
    int ways = 0;
    for(int i = left; i < right; i++)
    {
        if(vec[right] < vec[right+1])
        {
            vec[right]++;
            vec[i]--;
            ways += process(vec, i + 1, right - 1);
            ways++;
        }
        else
            break;
    }

    return ways;
}

int splitNumber(int number)
{
    vector<int> vec(number + 1, 1);
    vec[number] = INT32_MAX;
    int ret = process(vec, 0, number - 1);
    return ret + 1;//vec全为1也算1种,所以+1
}
//=============================================================











int main()
{
//    std::cout<<splitNumber(7) << std::endl;
    std::cout<<dp2(9) << std::endl;
    std::cout<<process1(8, 9) << std::endl;
}