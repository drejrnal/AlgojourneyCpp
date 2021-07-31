//
// Created by luoxiYun on 2021/7/31.
//

#include "common.h"

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class treeDistance{

public:
    vector<int> distanceK( TreeNode *root, TreeNode *target, int k ){
        vector<int> result;
        //先从target节点开始dfs求距离为k的节点
        dfs( target, result,0,k );
        //将该树转变成target为根节点的树
        target->left = NULL;
        target->right = NULL;
        if( k != 0 && root != target ){
            transformTree( root, target );
            dfs( target, result, 0, k );
        }
        return result;
    }
    bool transformTree( TreeNode *root, TreeNode *target ){
        if( root == NULL )
            return false;
        if( root == target )
            return true;
        if(transformTree( root->left , target ) ){
            //target节点在root的左子树中
            if( !root->left->left )
                root->left->left = root;
            else if( !root->left->right ){
                root->left->right = root;
            }
            root->left = NULL;
            return true;
        }
        if(transformTree( root->right, target ) ){
            //target节点在root的右子树中
            if( !root->right->right ){
                root->right->right = root;
            }else if( !root->right->left ){
                root->right->left = root;
            }
            root->right = NULL;
            return true;
        }
        return false;
    }
    void dfs( TreeNode *start, vector<int> &result, int distance, int k ){
        if( distance == k ){
            result.push_back(start->val);
            return;
        }
        if( start->left )
            dfs( start->left, result, distance+1, k );
        if( start->right )
            dfs( start->right, result, distance+1, k );
    }

};

int main(){

}