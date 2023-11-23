//
// Created by ButcherX on 23-10-28.
//
#include"../header/treenode.h"
//个人解法
//0-null, 1-true, 2-false
int judgeFullTree_in(TreeNode* root)
{
   if(root == nullptr)
       return 0;
   int lc = judgeFullTree_in(root->left);
   int rc = judgeFullTree_in(root->right);
   if(lc == 0 && rc == 0)
       return 1;
   if(lc == 1 && rc == 1)
       return 1;
   if(lc + rc == 1)
       return 2;
   if(lc == 2 || rc == 2)
       return 2;
}

bool judgeFullTree(TreeNode* root)
{
    int ret = judgeFullTree_in(root);
    if(ret == 0 || ret == 1)
        return true;
    else
        return false;
}
//=======================================
//官方解法：
bool isFullBinaryTree(TreeNode* root) {
    // 如果树为空，则是满二叉树
    if (root == nullptr) {
        return true;
    }

    // 如果节点没有左子树和右子树，它是叶子节点
    if (root->left == nullptr && root->right == nullptr) {
        return true;
    }

    // 如果节点有左子树和右子树，继续检查它们
    if (root->left && root->right) {
        return isFullBinaryTree(root->left) && isFullBinaryTree(root->right);
    }

    // 如果节点只有左子树或右子树，不是满二叉树
    return false;
}
