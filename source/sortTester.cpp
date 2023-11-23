//
// Created by ButcherX on 23-10-30.
//
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include "../header/sortTester.h"
using std::sort;
using std::cout;
using std::endl;


int* generateRandomArray(int maxVar, int len)
{
    if(maxVar <= 0 || len <= 0)
        return nullptr;
    int *arr = new int[len];
    for(int i = 0; i < len; i++)
    {
        arr[i] = rand() % maxVar;
    }
    return arr;
}

int* cpyArr(int* arr, int len)
{
    if(arr == nullptr || len <= 0)
        return nullptr;
    int* cpy = new int[len];
    for(int i = 0; i < len; i++)
    {
        cpy[i] = arr[i];
    }
    return cpy;
}

bool isEqual(int* arr1, int* arr2, int len)
{
    for(int i = 0; i < len; i++)
    {
        if(arr1[i] != arr2[i])
            return false;
    }
    return true;
}

void sortTester(void (*func)(int*, int, cmptor), int times, int maxVar, int maxLen)
{
    srand(time(nullptr));
    int len;
    for(int i = 0; i < times; i++)
    {
        len = rand() % maxLen;
        int* arr = generateRandomArray(maxVar, len);
        int* cpy = cpyArr(arr, len);
        int* cpy1 = cpyArr(arr, len);
        sort(arr, &arr[len], [](int a, int b){return a < b;});
        func(cpy, len, [](int a, int b){return a<b;});
        if(!isEqual(arr, cpy, len))
        {
            cout<< "wrong...." << endl << "original:" << endl;
            for(int i = 0; i < len; i++)
                cout<< cpy1[i] << " ";
            cout<< "wrong instance:" << endl;
            for(int i = 0; i < len; i++)
                cout<< cpy[i] << " ";
            cout<< endl;
            return;
        }
        cout<< "success" << endl;
        delete[] cpy;
        delete[] arr;
    }
}



void sortFunc1(int* data, int dataSize) {
    // 在这里实现排序函数1的逻辑
    //sort(data, &data[dataSize], [](int a, int b){return a<b;});
}

// 测试排序时间的函数
double testSortingTime(void (*sortFunc)(int*, int), int numComparisons, int dataSize, int maxValue) {
    int* data = new int[dataSize];
    // 生成随机数据
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, maxValue);
    for (int i = 0; i < dataSize; ++i) {
        data[i] = dis(gen);
    }

    // 测试排序函数的排序时间
    auto startTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numComparisons; ++i) {
        int* sortedData = new int[dataSize];
        std::copy(data, data + dataSize, sortedData);
        sortFunc1(sortedData, dataSize);
        delete[] sortedData;
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    double sortingTime1 = std::chrono::duration<double>(endTime - startTime).count();
    // 删除动态分配的数组
    delete[] data;
    // 返回排序时间结果
    return sortingTime1;
}

