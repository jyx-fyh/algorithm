//
// Created by ButcherX on 23-10-27.
//
#include"../header/treenode.h"
#include<string>
////个人解法


//个人解法：
//条件1：左右子树都是二叉搜索树
//条件2：左子树最大值<当前节点,右子树最小值>当前节点

struct info
{
    int flag;//-1=null, 0=false, 1=true
    int max;
    int min;
    info(int _flag):flag(_flag){};
    info(int _flag, int _max, int _min):flag(_flag), max(_max), min(_min){}
};

info progress(TreeNode* node)
{
    if(node == nullptr)
        return info(-1);
    info left = progress(node->left);
    info right = progress(node->right);
    if(left.flag == -1 && right.flag == -1)
        return info(1, node->data, node->data);
    if(left.flag == -1 && right.flag == 1 && right.min > node->data)
        return info(1, right.max, node->data);
    if(left.flag == 1 && right.flag == -1 && left.max < node->data)
        return info(1, node->data, left.min);
    if(left.flag == 1 && right.flag == 1 && left.max < node->data && right.min > node->data)
        return info(1, right.max, left.min);
    return info(0); //其他情况一律为false
}

bool judgeBST(TreeNode* root)
{
    if(root == nullptr)
        return true;
    return progress(root).flag;
}