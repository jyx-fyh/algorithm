//
// Created by ButcherX on 23-10-29.
//
//1.左右子树是否已经找到公共祖先
//2.左右子树是否已经分别找到a和b
//3.头结点自身是否是a或b
#include"../header/treenode.h"
struct info
{
    TreeNode* anc;
    TreeNode* target;
    info():anc(nullptr), target(nullptr){}
    info(TreeNode* _anc, TreeNode* tar): anc(_anc), target(tar){}
};

info process(TreeNode* root, TreeNode* a, TreeNode* b)
{
    if(root == nullptr)
        return info();
    info left = process(root->left, a, b);
    info right = process(root->right, a, b);
    info cur;
    //下行容易忽略,传递子树的目标
    cur.target = (left.target == nullptr ? (right.target == nullptr ? nullptr : right.target) : left.target);
    cur.anc = (left.anc == nullptr ? (right.anc == nullptr ? nullptr : right.anc) : left.anc);
    if(cur.anc != nullptr)
        return cur;
    if(left.target != nullptr && right.target != nullptr)
        cur.anc = root;
    if(root == a)
    {
        cur.target = root;
        if(left.target == b || right.target == b)
            cur.anc = root;
    }
    if(root == b)
    {
        cur.target = root;
        if(left.target == a || right.target == a)
            cur.anc = root;
    }
    return cur;
}

TreeNode* ancestor(TreeNode* root, TreeNode* a, TreeNode* b)
{
    info inf = process(root, a, b);
    return inf.anc;
}