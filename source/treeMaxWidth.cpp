//
// Created by ButcherX on 23-10-30.
//
#include"../header/treenode.h"
#include<queue>
using std::queue;
/**返回树的最大宽度**/
int maxWidth(TreeNode* root)
{
    if(root == nullptr)//易略
        return 0;
    queue<TreeNode*> que;
    TreeNode* curEnd = root;
    TreeNode* nextEnd = nullptr;
    TreeNode* tmp;
    int max = 1;
    int counter = 0;
    que.push(root);
    while(!que.empty())
    {
        tmp = que.front();
        que.pop();
        counter++;
        if(tmp->left != nullptr)
        {
            que.push(tmp->left);
            nextEnd = tmp->left;
        }
        if(tmp->right != nullptr)
        {
            que.push(tmp->right);
            nextEnd = tmp->right;
        }
        if(tmp == curEnd)
        {
            max = max > counter ? max : counter;
            counter = 0;
            curEnd = nextEnd;
            nextEnd = nullptr;
        }
    }
    return max;
}
