//题目描述
//输入一棵二叉树，判断该二叉树是否是平衡二叉树

class Solution {
public:
    int get_binary_height(TreeNode* pRoot){
        if(pRoot == NULL){
            return 0;
        }
        return 1 + max(get_binary_height(pRoot->left),
                       get_binary_height(pRoot->right));
    }
    bool IsBalanced_Solution(TreeNode* pRoot) {
        int num = 0;
        
        if(pRoot == NULL){
            return true;
        }
        
        num = abs(get_binary_height(pRoot->left) - get_binary_height(pRoot->right));
        
        if(num <= 1){
               IsBalanced_Solution(pRoot->right);
            IsBalanced_Solution(pRoot->left);
         
        }else{
            return false;
        }
        
        return true;
    }
};
