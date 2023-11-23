#pragma once
#include<iostream>
using std::swap;

template<class T, class cmptor>
void selectSort(T* vec, int len, cmptor cmp)
{
	int mIndex;
	for(int i = 0; i < len-1; i++)
	{
		mIndex = i;
		for(int k = i + 1; k < len; k++)
		{
			if(!cmp(vec[mIndex], vec[k])) 
				mIndex = k;
		}
		swap(vec[i], vec[mIndex]);
	}
}
