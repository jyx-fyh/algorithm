//
// Created by ButcherX on 23-11-9.
//

#ifndef ALGORITHM_GRAPH_H
#define ALGORITHM_GRAPH_H
#include<unordered_map>
#include<unordered_set>
#include<list>
#include<vector>
using std::list;
using std::vector;
using std::unordered_set;
using std::unordered_map;
// 点结构的描述
struct graphEdge;
struct graphNode
{
    int value;
    int in;
    int out;
    list<graphNode*> nexts;
    list<graphEdge*> edges;
    graphNode(int _value):value(_value), in(0), out(0){}
};

struct graphEdge
{
    int weight;
    graphNode* from;
    graphNode* to;
    graphEdge(int _weight, graphNode* _from, graphNode* _to):weight(_weight), from(_from), to(_to){}
};

struct graph
{
    unordered_map<int, graphNode*> nodes;
    unordered_set<graphEdge*> edges;
};

graph graphAdaptor(vector<vector<int>> _graph);
void graphBFS(graphNode* node);
void graphDFS(graphNode* node);
#endif //ALGORITHM_GRAPH_H
