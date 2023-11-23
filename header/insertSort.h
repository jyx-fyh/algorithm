#pragma once
#include<iostream>
using std::swap;

template<class T, class cmptor>
void insertSort(T* vec, int len, cmptor cmp)
{
	for(int i = 1; i < len; i++)
	{
		for(int k = i; k > 0; k--) //k>0!!!
		{
			if(!cmp(vec[k-1], vec[k]))
				swap(vec[k-1], vec[k]);
			else
				break;
		}
	}
}
