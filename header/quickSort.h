#pragma once
#include<iostream>
using std::swap;
struct loc
{
	int left;
	int right;
};

template<class T, class cmptor>
loc netherLandFlag(T* vec, int left, int right, cmptor cmp)
{
	loc bound;
	int N = vec[right-1];
	int ptr = left + 1;
	while(ptr < right)
	{
		if(cmp(vec[ptr], N)) //vec[ptr]和N顺序不可反,否则排序反
			swap(vec[++left], vec[ptr++]); //注意ptr++
		else if(vec[ptr] == N)
			ptr++;
		else
			swap(vec[--right], vec[ptr]); //此处没有ptr--!!!!!!!!!!!!!
	}
	bound.left = left;
	bound.right = right;
	return bound;
}

template<class T, class cmptor>
void process(T* vec, int left, int right, cmptor cmp)
{
	if(right - left == 1) //当right-left==1时,说明该区间已经没有数了
		return;
	loc bound = netherLandFlag(vec, left, right, cmp);
	process(vec, left, bound.left + 1, cmp);//参数意义是开区间,所以此处必须+1,下面同理!!!!!!
	process(vec, bound.right - 1, right, cmp);
}


template<class T, class cmptor>
void quickSort(T* vec, int len, cmptor cmp)
{
	if(vec == NULL || len <= 1) 
		return;
	process(vec, -1, len, cmp);
}
