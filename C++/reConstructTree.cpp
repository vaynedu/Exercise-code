//输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。

class Solution {
public:
    struct TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> in) {
        int in_size = in.size();
        vector<int>pre_left,pre_right,in_left,in_right;
        int i = 0;
        int p = 0;
        int val = pre[0];
        TreeNode *node = new TreeNode(val);
        
        if(in_size == 0){
            return NULL;
        }
        
        for(p = 0; p < in_size; ++p){
            if(in[p] == val){
                break;  //find the root position in in
            }
        }
        for(i = 0; i < in_size; ++i){
            if(i < p){
                in_left.push_back(in[i]);
                pre_left.push_back(pre[i+1]);
            }else if(i > p){
                in_right.push_back(in[i]);
                pre_right.push_back(pre[i]);
            }
        }
        
        node->left = reConstructBinaryTree(pre_left,in_left);
        node->right = reConstructBinaryTree(pre_right,in_right);
        
        return node;
    }
};