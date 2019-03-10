//树的子结构
//输入两棵二叉树A，B，判断B是不是A的子结构。（ps：我们约定空树不是任意一个树的子结构） 


/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};*/
class Solution {
    bool isSubtree(TreeNode* pRootA, TreeNode* pRootB) {
        if (pRootB == NULL){
            return true;
        }
        if (pRootA == NULL){
            return false;
        }
        if (pRootB->val == pRootA->val) {
            return isSubtree(pRootA->left, pRootB->left)
                && isSubtree(pRootA->right, pRootB->right);
        }else{
            return false;
        }
    }
public:
    bool HasSubtree(TreeNode* pRootA, TreeNode* pRootB)
    {
        if (pRootA == NULL || pRootB == NULL){
            return false;
        }
        return isSubtree(pRootA, pRootB) ||
            HasSubtree(pRootA->left, pRootB) ||
            HasSubtree(pRootA->right, pRootB);
    }
};







Boolean does_tree_have_tree2(Bin_tree *root1,Bin_tree *root2)
{
    if(root2 == NULL){
        return TRUE;
    }
    if(root1 == NULL){
        return FALSE;
    }
    if(root1->data != root2->data){
        return FALSE;
    }

    return (does_tree_have_tree2(root1->left_child,root2->left_child) 
           &&  does_tree_have_tree2(root1->right_child,root2->right_child));
}

Boolean is_include_tree(Bin_tree root1,
                        Bin_tree root2)    //二叉树是否包含
{
    //                  A
    //                /   \
    //               B     G   
    //              / \    / \
    //             C   D  H   J
    //                / \  \
    //               E   F  I
    //
    //        1.找root2在root1中的位置，如果存在，则在root1对于
    //        的位置开始（p_node），递归地对root2的左右子树部分进行
    //        查找，如果root2遍历结束，则认为root2包含于root1
    //
    //   《剑指offer》

    Boolean result = FALSE;

    if(root1 != NULL && root2 != NULL){
        if(root1->data == root2->data){
            result = does_tree_have_tree2(root1,root2);
        }
        if(result == NULL){
            result = is_include_tree(root1->left_child,root2);
        }
        if(result == NULL){
            result = is_include_tree(root2->right_child,root2);
        }
    }

    return result;

}