#pragma once
#include<iostream>
using std::swap;
template<class T, class cmptor>
void shell(T* vec, int len, cmptor cmp)
{
    if(vec == NULL || len <= 1)
        return;
    for(int g = len/2; g > 0; g /= 2)
    {
        for(int i = g; i < len; i += g)
        {
            for(int k = i; k > 0; k -= g) //k>0!!!
            {
                if(!cmp(vec[k-g], vec[k]))
                    swap(vec[k], vec[k-g]);
                else
                    break;
            }
        }
    }
}