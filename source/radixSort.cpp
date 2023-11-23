int getDigit(int num, int fig)
{
	int digit;
	for(int i = 0; i < fig; i++)
	{
		digit = num % 10;
		num /= 10;
	}
	return digit;
}

int getMax(int* arr, int len)
{
	int max = -1;
	for(int i = 0; i < len; i++)
	{
		max = max > arr[i] ? max : arr[i];
	}
	return max;
}

void radixSort(int* arr, int len)
{
	
	int* tmp = new int[len];
	int max = getMax(arr, len);
	int d = 0;
	while(max) //计算最多有几位数
	{
		max /= 10;
		d++;
	}
	for(int i = 1; i <= d; i++)
	{
		
		int count[10] = {0}; //每次count必须清空,所以直接在此处创建
		for(int k = 0; k < len; k++) //统计某位上数字出现的次数
		{
			int n = getDigit(arr[k], i);
			count[n]++;
		}

		for(int k = 1; k < 10; k++) //改为累加和
			count[k] += count[k-1];
		
		for(int k = len-1; k >= 0; k--)
		{
			int n = getDigit(arr[k], i);
			int pos = count[n] - 1;//别忘了-1 !!!!!!!!!!!!!!!
			tmp[pos] = arr[k];
			count[n]--;
		}
		for(int k = 0; k < len; k++)
			arr[k] = tmp[k];
	}
	delete[] tmp;
}
