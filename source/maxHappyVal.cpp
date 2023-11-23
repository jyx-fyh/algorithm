//
// Created by ButcherX on 23-11-3.
//
#include<iostream>
#include<list>
using std::list;

struct employee
{
    int happy; // 这名员工可以带来的快乐值
    list<employee*> inferior; // 这名员工有哪些直接下级
    employee(int _happy):happy(_happy){}
};

int process(employee* superior, bool present)
{

    int max = 0;
    auto p = superior->inferior.begin();
    while(p != superior->inferior.end())
    {
        if(present == true)//上级来了,则该员工不能来
            max += process((*p), false);
        else//上级没来，该员工可来可不来
        {
            int go = (*p)->happy + process((*p), true);
            int notGo = process((*p), false);
            max += std::max(go, notGo);
        }
        p++;
    }
    return max;
}

int happyVal(employee* root)
{
    if(root == nullptr)
        return 0;
    int m = std::max(process(root, true), process(root, false));
    return m;
}

int main()
{
//       4
//     / | \
//    13 3  10
//   /\\    /\\
//  1 3 8  5 3 1
//     / \
//    5   4
    employee* root = new employee(4);
    root->inferior.push_back(new employee(13));
    root->inferior.push_back(new employee(3));
    root->inferior.push_back(new employee(10));
    root->inferior.back()->inferior.push_back(new employee(5));
    root->inferior.back()->inferior.push_back(new employee(3));
    root->inferior.back()->inferior.push_back(new employee(1));
    root->inferior.front()->inferior.push_back(new employee(1));
    root->inferior.front()->inferior.push_back(new employee(3));
    root->inferior.front()->inferior.push_back(new employee(8));
    root->inferior.front()->inferior.back()->inferior.push_back(new employee(5));
    root->inferior.front()->inferior.back()->inferior.push_back(new employee(4));
    int val = happyVal(root);
    std::cout << val;
}