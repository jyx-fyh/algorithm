//
// Created by bubtcher on 23-10-21.
//

#ifndef ALGORITHM_BINARYTREE_H
#define ALGORITHM_BINARYTREE_H
#include"treenode.h"
#include<iostream>
#include <string>
#include <queue>
using std::cout, std::endl, std::string, std::queue;
void del(TreeNode* nd);//删除树
void preR(TreeNode* nd);//递归前序遍历
void inR(TreeNode* nd);//递归后续遍历
void postR(TreeNode* nd);//递归后续遍历
void pre(TreeNode* root);//非递归前序遍历1
void pre_1(TreeNode* root);//非递归前序遍历2
void in(TreeNode* root);//非递归中序遍历
void post(TreeNode* root);//非递归后续遍历
void layer(TreeNode* root);//层序遍历
string serializePre(TreeNode* root);//前序序列化
TreeNode* deserializePre(string str);//前序反序列化
string serializePost(TreeNode* root);//后续序列化
TreeNode* deserializePost(string str);//后续反序列化
string serializeLayer(TreeNode* root);//层序序列化
TreeNode* deserializeLayer(const string &str);//层序反序列化
void printTree(TreeNode* head);//打印树
TreeNode* generateRandomTreeLayer(int maxLayers, int maxVar);//随机创建一棵树,指定最大层数
TreeNode* generateRandomTreeNum(int numNodes, int maxVar);//随机创建一棵树,指定节点数
TreeNode* randomNode(TreeNode* root);//随机返回树中的一个节点

#endif //ALGORITHM_BINARYTREE_H
