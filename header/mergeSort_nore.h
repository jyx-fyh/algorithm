#pragma once
template<class T, class cmptor>
void merge(T* vec, int left, int mid, int right, cmptor cmp)
{
	T* tmp = new T[right-left+1];
	int lp = left;
	int rp = mid+1;
	int i = 0;
	while(lp <= mid && rp <= right)
		cmp(vec[lp], vec[rp]) ? tmp[i++]=vec[lp++] : tmp[i++]=vec[rp++];
	while(lp <= mid)
		tmp[i++] = vec[lp++];
	while(rp <= right)
		tmp[i++] = vec[rp++];
	for(int k = 0; k < right-left+1; k++)
		vec[left+k] = tmp[k];
	delete[] tmp;

}

template<class T, class cmptor>
void mergeSort(T* vec, int len, cmptor cmp)
{
	if(vec == nullptr || len <= 1)
		return;
	int mergeSize, left, right, mid;
	mergeSize = 1;

	while(mergeSize < len)//!!!
	{
		left = 0;//!!
		while(true)//!!
		{
			mid = left + mergeSize -1;
			if(mid >= len-1)//!!
				break;
			right = (mid + mergeSize) <  (len - 1) ? (mid + mergeSize) : (len - 1);
			merge(vec, left, mid, right, cmp);
			left = right + 1;
		}
		if (mergeSize > len / 2)//防止整形溢出
			break;
		mergeSize *= 2; //!!
	}
}
