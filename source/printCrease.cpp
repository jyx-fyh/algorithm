//
// Created by ButcherX on 23-11-3.
//
//fold times-n, current layer-cur, direction-dir(false-down, true-up)
#include<iostream>
void process(int n, int cur, bool dir)
{
    if(cur > n)
        return;
    process(n, cur + 1, false);
    std::cout << (dir ? "up " : "down ");
    process(n, cur + 1, true);
}

void fold(int n)
{
    if(n < 1)
        return;
    process(n, 1, false);
}

int main()
{
    fold(3);
}
