//
// Created by ButcherX on 23-11-5.
//
#include"../header/UnionFind.h"
int findCircleNum(vector<vector<int>>& isConnected)
{
    UnionFind uf(isConnected.size());
    for(int i = 0; i < isConnected.size() - 1; i++)
    {
        for(int k = i + 1; k < isConnected.size(); k++)//只用看主对角线上方
        {
            if(isConnected[i][k] == 1)
            {
                uf.unite(i,k);
            }
        }
    }
    return uf.count();

}
