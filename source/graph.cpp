//
// Created by ButcherX on 23-11-9.
//
#include"../header/graph.h"
#include<queue>
#include<stack>
#include<iostream>
using std::stack;
using std::queue;

graph graphAdaptor(vector<vector<int>> _graph)
{
    graph gra;
    int weight;
    int from;
    int to;
    for(int i = 0; i < _graph.size(); i++)
    {
        weight = _graph[i][0];
        from = _graph[i][1];
        to = _graph[i][2];
        if(gra.nodes.find(from) == gra.nodes.end())
        {
            graphNode* node = new graphNode(from);
            gra.nodes.emplace(from, node);
        }
        if(gra.nodes.find(to) == gra.nodes.end())
        {
            graphNode* node = new graphNode(to);
            gra.nodes.emplace(to, node);
        }
        graphNode* nodeFrom = gra.nodes.at(from);
        graphNode* nodeTo = gra.nodes.at(to);
        graphEdge* edge = new graphEdge(weight, nodeFrom, nodeTo);
        nodeFrom->edges.push_back(edge);
        nodeFrom->out++;
        nodeTo->in++;
        nodeFrom->nexts.push_back(nodeTo);
        gra.edges.emplace(edge);
    }
    return gra;
}



void graphDFS_in(graphNode* node, unordered_set<graphNode*> &accessed)//注意这里必须引用！
{
    if(accessed.find(node) != accessed.end())
        return;
    std::cout << node->value << ", ";
    accessed.emplace(node);
    for(auto n : node->nexts)
        graphDFS_in(n, accessed);
}

void graphDFS(graphNode* node)
{
    if(node == nullptr)
        return;
    unordered_set<graphNode*> accessed;
    graphDFS_in(node, accessed);
    std::cout << std::endl;
}

void graphDFS_stack(graphNode* node)
{
    stack<graphNode*> stk;
    unordered_set<graphNode*> set;
    graphNode* tmp;
    stk.push(node);
    set.emplace(node);
    std::cout<< node->value << ", ";
    while(!stk.empty())
    {
        tmp = stk.top();
        stk.pop();
        for(auto n : tmp->nexts)
        {
            if(set.find(n) == set.end())
            {
                stk.push(tmp);
                stk.push(n);
                set.emplace(n);
                std::cout<< n->value << ", ";
            }
        }
    }
    std::cout << std::endl;
}

void graphBFS(graphNode* node)
{
    if(node == nullptr)
        return;
    graphNode* tmp;
    queue<graphNode*> que;
    unordered_set<graphNode*> accessed;
    que.push(node);
    accessed.emplace(node);
    while(!que.empty())
    {
        tmp = que.front();
        que.pop();
        std::cout << tmp->value << ", ";
        auto p = tmp->nexts.begin();
        while(p != tmp->nexts.end())
        {
            if(accessed.find(*p) == accessed.end())
            {
                que.push(*p);
                accessed.emplace(*p);
            }
            p++;
        }
    }
    std::cout << std::endl;
}
//int main()
//{
//    vector<vector<int>> nodes = {{0,1,2},
//                                 {0,1,3},
//                                 {0,2,3},
//                                 {0,2,4},
//                                 {0,2,5},
//                                 {0,4,5},
//                                 {0,5,3},
//                                 {0,6,5},
//                                 {0,3,6}};
//    graph gra = graphAdaptor(nodes);
//    graphNode* p = gra.nodes.at(1);
//    graphDFS_stack(p);
//    graphDFS(p);
//    graphBFS(p);
//}