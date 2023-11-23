//
// Created by ButcherX on 23-11-5.
//

#ifndef ALGORITHM_UNIONFIND_H
#define ALGORITHM_UNIONFIND_H
#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<list>
#include <vector>
//using std::vector;
//class UnionFind {
//public:
//    UnionFind(int n)
//    {
//        counts = n;
//        parent.resize(n);
//        size.resize(n, 0);
//        for (int i = 0; i < n; i++)
//        {
//            parent[i] = i;
//            size[i] = 1;
//        }
//    }
//
//    int find(int x)
//    {
//        //fix：如果没有x，仍然返回x
//        int anc = x;
//        int tmp;
//        while(anc != parent[anc])
//            anc = parent[anc];
//        while(x != anc)//路径压缩
//        {
//            tmp = x;
//            x = parent[x];
//            parent[tmp] = anc;
//        }
//        return anc;
//    }
//
//    void unite(int x, int y)
//    {
//        int px = find(x);
//        int py = find(y);
//        if (px == py)
//            return;
//        if (size[px] < size[py])//按大小合并
//        {
//            parkkent[px] = py;
//            size[py] += size[px];
//            size[px] = 0;
//        }
//        else
//        {
//            parent[py] = px;
//            size[px] += size[py];
//            size[py] = 0;
//        }
//        counts--;
//    }
//    bool isSameSet(int x, int y)
//    {
//        return find(x) == find(y);
//    }
//    int count()
//    {
//        return counts;
//    }
//
//private:
//    vector<int> parent;
//    vector<int> size;
//    int counts;
//};
using std::list;
using std::unordered_map;
using std::unordered_set;

template<class T>
class UnionFind
{
    unordered_map<T, T> parentMap;
    unordered_map<T, int> sizeMap;
public:
    UnionFind(const list<T> &nodeList);
    T Find(T obj);
    void Union(T obj1, T obj2);
    bool isSameSet(T obj1, T obj2);
};

template<class T>
UnionFind<T>::UnionFind(const list<T> &nodeList)
{
    for(auto n : nodeList)
    {
        parentMap.emplace(n, n);
        sizeMap.emplace(n, 1);
    }
}

template<class T>
T UnionFind<T>::Find(T obj)
{
    if(parentMap.find(obj) == parentMap.end())
    {
        std::cout << "错误参数..." << std::endl;
        exit(-1);
    }
    T anc = obj;
    while(anc != parentMap[anc])
        anc = parentMap[anc];
    T tmp;
    while(obj != anc)
    {
        tmp = parentMap[obj];
        if(tmp != anc)
            parentMap[obj] = anc;
        obj = tmp;
    }
    return anc;
}

template<class T>
void UnionFind<T>::Union(T obj1, T obj2)
{
    T obj1p = Find(obj1);
    T obj2p = Find(obj2);
    if(obj1 == obj2)
        return;
    if(sizeMap[obj1p] > sizeMap[obj2p])
    {
        parentMap[obj2p] = obj1p;
        sizeMap[obj1p]++;
    }
    else
    {
        parentMap[obj1p] = obj2p;
        sizeMap[obj2p]++;
    }
}

template<class T>
bool UnionFind<T>::isSameSet(T obj1, T obj2)
{
    if(Find(obj1) == Find(obj2))
        return true;
    else
        return false;
}

#endif //ALGORITHM_UNIONFIND_H
