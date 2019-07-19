#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "tools.h"

#define FALSE (0)
#define TRUE  (1)

typedef struct Tree_node{
    int   data;
    struct Tree_node *left_child;
    struct Tree_node *right_child;
}Tree_node;

typedef Tree_node *Bin_tree;

typedef unsigned char Boolean;

#define max(a,b) ((b) > (a) ? (b) : (a))

Bin_tree insert_value(Bin_tree root, int value);    //二叉树的插入
int get_tree_height(Bin_tree root);
Tree_node *find_value(Bin_tree root, int value, Tree_node **parent);


Tree_node *find_value(Bin_tree root,
              int value, Tree_node **parent)
{
    Tree_node *p_node = root;
    Tree_node *q_node = NULL;

    while(p_node != NULL){
        q_node = p_node;
        if(p_node->data > value){
            p_node = p_node->left_child;
        }else if(p_node->data < value){
            p_node = p_node->right_child;
        }else{
            return p_node;
        }
    }

    if(parent != NULL){
         *parent = q_node;
    }
    return NULL;
}
 
static Tree_node *buy_node(void)
{
    Tree_node *node = (Tree_node *)Malloc(sizeof(Tree_node));
    bzero(node, sizeof(Tree_node));
   
    return node;
}

Bin_tree insert_value(Bin_tree root, int value)    //二叉树的插入
{
    Tree_node *p_node = NULL;
    Tree_node *new_node = NULL;
 
    if(root == NULL){   //当树为空时，生成节点赋值
        root = buy_node();
        root->data = value;
        return root;
    }else{
        if(find_value(root, value, &p_node) != NULL){    //该节点已存在，插入失败
             fprintf(stderr, "insert failed!\n");
             return root;
        }
        //新生成节点并插入到平衡二叉树的对应位置
        new_node = buy_node();
        new_node->data = value;

        if(p_node != NULL){
            if(p_node->data > value){
                p_node->left_child = new_node;
            }else{
                p_node->right_child = new_node;
            }
        }
        return root; 
    }
}

int get_tree_height(Bin_tree root)
{
    if(root == NULL){
        return 0;
    }

    return 1 + max(get_tree_height(root->left_child),
                   get_tree_height(root->right_child));
}


int main(int argc, char **argv)
{
    Bin_tree root = NULL;
    int array[] = {12, 23, 34, 45, 56, 67, 78};
    int length = sizeof(array) / sizeof(int);    
    int i = 0;
     
    for(i = 0; i < length; ++i){
        root = insert_value(root, array[i]);
        printf("the tree height:%d\n", get_tree_height(root));
    }
   
    printf("the tree height:%d\n", get_tree_height(root));
   
    return 0;
}
