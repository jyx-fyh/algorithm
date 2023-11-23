//
// Created by ButcherX on 23-11-15.
//
#include"../header/heapEnhanced.h"
#include"../header/graph.h"
struct wrap
{
    graphNode* node;
    int dis;
    wrap(graphNode* _node, int _dis):node(_node), dis(_dis){}
};

struct cmptor
{
    bool operator()(const wrap* a, const wrap* b) {
        return a->dis > b->dis;//小顶堆
    }
};

void addOrUpdateOrIgnore(heapGreater<wrap*, cmptor> &heap, unordered_map<graphNode*, wrap*> &help, graphNode* node, int dis)
{
    if(help.find(node) == help.end())
    {
        wrap* wp = new wrap(node, dis);
        heap.push(wp);
        help.emplace(node, wp);
    }
    else
    {
        wrap* wp = help.find(node)->second;
        if(wp->dis > dis)
        {
            wp->dis = dis;
            heap.modify(wp, wp);
        }
    }
}

unordered_map<graphNode*, int> disMap(graphNode* node)
{
    unordered_map<graphNode*, int> retMap;
    unordered_map<graphNode*, wrap*> help;
    heapGreater<wrap*, cmptor> heap;
    wrap* nd = new wrap(node, 0);
    heap.push(nd);
    help.emplace(node, nd);
    while(!heap.empty())
    {
        nd = heap.pop();
        retMap.emplace(nd->node, nd->dis);
        for(auto edge : nd->node->edges)
        {
            addOrUpdateOrIgnore(heap, help, edge->to, nd->dis + edge->weight);
        }
    }
    for(auto n : help)
        delete n.second;
    return retMap;
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
    auto startNode =gra.nodes['a'];
    auto map = disMap(startNode);
    char ch;
    for(auto n : map)
    {
        ch = n.first->value;
        std::cout << "node: " << ch << " distance: " << n.second << std::endl;
    }
}




















