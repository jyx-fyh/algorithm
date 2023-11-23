#pragma once
template<class T, class cmptor>
void merge(T* vec, int left, int mid, int right, cmptor cmp)
{
	T* tmp = new T[right-left+1];
	int lp = left;
	int rp = mid + 1;
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
void process(T* vec, int left, int right, cmptor cmp)
{
	if(left >= right) //base line 放在process中而非merge中
		return;
	int mid = left + ((right - left) >> 1);//注意括号！+优先于>>
	process(vec, left, mid, cmp);
	process(vec, mid+1, right, cmp);
	merge(vec, left, mid, right, cmp);
}


template<class T, class cmptor>
void mergeSort(T* vec, int len, cmptor cmp)
{
	if(vec == nullptr || len <= 1)
		return;
	process(vec, 0, len-1, cmp);
}
