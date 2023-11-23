//
// Created by ButcherX on 23-11-17.
//
#include<stack>
using std::stack;
void process(stack<int> &stk, int topNum, int cur, int bottom)
{
    if(cur == bottom)
    {
        stk.push(topNum);
        return;
    }
    int tmp = stk.top();
    stk.pop();
    process(stk, topNum, cur + 1, bottom);
    stk.push(tmp);
}

void reverse(stack<int> &stk)
{
    for(int i = 0; i < stk.size(); i++)
    {
        process(stk, stk.top(), 0, stk.size() - i);
        stk.pop();
    }
}