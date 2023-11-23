//
// Created by ButcherX on 23-11-14.
//
#include"../header/graph.h"
#include<iostream>
#include<queue>
#include<list>
#include<unordered_set>
using std::priority_queue;
using std::list;
using std::unordered_set;
struct cmp
{
    bool operator()(graphEdge* a, graphEdge* b)
    {
        return a->weight > b->weight;
    }
};
list<graphEdge*> prim(graph _graph)
{
    unordered_set<graphNode*> unlockedNodes;
    priority_queue<graphEdge*, vector<graphEdge*>, cmp> unlockedEdges;
    list<graphEdge*> ret;
    graphNode* node;
    graphEdge* edge;
    for(auto n : _graph.nodes)
    {
        node = n.second;
        if(unlockedNodes.find(node) != unlockedNodes.end())
            continue;
        unlockedNodes.emplace(node);
        for(auto e : node->edges)
            unlockedEdges.push(e);
        while(!unlockedEdges.empty())
        {
            edge = unlockedEdges.top();
            unlockedEdges.pop();
            if(unlockedNodes.find(edge->to) == unlockedNodes.end())
            {
                unlockedNodes.emplace(edge->to);
                ret.push_back(edge);
                for(auto e : edge->to->edges)
                    unlockedEdges.push(e);
            }
        }
    }
    return ret;
}
int main()
{
    vector<vector<int>> vec = {
            {3, 'a', 'b'},
            {3, 'b', 'a'},
            {1, 'a', 'c'},
            {1, 'c', 'a'},
            {1, 'b', 'c'},
            {1, 'c', 'b'},
            {10, 'b', 'e'},
            {10, 'e', 'b'},
            {2, 'c', 'e'},
            {2, 'e', 'c'},
            {50, 'c', 'f'},
            {50, 'f', 'c'},
            {1, 'e', 'g'},
            {1, 'g', 'e'},
            {6, 'f', 'h'},
            {6, 'h', 'f'},
            {3, 'f', 'g'},
            {3, 'g', 'f'},
            {9, 'g', 'h'},
            {9, 'h', 'g'}
    };
    graph gra = graphAdaptor(vec);
    auto ret = prim(gra);
    for(auto e : ret)
        std::cout << e->weight << std::endl;
    
}