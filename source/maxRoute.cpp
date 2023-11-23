//
// Created by ButcherX on 23-10-27.
//
#include"../header/treenode.h"

//个人解法
struct info
{
    int maxHeight;
    int maxDis;
    info(int height, int dis):maxHeight(height), maxDis(dis){}
};

info findMaxDis_in(TreeNode* nd)
{
    if(nd == nullptr)
    {
        info inf(0, 0);
        return inf;
    }
    info infl = findMaxDis_in(nd->left);
    info infr = findMaxDis_in(nd->right);

    info infc(0, 0);
    infc.maxDis = std::max(std::max(infl.maxDis, infr.maxDis), infl.maxHeight + infr.maxHeight);
    infc.maxHeight = std::max(infl.maxHeight, infr.maxHeight) + 1;
    return infc;
}

int findMaxDis(TreeNode* root)
{
    info inf = findMaxDis_in(root);
    return std::max(inf.maxHeight - 1, inf.maxDis);
}

//官方解法
class Solution{
    int ans;
    int depth(TreeNode* rt){
        if (rt == nullptr) {
            return 0; // 访问到空节点了，返回0
        }
        int L = depth(rt->left); // 左儿子为根的子树的深度
        int R = depth(rt->right); // 右儿子为根的子树的深度
        ans = std::max(ans, L + R + 1); // 计算d_node即L+R+1 并更新ans
        return std::max(L, R) + 1; // 返回该节点为根的子树的深度
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        ans = 1;
        depth(root);
        return ans - 1;
    }
};