#pragma once
#include<iostream>
using std::swap;
template<class T, class cmptor>
void bubbleSort(T* vec, int len, cmptor cmp)
{
	for(int i = 0; i < len-1; i++)
	{

	for(int k = 0; k < len-1-i; k++)
		{
			if(!cmp(vec[k], vec[k+1]))
				swap(vec[k], vec[k+1]);
		}

	}
}
