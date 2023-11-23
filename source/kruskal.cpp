//
// Created by ButcherX on 23-11-13.
//
#include<vector>
#include"../header/UnionFind.h"
#include"../header/graph.h"
#include<queue>
using std::priority_queue;
using std::vector;
struct cmp
{
    bool operator()(graphEdge* a, graphEdge* b)
    {
        return a->weight > b->weight;
    }
};
unordered_set<graphEdge*> kruskal(const graph &_graph)
{
    unordered_set<graphEdge*> ret;
    list<graphNode*> listNode;
    for(auto n : _graph.nodes)
        listNode.push_back(n.second);
    UnionFind<graphNode*> uf(listNode);
    priority_queue<graphEdge*, vector<graphEdge*>, cmp> queEdge;
    for(auto n : _graph.edges)
        queEdge.push(n);
    graphEdge* tmp;
    while(!queEdge.empty())
    {
        tmp = queEdge.top();
        queEdge.pop();
        if(!uf.isSameSet(tmp->to, tmp->from))
        {
            ret.emplace(tmp);
            uf.Union(tmp->from, tmp->to);
        }
    }
    return ret;
}

int main()
{
    vector<vector<int>> vec = {
            {3, 'a', 'b'},
            {1, 'a', 'c'},
            {1, 'b', 'c'},
            {10, 'b', 'e'},
            {2, 'c', 'e'},
            {50, 'c', 'f'},
            {1, 'e', 'g'},
            {6, 'f', 'h'},
            {3, 'f', 'g'},
            {9, 'g', 'h'}
    };
    graph gra = graphAdaptor(vec);
    auto ret = kruskal(gra);
    for(auto e : ret)
        std::cout << e->weight << std::endl;
}
