//
// Created by ButcherX on 23-11-9.
//
#include"../header/graph.h"
#include<iostream>
#include<queue>
#include<stack>
using std::stack;
using std::queue;
using std::list;
//法1：入度
list<graphNode*> topologySort(const graph& gra)
{
    list<graphNode*> result;
    queue<graphNode*> zero_in;
    unordered_map<graphNode*, int> map_in;
    graphNode* tmp;
    int counter = 0;
    for(auto n : gra.nodes)
        map_in.emplace(n.second, n.second->in);
    for(auto n : gra.nodes)
    {
        if (n.second->in == 0)
            zero_in.push(n.second);
    }
    while(!zero_in.empty())
    {
        tmp = zero_in.front();
        zero_in.pop();
        counter++;
        result.push_back(tmp);
        for(auto n : tmp->nexts)
        {
            map_in[n]--;
            if(map_in.at(n) == 0)
                zero_in.push(n);
        }
    }
    if(counter != gra.nodes.size())
    {
        std::cout<<"图中存在环,无法进行拓扑排序..."<<std::endl;
        exit(-1);
    }
    return result;
}

//方法2：深度优先遍历
void DFS(graphNode* node, unordered_set<graphNode*>& visited
         ,unordered_set<graphNode*> visitedInPath, stack<graphNode*>& stk)
{
    if(visitedInPath.find(node) != visitedInPath.end())
    {
        std::cout<<"图中存在环,无法进行拓扑排序..."<<std::endl;
        exit(-1);
    }
    if(visited.find(node) != visited.end())
        return;
    visited.emplace(node);
    visitedInPath.emplace(node);
    for(auto n : node->nexts)
        DFS(n, visited, visitedInPath, stk);
    stk.push(node);
}

list<graphNode*> topologicalSort(const graph &g)
{
    stack<graphNode*> stk;
    list<graphNode*> ret;
    std::unordered_set<graphNode*> visitedInPath;
    unordered_set<graphNode*> visited;
    for (auto it : g.nodes)
        DFS(it.second, visited, visitedInPath, stk);
    while(!stk.empty())
    {
        ret.push_back(stk.top());
        stk.pop();
    }
    return ret;
}
//
//int main()
//{
//    vector<vector<int>> nodes = {{0,1,2},
//                                 {0,1,5},
//                                 {0,1,6},
//                                 {0,1,7},
//                                 {0,2,3},
//                                 {0,3,4},
//                                 {0,6,5}};
//
//    graph gra = graphAdaptor(nodes);
//    auto ret1 = topologicalSort(gra);
//    auto ret2 = topologySort(gra);
//    for(auto n : ret1)
//        std::cout << n->value << ", ";
//    std::cout << std::endl;
//    for(auto n : ret2)
//        std::cout << n->value << ", ";
//    std::cout << std::endl;
//}