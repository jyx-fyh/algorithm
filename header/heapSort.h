//
// Created by ButcherX on 23-10-30.
//

#ifndef ALGORITHM_HEAPSORT_H
#define ALGORITHM_HEAPSORT_H
#include <iostream>
template<class T, class cmptor>
void heapInsert(T* vec, int cur, cmptor cmp)
{
    if((cur-1)/2 < 0)
        return;
    if(!cmp(vec[(cur-1)/2], vec[cur]))
    {
        swap(vec[(cur-1)/2], vec[cur]);
        heapInsert(vec, (cur-1)/2, cmp);
    }
}

template<class T, class cmptor>
void heaplify(T* vec, int cur, int len, cmptor cmp)
{
    if(cur * 2 + 1 >= len)
        return;
    int m;
    if(cur * 2 + 2 >= len)
        m = cur * 2 + 1;
    else
        m = cmp(vec[cur*2+1], vec[cur*2+2]) ? cur*2+1 : cur*2+2;

    if(!cmp(vec[cur], vec[m]))
    {
        swap(vec[cur], vec[m]);
        heaplify(vec, m, len, cmp);/**易错,别写在外面了!!!!**/
    }
}

template<class T, class cmptor>
void createHeapByHeaplify(T* vec, int len, cmptor cmp)
{
    if(vec == nullptr || len <= 1)
        return;
    for(int i = len - 1; i >= 0; i--)
        heaplify(vec, i, len, cmp);
}


template<class T, class cmptor>
void createHeapByInsert(T* vec, int len, cmptor cmp)
{
    if(vec == nullptr || len <= 1)
        return;
    for(int i = 0; i < len; i++)
        heapInsert(vec, i, cmp);
}


template<class T, class cmptor>
void heapSort(T* vec, int len, cmptor cmp)
{
    if(vec == nullptr || len <= 1)
        return;

    auto cmp_in = [cmp](int a, int b){return !cmp(a, b);};
    createHeapByInsert(vec, len, cmp_in);
    for (int i = 0; i < len; i++)
    {
        std::swap(vec[0], vec[len - 1 - i]);
        heaplify(vec, 0, len - i - 1, cmp_in);/**易错,别写在外面了!!!!**/
    }
}

#endif //ALGORITHM_HEAPSORT_H
