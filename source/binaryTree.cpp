#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <sstream> //stringstream
#include "../header/treenode.h"
using namespace std;

void del(TreeNode* nd)
{
    if(nd == nullptr)
        return;
    del(nd->left);
    del(nd->right);
    delete nd;
}

void preR(TreeNode* nd)
{
    if(nd == nullptr)
        return;
    cout << nd->data << endl;
    preR(nd->left);
    preR(nd->right);
}
void inR(TreeNode* nd)
{
    if(nd == nullptr)
        return;
    inR(nd->left);
    cout << nd->data << endl;
    inR(nd->right);
}

void postR(TreeNode* nd)
{
    if(nd == nullptr)
        return;
    postR(nd->left);
    postR(nd->right);
    cout << nd->data << endl;
}

void pre(TreeNode* root)
{
    if(root == nullptr)
        return;
    TreeNode* tmp;
    stack<TreeNode*> stk;
    stk.push(root);
    while(!stk.empty())
    {
        tmp = stk.top();
        cout << tmp->data << endl;
        stk.pop();
        if(tmp->right != nullptr)
            stk.push(tmp->right);
        if(tmp->left != nullptr)
            stk.push(tmp->left);
    }
}

void pre_1(TreeNode* root)
{
    if(root == nullptr)
        return;
    TreeNode* tmp = root;
    stack<TreeNode*> stk;
    while(tmp || !stk.empty())//为什么要tmp？因为当返回到root时,stk为空,但右子树还没有遍历
    {
        if(tmp != nullptr)
        {
            cout << tmp->data << endl;
            stk.push(tmp);
            tmp = tmp->left;
        }
        else
        {
            tmp = stk.top();
            stk.pop();
            tmp = tmp->right;
        }
    }
}

void in(TreeNode* root)
{
    if(root == nullptr)
        return;
    TreeNode* tmp = root;
    stack<TreeNode*> stk;
    while(tmp || !stk.empty())
    {
        if(tmp != nullptr)
        {
            stk.push(tmp);
            tmp = tmp->left;
        }
        else
        {
            tmp = stk.top();
            stk.pop();
            cout << tmp->data << endl;
            tmp = tmp->right;
        }
    }
}
void post(TreeNode* root)
{
    if(root == nullptr)
        return;
    TreeNode* tmp;
    stack<TreeNode*> stk1;
    stack<TreeNode*> stk2;
    stk1.push(root);
    while(!stk1.empty())
    {
        tmp = stk1.top();
        stk1.pop();
        stk2.push(tmp);
        if(tmp->left != nullptr)
            stk1.push(tmp->left);
        if(tmp->right != nullptr)
            stk1.push(tmp->right);
    }
    while(!stk2.empty())
    {
        tmp = stk2.top();
        stk2.pop();
        cout << tmp->data << endl;
    }
}

void layer(TreeNode* root)
{
    if(root == nullptr)
        return;
    TreeNode* tmp = root;
    queue<TreeNode*>que;
    que.push(tmp);
    while(!que.empty())
    {
        tmp = que.front();
        que.pop();
        cout << tmp->data << endl;
        if(tmp->left != nullptr) /**容易忽略**/
            que.push(tmp->left);
        if(tmp->right != nullptr) /**容易忽略**/
            que.push(tmp->right);
    }
}

void serializePre_in(TreeNode* nd, string& str)
{
    if(nd == nullptr)
    {
        str += "#,";
        return;
    }
    str.append(to_string(nd->data)).append(",");
    serializePre_in(nd->left, str);
    serializePre_in(nd->right, str);
}

string serializePre(TreeNode* root)
{
    if(root == nullptr)
        return "";
    string str = "";
    serializePre_in(root, str);
    return str;
}

TreeNode* deserializePre_in(queue<string> &que)/**必须引用**/
{
    string str = que.front();
    que.pop();
    if(str == "#")
        return nullptr;
    TreeNode* nd = new TreeNode(stoi(str));
    nd->left = deserializePre_in(que);
    nd->right = deserializePre_in(que);
    return nd;
}

TreeNode* deserializePre(string str)
{
    if(str.empty())
        return nullptr;
    stringstream ss(str);
    queue<string> tokens;
    string token;
    while (getline(ss, token, ','))
        tokens.push(token);

    TreeNode* root = deserializePre_in(tokens);
    return root;
}

void serializePost_in(TreeNode* nd, string &str)
{
    if(nd == nullptr)
    {
        str += "#,";
        return;
    }
    serializePost_in(nd->left, str);
    serializePost_in(nd->right, str);
    str.append(to_string(nd->data)).append(",");
}

string serializePost(TreeNode* root)
{
    if(root == nullptr)
        return "";
    string str;
    serializePost_in(root, str);
    return str;
}

TreeNode* deserializePost_in(stack<string> &stk)
{
    string tmp = stk.top();
    stk.pop();
    if(tmp == "#")
        return nullptr;
    TreeNode* nd = new TreeNode(stoi(tmp));
    nd->right = deserializePost_in(stk);
    nd->left = deserializePost_in(stk);
    return nd;
}

TreeNode* deserializePost(string str)
{
    if(str.empty())
        return nullptr;
    stringstream ss(str);//注意初始化ss!!!
    string token;
    stack<string> stk;
    while(getline(ss,token,','))
        stk.push(token);
    TreeNode* root = deserializePost_in(stk);
    return root;
}

string serializeLayer(TreeNode* root)
{
    if(root == nullptr)
        return "";
    string str;
    TreeNode* tmp;
    queue<TreeNode*> que;
    que.push(root);
    while(!que.empty())
    {
        tmp = que.front();
        que.pop();
        if(tmp == nullptr)/**易忽略**/
        {
            str.append("#,");
            continue;
        }
        str.append(to_string(tmp->data)).append(",");
        que.push(tmp->left);
        que.push(tmp->right);
    }
    return str;
}

TreeNode* generatenode(queue<string> &que)
{
    string tmp = que.front();
    que.pop();
    if(tmp != "#")
    {
        TreeNode* nd = new TreeNode(stoi(tmp));
        return nd;
    }
    else
        return nullptr;
}

TreeNode* deserializeLayer(const string &str)
{
    if(str.empty())
        return nullptr;
    queue<string> que_str;
    queue<TreeNode*> que_node;
    stringstream ss(str);
    string token;
    while(getline(ss, token, ','))
        que_str.push(token);

    TreeNode *tmp, *root;
    root = generatenode(que_str);
    if(root == nullptr)
        return nullptr;
    que_node.push(root);
    while(!que_str.empty())
    {
        tmp = que_node.front();
        que_node.pop();
        tmp->left = generatenode(que_str);
        tmp->right = generatenode(que_str);
        if(tmp->left != nullptr) // 只放非nullptr节点；
            que_node.push(tmp->left);
        if(tmp->right != nullptr)
            que_node.push(tmp->right);
    }
    return root;
}


/**打印二叉树**/
string getSpace(int num)
{
    std::string space = " ";
    std::string result = "";
    for (int i = 0; i < num; i++)
    {
        result += space;
    }
    return result;
}

void printInOrder(TreeNode* head, int height, const std::string& to, int len)
{
    if (head == nullptr)
    {
        return;
    }
    printInOrder(head->right, height + 1, "v", len);
    std::string val = to + std::to_string(head->data) + to;
    int lenM = val.length();
    int lenL = (len - lenM) / 2;
    int lenR = len - lenM - lenL;
    val = getSpace(lenL) + val + getSpace(lenR);
    std::cout << getSpace(height * len) + val << std::endl;
    printInOrder(head->left, height + 1, "^", len);
}

void printTree(TreeNode* head)
{
    std::cout << "Binary Tree:" << std::endl;
    printInOrder(head, 0, "H", 17);
    std::cout << std::endl;
}


TreeNode* randomNode(TreeNode* root)
{
    if(root == nullptr)
        return nullptr;
    srand(time(nullptr));
    TreeNode* tmp = root;
    queue<TreeNode*>que;
    que.push(tmp);
    while(!que.empty())
    {
        tmp = que.front();
        que.pop();
        if(rand() % 2 == 0)
            return tmp;
        if(tmp->left != nullptr) /**容易忽略**/
            que.push(tmp->left);
        if(tmp->right != nullptr) /**容易忽略**/
            que.push(tmp->right);
    }
    return root;
}
TreeNode* genRanBi_in(int maxLayers, int maxVar, int curLayer)
{
    curLayer++;
    if(curLayer > maxLayers)
        return nullptr;
    int odds = rand() % curLayer;//当前层数越深,生成节点的几率越小
    if(odds == 0 && curLayer != 1)
        return nullptr;
    else
    {
        TreeNode* nd = new TreeNode(rand() % maxVar + 1);
        nd->left = genRanBi_in(maxLayers, maxVar, curLayer);
        nd->right = genRanBi_in(maxLayers, maxVar, curLayer);
        return nd;
    }
}
TreeNode* generateRandomTreeLayer(int maxLayers, int maxVar)
{
    if(maxLayers <= 0)
        return nullptr;
    srand(time(nullptr));
    TreeNode* root = genRanBi_in(maxLayers, maxVar, 0);
    return root;
}

// 随机生成指定节点数的二叉树
TreeNode* generateRandomTreeNum_in(int numNodes, int maxValue) {
    if (numNodes <= 0) {
        return nullptr;
    }
    if (numNodes == 1) {
        int data = rand() % maxValue + 1;
        return new TreeNode(data);
    }
    int leftNodes = rand() % numNodes; // 随机分配节点数给左子树
    int rightNodes = numNodes - leftNodes - 1; // 剩余的节点数给右子树
    int data = rand() % (maxValue + 1);
    TreeNode* root = new TreeNode(data);
    root->left = generateRandomTreeNum_in(leftNodes, maxValue);
    root->right = generateRandomTreeNum_in(rightNodes, maxValue);
    return root;
}

TreeNode* generateRandomTreeNum(int numNodes, int maxVar)
{
    if(numNodes <= 0)
        return nullptr;
    srand(time(nullptr));
    TreeNode* root = generateRandomTreeNum_in(numNodes, maxVar);
    return root;
}