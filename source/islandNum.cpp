//
// Created by ButcherX on 23-11-5.
//
//方法一：并查集
#include<vector>
using std::vector;
class UnionFind {
public:
    UnionFind(vector<vector<char>>& grid)
    {
        counts = 0;
        int r = grid.size();
        int c = grid[0].size();
        parent.resize(r*c);
        size.resize(r*c, 0);
        for (int i = 0; i < r*c; i++)
        {
            parent[i] = i;
            size[i] = 1;
        }
        for (int i = 0; i < r; i++)
        {
            for(int k = 0; k < c; k++)
            {
                if(grid[i][k] == '1')
                    counts++;
            }
        }
    }

    int find(int x)
    {
        int anc = x;
        int tmp;
        while(anc != parent[anc])
            anc = parent[anc];
        while(x != anc)
        {
            tmp = x;
            x = parent[x];
            parent[tmp] = anc;
        }
        return anc;
    }

    void unite(int x, int y)
    {
        int px = find(x);
        int py = find(y);
        if (px == py)
            return;
        if (size[px] < size[py])
        {
            parent[px] = py;
            size[py] += size[px];
            size[px] = 0;
        }
        else
        {
            parent[py] = px;
            size[px] += size[py];
            size[py] = 0;
        }
        counts--;
    }
    bool isSameSet(int x, int y)
    {
        return find(x) == find(y);
    }
    int count()
    {
        return counts;
    }

private:
    vector<int> parent;
    vector<int> size;
    int counts;
};

int numIslands(vector<vector<char>>& grid)
{
    UnionFind uf(grid);
    int r = grid.size();
    int c = grid[0].size();
    for(int i = 0; i < r; i++)
    {
        for(int k = 0; k < c; k++)
        {
            if(i - 1 >= 0 && grid[i][k] == '1' && grid[i-1][k] == '1')
                uf.unite(i * c + k, i * c + k - c);
            if(k - 1 >= 0 && grid[i][k] == '1' && grid[i][k-1] == '1')
                uf.unite(i * c + k, i * c + k - 1);
        }
    }
    return uf.count();
}
//方法二：感染

