#include <stdio.h>
#include "binary_tree.h"

int main(int argc, char **argv)
{
    Bin_tree root = NULL;
    Bin_tree root1 = NULL;
    Bin_tree root2 = NULL;
    Tree_node *find = NULL;
    char *str = "ABC##DE##F##GH#I##J##";
    char *pre  = "ABCDEFGHIJ";
    char *mid  = "CBEDFAHIGJ";
    char *last = "CEFDBIHJGA";
    Boolean equal = FALSE;


    root = create_tree(&str);    //二叉树的创建
    root1 = create_tree_by_pre_mid(pre, mid, strlen(pre));
   
    printf("pre order:\n");
    pre_order_print(root);
    printf("\n");
  
    printf("mid order:\n");
    mid_order_print(root);
    printf("\n");

    printf("last order:\n");
    last_order_print(root);
    printf("\n");

    printf("last order:\n");
    last_order_print(root1);
    printf("\n");


    printf("level order:\n");
    level_order_print(root1);
    printf("\n");

    printf("pre order:\n");
    pre_order_print_nr(root);
    printf("\n");

    printf("mid order:\n");
    mid_order_print_nr(root);
    printf("\n");

    root2 = copy_binary_tree(root1);    //二叉树地拷贝

    if((equal = is_binarytree_equal(root1, root2)) == TRUE){
        printf("two trees are equal!\n");
    }


    printf("mid order:\n");
    mid_order_print_nr(root2);
    printf("\n");
   
    printf("the height of root2:%d\n", get_binarytree_height(root2));
    printf("the count of root2:%d\n", get_binarytree_node_count(root2));
    printf("the leaves count of root2:%d\n", get_binarytree_leaf_count(root2));
   
    //得到二叉树镜像
    swap_left_right(root1);
    printf("pre order:\n");
    pre_order_print_nr(root1);
    printf("\n");
    
    //判断是否是满二叉树
    if(is_full_binary_tree(root1) == TRUE){
        printf("root1 is full!\n");
    }else{
        printf("root1 is not full!\n");
    }
   
    //得到第n层二叉树的节点个数
    printf("the %d level count is:%d\n", 3, get_binarytree_level_count(root, 3));

    if((find = find_value(root, 'H')) == NULL){
        printf("H is not found!\n");
    }else{
        printf("%c is found!\n", find->data);
    }
 
    Tree_node *find1 = find_value(root, 'B');
    Tree_node *find2 = find_value(root, 'I');
    //找到两个节点的最近公共祖先
    Tree_node *parent = find_common_node(root, find1, find2);
    
    if(parent != NULL){ 
        printf("(%c and %c) parent is:%c\n",
            find1->data, find2->data, parent->data);
    }else{
        printf("not have baba!\n");
    }

    destroy_tree_nr(&root);
    destroy_tree_nr(&root1);
    destroy_tree_nr(&root2);
    return 0;
}
