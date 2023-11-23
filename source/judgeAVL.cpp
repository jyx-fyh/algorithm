//
// Created by ButcherX on 23-10-27.
//
#include"../header/treenode.h"
#include <iostream>
#include <vector>
#include <chrono>

/**
* AVL树中，任一节点对应的两棵子树的最大高度差为1
*/

//个人解法：
int judge_in(TreeNode* nd)
{
    if(nd == nullptr)
        return 0;
    int leftH;
    int rightH;
    leftH = judge_in(nd->left);
    rightH = judge_in(nd->right);
    if(leftH == -1 || rightH == -1 || abs(leftH - rightH) > 1)
        return -1;
    return std::max(leftH + 1, rightH + 1);
}

bool judgeAVL(TreeNode* root)
{
    if(root == nullptr)
        return true;
    int leftH = judge_in(root->left);
    int rightH = judge_in(root->right);
    if(leftH == -1 || rightH == -1 || abs(leftH - rightH) > 1)
        return false;
    else
        return true;
}
//====================================================================
//套路解法
struct info
{
    bool isAVL;
    int height;
    info(bool _isAVL, int _height):isAVL(_isAVL), height(_height){}
};

info process(TreeNode* node)
{
    if(node == nullptr)
        return info(true, 0);
    info left = process(node->left);
    info right = process(node->right);
    if(!left.isAVL || !right.isAVL || abs(left.height - right.height) > 1)
        return info(false, -1); //此时不用再判断高度,可传任意值
    return info(true, std::max(left.height, right.height) + 1);
}

bool judgeAVL1(TreeNode* root)
{
    if(root == nullptr)
        return true;
    return process(root).isAVL;
}
//======================================================================
//官方解法：
int getHeight(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    return 1 + std::max(leftHeight, rightHeight);
}

// 判断二叉树是否为平衡二叉树
bool isBalanced(TreeNode* root)
{
    if (root == nullptr)
    {
        return true;
    }

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    // 检查当前节点是否平衡，即左右子树高度差是否不超过1
    if (std::abs(leftHeight - rightHeight) <= 1 &&
        isBalanced(root->left) && isBalanced(root->right))
    {
        return true;
    }

    return false;
}
//======================================================================
// 生成随机二叉树（用于测试）
//TreeNode* GenerateRandomBinaryTree(int n)
//{
//    if (n <= 0)
//    {
//        return nullptr;
//    }
//    // 生成一个随机值作为节点的值
//    int val = rand() % 100;
//    TreeNode* root = new TreeNode(val);
//    int leftSize = rand() % n;
//    root->left = GenerateRandomBinaryTree(leftSize);
//    root->right = GenerateRandomBinaryTree(n - leftSize - 1);
//    return root;
//}
//
//int main() {
//    const int numTests = 1;  // 测试次数
//    const int treeSize = 10000000;   // 生成的二叉树节点数量
//
//    std::vector<TreeNode*> testTrees;
//    for (int i = 0; i < numTests; ++i)
//    {
//        // 生成随机二叉树
//        TreeNode* root = GenerateRandomBinaryTree(treeSize);
//        testTrees.push_back(root);
//    }
//
//    std::chrono::duration<double> totalDuration(0);
//    for (int i = 0; i < numTests; ++i)
//    {
//        auto start = std::chrono::high_resolution_clock::now();
//
//        // 测试二叉树是否为平衡二叉树
//        bool isBalancedTree = isBalanced(testTrees[i]);
//        //bool isBalancedTree = judgeAVL(testTrees[i]);
//
//        auto end = std::chrono::high_resolution_clock::now();
//        std::chrono::duration<double> duration = end - start;
//        totalDuration += duration;
//        // 清理二叉树内存
//        delete testTrees[i];
//    }
//
//    double averageTime = totalDuration.count() / numTests;
//    std::cout << "平均运行时间：" << averageTime << " 秒" << std::endl;
//    return 0;
//}