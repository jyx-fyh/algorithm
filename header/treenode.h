//
// Created by butcherX on 23-10-21.
//

#ifndef ALGORITHM_TREENODE_H
#define ALGORITHM_TREENODE_H
#include<iostream>
struct TreeNode
{
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int _data): data(_data), left(NULL), right(NULL){}
};

#endif //ALGORITHM_TREENODE_H
