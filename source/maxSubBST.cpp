//
// Created by ButcherX on 23-10-29.
//
#include"../header/treenode.h"
//描述：找出当前二叉树中拥有最多节点的搜索二叉子树
可修改代码
//个人解法：
//1.左右子树是为搜索二叉树
//2.左子树max<cur,右子树min>cur
//3.cur.size = left.size+right.size+1
//struct info
//{
//    bool isNul;
//    bool isBST;
//    int size;
//    int max;
//    int min;
//    info(bool _isNul):isNul(_isNul){}
//    info(bool _isBST, int _size):isBST(_isBST), size(_size){}
//    info(bool _isNul, bool _isBST, int _size, int _max, int _min)
//    :isNul(_isNul), isBST(_isBST), size(_size), max(_max), min(_min){}
//};
//
//info process(TreeNode* nd)
//{
//    if(nd == nullptr)
//        return info(true);
//    info left = process(nd->left);
//    info right = process(nd->right);
//    if(!left.isNul && (!left.isBST || left.max >= nd->data))
//        return info(false, right.isNul ? left.size : std::max(left.size, right.size));
//    if(!right.isNul && (!right.isBST || right.min <= nd->data))
//        return info(false, left.isNul ? right.size : std::max(left.size, right.size));
//    if(left.isNul && right.isNul)
//        return info(false, true, 1, nd->data, nd->data);
//    if(left.isNul && !right.isNul)
//        return info(false, true, right.size + 1, std::max(right.max, nd->data), std::min(right.min, nd->data));
//    if(!left.isNul && right.isNul)
//        return info(false, true, left.size + 1, std::max(left.max, nd->data), std::min(left.min, nd->data));
//    if(!left.isNul && !right.isNul)
//        return info(false, true, left.size + right.size + 1, std::max(nd->data, std::max(left.max, right.max))
//                        , std::min(nd->data, std::min(left.min, right.min)));
//}
//
//int maxSubBST(TreeNode* root)
//{
//    if(root == nullptr)
//        return 0;
//    return process(root).size;
//}
//
//
//
//


















