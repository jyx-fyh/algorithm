//
// Created by ButcherX on 23-11-2.
//
#include"../header/treenode.h"
#include"../header/binaryTree.h"
#include<queue>
#include<list>
using std::queue;
using std::list;
using std::pair;
struct NaryNode
{
    int data;
    list<NaryNode*> children;
    NaryNode(int _data):data(_data){}
};

TreeNode* convert1(NaryNode* root)
{
    if(root == nullptr)
        return nullptr;
    TreeNode* biRoot = new TreeNode(root->data);
    pair<NaryNode*, TreeNode*> tmp_pr;
    queue<pair<NaryNode*, TreeNode*>> que;
    que.push(pair(root, biRoot));
    while(!que.empty())
    {
        tmp_pr = que.front();
        que.pop();
        if(!tmp_pr.first->children.empty())
        {
            auto p = tmp_pr.first->children.begin();
            while(p != tmp_pr.first->children.end())
            {
                if(p == tmp_pr.first->children.begin())
                {
                    TreeNode* nd = new TreeNode((*p)->data);
                    tmp_pr.second->left = nd;
                    que.push(pair(*p, nd));
                    p++;
                }
                else
                {
                    auto tmp = que.back();
                    TreeNode* nd = new TreeNode((*p)->data);
                    tmp.second->right = nd;
                    que.push(pair(*p, nd));
                    p++;
                }
            }
        }
    }
    return biRoot;
}

TreeNode* convert_in(list<NaryNode*> children)
{
    if(children.empty())
        return nullptr;
    auto p = children.begin();
    TreeNode* head = new TreeNode((*p)->data);
    head->left = convert_in((*p)->children);
    p++;
    TreeNode* tmp = head;
    while(p != children.end())
    {
        tmp->right = new TreeNode((*p)->data);
        tmp = tmp->right;
        tmp->left = convert_in((*p)->children);
        p++;
    }
    return head;
}
TreeNode* convert(NaryNode* root)
{
    if(root == nullptr)
        return nullptr;
    TreeNode* binaryRoot = new TreeNode(root->data);
    binaryRoot->left = convert_in(root->children);
    return binaryRoot;
}




int main()
{
//       1
//     / | \
//    2  3  4
//   /\\    /\\
//  8 9 10 5 6 7

    NaryNode* root = new NaryNode(1);
    root->children.push_back(new NaryNode(2));
    root->children.push_back(new NaryNode(3));
    root->children.push_back(new NaryNode(4));
    root->children.back()->children.push_back(new NaryNode(5));
    root->children.back()->children.push_back(new NaryNode(6));
    root->children.back()->children.push_back(new NaryNode(7));
    root->children.front()->children.push_back(new NaryNode(8));
    root->children.front()->children.push_back(new NaryNode(9));
    root->children.front()->children.push_back(new NaryNode(10));
    TreeNode* binaryRoot = convert(root);
    string fuck = serializePre(binaryRoot);
    cout <<fuck;
}

