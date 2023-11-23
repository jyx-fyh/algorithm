//
// Created by ButcherX on 23-11-16.
//

#ifndef ALGORITHM_HEAPENHANCED_H
#define ALGORITHM_HEAPENHANCED_H
#include<unordered_map>
#include<iostream>
#include<vector>
using std::vector;
using std::unordered_map;
using std::unordered_multimap;

template<class T>
struct maxHeap
{
    bool operator()(const T &a, const T &b){
        return a < b;
    }
};

template<class T, class compare = maxHeap<T>>//比较器默认大根堆
class heapGreater
{
private:
    vector<T> heap;
    unordered_multimap<T, int> indexMap;
    compare cmp;
    int count;
private:
    void swap(T& a,T& b);
    void heapInsert(int cur);
    void heapify(int cur);
public:
    heapGreater(){count = 0;}
    T pop();
    void push(const T &var);
    void remove(const T &var);
    void modify(const T &var1, const T &var2);
    T peek() {return heap[0];}
    int size() {return heap.size();}
    bool empty(){return count == 0;}
};

template<class T, class compare>
void heapGreater<T, compare>::swap(T& a,T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
    tmp = indexMap.find(a)->first;
    indexMap.find(a)->second = indexMap.find(b)->second;
    indexMap.find(b)->second = indexMap.find(tmp)->second;
}

template<class T, class compare>
void heapGreater<T, compare>::heapInsert(int cur)
{
    if (cmp(heap[(cur - 1) / 2], heap[cur]))
    {
        swap(heap[(cur - 1) / 2], heap[cur]);
        heapInsert((cur - 1) / 2);
    }
}

template<class T, class compare>
void heapGreater<T, compare>::heapify(int cur)
{
    int leftChd = cur * 2 + 1;
    if (leftChd > ((int)heap.size() - 1))//heap.size()返回的是无符号数size_t，若返回0，减1后为最大正数
        return;                          //所以必须要强制转为int
    int mIndex;
    if(leftChd + 1 < (int)heap.size())
        mIndex = cmp(heap[leftChd + 1], heap[leftChd]) ? leftChd + 1 : leftChd;
    else
        mIndex = leftChd;
    if (cmp(heap[cur], heap[mIndex]))
    {
        swap(heap[mIndex], heap[cur]);
        heapify(mIndex);
    }
}

template<class T, class compare>
void heapGreater<T, compare>::push(const T &var)
{
    heap.push_back(var);
    indexMap.emplace(var,heap.size()-1);
    heapInsert(heap.size() - 1);
    count++;
}

template<class T, class compare>
T heapGreater<T, compare>::pop()
{
    T tmp = peek();
    swap(heap[0], heap[heap.size() - 1]);
    indexMap.erase(heap[heap.size()-1]);
    heap.pop_back();
    heapify(0);
    count--;
    return tmp;
}

template<class T, class compare>
void heapGreater<T, compare>::remove(const T &var) {
    int index = indexMap.find(var)->second;
    swap(heap[index], heap[heap.size() - 1]);
    indexMap.erase(heap[heap.size() - 1]);
    heap.pop_back();
    if (index != heap.size())//当要删除的元素位于堆末尾时，pop后不再做以下操作，否则越界。
    {                        //注意此处是已经pop后的，易错写为heap.size()-1
        heapify(index);
        heapInsert(index);//两个只会执行其中一个
    }
    count--;
}

template<class T, class compare>
void heapGreater<T, compare>::modify(const T &var1, const T &var2)
{
    int index = indexMap.find(var1)->second;
    heap[index] = var2;
    indexMap.erase(var1);
    indexMap.emplace(var2, index);
    heapify(index);
    heapInsert(index);
}
#endif //ALGORITHM_HEAPENHANCED_H
