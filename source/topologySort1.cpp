//
// Created by ButcherX on 23-11-11.
//
//测试链接：https://www.lintcode.com/problem/127/
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<utility>
#include<stack>
#include<algorithm>
using std::pair;
using std::stack;
using std::unordered_set;
using std::unordered_map;
using std::vector;
struct DirectedGraphNode
{
     int label;
     vector<DirectedGraphNode *> neighbors;
     DirectedGraphNode(int x) : label(x) {};
};

//方法1：高度比较==============================================================================
struct wrap
{
    DirectedGraphNode* node;
    int depth;
    wrap(DirectedGraphNode* _node, int _depth):node(_node), depth(_depth){}
};

int process(DirectedGraphNode* node, unordered_map<DirectedGraphNode*, wrap*> &map)
{
    if(map.find(node) != map.end())
        return map[node]->depth;
    if(node->neighbors.empty())
        return 1;
    int maxDepth = 0;
    int depth;
    for(auto n : node->neighbors)
    {
        depth = process(n, map);
        wrap* w = new wrap(n, depth);
        map.emplace(n, w);
        maxDepth = maxDepth > depth ? maxDepth : depth;
    }
    return maxDepth + 1;
}

vector<DirectedGraphNode*> topSort(vector<DirectedGraphNode*> graph)
{
    unordered_map<DirectedGraphNode*, wrap*> map;
    int depth;
    for(auto n : graph)
    {
        depth = process(n, map);
        wrap* w = new wrap(n, depth);
        map.emplace(n, w);
    }
    vector<pair<DirectedGraphNode*, wrap*>> vec;
    for(auto n : map)
        vec.push_back(n);
    std::sort(vec.begin(), vec.end()
              , [](pair<DirectedGraphNode*, wrap*> a, pair<DirectedGraphNode*, wrap*> b)
              {return a.second->depth > b.second->depth;});
    vector<DirectedGraphNode*> ret;
    for(auto n : vec)
        ret.push_back(n.first);
    return ret;
}

//方法2 深度优先==============================================================================
void dfs(DirectedGraphNode* node, unordered_set<DirectedGraphNode*> visitedInPath
        , unordered_set<DirectedGraphNode*> &visited, stack<DirectedGraphNode*> &stk)
{
    if(visitedInPath.find(node) != visitedInPath.end())
        exit(0);
    if(visited.find(node) != visited.end())
        return;
    visited.emplace(node);
    visitedInPath.emplace(node);
    for(auto n : node->neighbors)
        dfs(n, visitedInPath, visited, stk);
    stk.push(node);
}

vector<DirectedGraphNode*> topSort1(vector<DirectedGraphNode*> graph)
{
    unordered_set<DirectedGraphNode*> visitedInPath;
    unordered_set<DirectedGraphNode*> visited;
    stack<DirectedGraphNode*> stk;
    vector<DirectedGraphNode*> ret;
    for(auto n : graph)
        dfs(n, visited, visitedInPath, stk);
    while(!stk.empty())
    {
        ret.push_back(stk.top());
        stk.pop();
    }
    return ret;
}

















