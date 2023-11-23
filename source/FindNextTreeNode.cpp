#include<iostream>
#include<queue>
#include<list>
using namespace std;
struct Node
{
    int data;
    Node* parent;
    Node* left;
    Node* right;
    Node(int _data):data(_data), parent(nullptr), left(nullptr), right(nullptr){}
};

void del(Node* nd)
{
    if(nd == nullptr)
        return;
    del(nd->left);
    del(nd->right);
    delete nd;
}

Node* genTree_in(int maxLayers, int maxVar, int curLayer, Node* parent)
{
    curLayer++;
    if(curLayer > maxLayers)
        return nullptr;
    int ran;
    if(curLayer <= 2)
        ran = rand() % 4;
    else
        ran = rand() % 2;
    if(ran == 0 && curLayer != 1)
        return nullptr;
    else
    {
        Node* nd = new Node(rand() % maxVar + 1);
        nd->parent = parent;
        nd->left = genTree_in(maxLayers, maxVar, curLayer, nd);
        nd->right = genTree_in(maxLayers, maxVar, curLayer, nd);
        return nd;
    }
}
Node* generateRandomTree(int maxLayers, int maxVar)
{
    if(maxLayers <= 0)
        return nullptr;
    srand(time(nullptr));
    Node* root = genTree_in(maxLayers, maxVar, 0, nullptr);
    return root;
}


Node* findNextPre(Node* nd)
{
    if(nd == nullptr)
        return nullptr;
    if(nd->left != nullptr)
        return nd->left;
    if(nd->right != nullptr)
        return nd->right;
    Node* pa = nd->parent;
    while(pa != nullptr)
    {
        if(pa->right != nd)
            return pa->right;
        nd = pa;
        pa = pa->parent;
    }
    return nullptr;
}

Node* findNextPost_in(Node* nd)
{
    if(nd->left == nullptr && nd->right == nullptr)
        return nd;
    if(nd->left != nullptr)
        return findNextPost_in(nd->left);
    if(nd->right != nullptr)
        return findNextPost_in(nd->right);
}
Node* findNextPost(Node* nd)
{
    if(nd == nullptr || nd->parent == nullptr)
        return nullptr;
    Node* parent = nd->parent;
    if(parent->right == nd || parent->right == nullptr)
        return parent;
    return findNextPost_in(parent->right);
}

Node* findNextIn_in(Node* nd)
{
    if(nd->left == nullptr)
        return nd;
    else
        return findNextIn_in(nd->left);
}

Node* findNextIn(Node* nd)
{
    if(nd == nullptr)
        return nullptr;
    if(nd->right != nullptr)
        return findNextIn_in(nd->right);
    Node* parent = nd->parent;
    while(parent != nullptr)
    {
        if(parent->right == nd)
        {
            nd = parent;
            parent = parent->parent;
        }
        return parent;
    }
    return nullptr;
}


Node* randomNode(Node* root)
{
    if(root == nullptr)
        return nullptr;
    srand(time(nullptr));
    Node* tmp = root;
    queue<Node*>que;
    que.push(tmp);
    while(!que.empty())
    {
        tmp = que.front();
        que.pop();
        if(rand() % 2 == 0)
            return tmp;
        if(tmp->left != nullptr)
            que.push(tmp->left);
        if(tmp->right != nullptr)
            que.push(tmp->right);
    }
    return root;
}

void pre(list<Node*> &orderList, Node* nd)
{
    if(nd == nullptr)
        return;
    orderList.push_back(nd);
    pre(orderList, nd->left);
    pre(orderList, nd->right);
}
void in(list<Node*> &orderList, Node* nd)
{
    if(nd == nullptr)
        return;
    in(orderList, nd->left);
    orderList.push_back(nd);
    in(orderList, nd->right);
}

void post(list<Node*> &orderList, Node* nd)
{
    if(nd == nullptr)
        return;
    post(orderList, nd->left);
    post(orderList, nd->right);
    orderList.push_back(nd);
}

void tester(int times, Node* (*func)(Node*))
{
    void (*trav)(list<Node*>&, Node*);
    if(func == findNextPre)
        trav = pre;
    else if(func == findNextIn)
        trav = in;
    else
        trav = post;
    for(int i = 0; i < times; i++)
    {
        Node* root = generateRandomTree(20, 10000);
        Node* nd = randomNode(root);
        list<Node*> orderList;
        trav(orderList, root);
        Node* next = func(nd);
        auto p = orderList.begin();
        while((*p) != nd)
            p++;
        p++;
        if((*p) == next || (p == orderList.end() && next == nullptr))
        {
            cout << "success" << endl;
            del(root);
            continue;
        }
        cout << "wrong..." << endl;
        cout << "traverse result: " << endl;
        for(auto i : orderList)
            cout << i->data << endl;
        return;
    }
}

int main()
{
    tester(1000000, findNextIn);
}






