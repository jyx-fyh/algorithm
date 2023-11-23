//
// Created by ButcherX on 23-10-26.
//
#include"../header/treenode.h"
#include<queue>
using std::queue;
/**
 * 完全二叉树的定义为：设二叉树的深度为h，除第 h 层外，其它各层 (1～h-1) 的结点数都
 * 达到最大个数，且第 h 层所有的结点都连续集中在最左边，这就是完全二叉树
 *
 * 思路：按层遍历，如果当前节点为空，则后续所有节点必须为空，否则非完全二叉树
 */
bool judgeCLB(TreeNode* root)
{
    if(root == nullptr)
        return true;
    bool flag = false;
    queue<TreeNode*> que;
    TreeNode* cur = root;
    que.push(cur);
    while(!que.empty())
    {
        cur = que.front();
        que.pop();
        if(cur == nullptr)
        {
            flag = true;
            continue;
        }
        else if(cur != nullptr && flag == true)
            return false;
        que.push(cur->left);
        que.push(cur->right);
    }
    return true;
}
//============================================



















