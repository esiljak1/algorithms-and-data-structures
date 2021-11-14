#include <iostream>

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
}

void invertTreeHelper(TreeNode *node){
    if(node -> left)
        invertTreeHelper(node -> left);
    if(node -> right)
        invertTreeHelper(node -> right);
    
    std::swap(node -> left, node -> right);
}

TreeNode* invertTree(TreeNode *root){
    invertTreeHelper(root);
    return root;
}

int main(){
    return 0;
}