//
// Created by ButcherX on 23-11-11.
//
#include<queue>
#include"../header/graph.h"
using std::queue;
//课程表：https://leetcode.cn/problems/course-schedule/
//提交时需要引入graph.h中的声明
bool topologySort(const graph& gra)
{
    queue<graphNode*> zero_in;
    unordered_map<graphNode*, int> map_in;
    graphNode* tmp;
    int counter1 = 0;
    int counter2 = 0;
    for(auto n : gra.nodes)
    {
        map_in.emplace(n.second, n.second->in);
        counter1++;
    }
    for(auto n : gra.nodes)
    {
        if (n.second->in == 0)
            zero_in.push(n.second);
    }
    while(!zero_in.empty())
    {
        tmp = zero_in.front();
        zero_in.pop();
        counter2++;
        for(auto n : tmp->nexts)
        {
            map_in[n]--;
            if(map_in.at(n) == 0)
                zero_in.push(n);
        }
    }
    return counter1 == counter2;
}
bool classSchedule(int numCourses, vector<vector<int>>& prerequisites)
{
    if(numCourses == 0)
        return true;
    graph gra = graphAdaptor(prerequisites);
    return topologySort(gra);
}

//int main()
//{
//    vector<vector<int>> pre{{0,1},{0,2},{2,0}};
//    bool aha = classSchedule(3, pre);
//    if(aha)
//        std::cout << "yes";
//}
