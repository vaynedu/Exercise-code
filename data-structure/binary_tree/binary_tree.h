#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

// 1.二叉树：
//    普通；
//    二叉搜索树（平衡二叉搜索树：
//               avl树，红黑树）
//              （非平衡二叉搜索树）
//    二叉线索树； 
// 2.多叉树：
//    B树（磁盘检索）
#include "tools.h"

#define END ('#')
#define ONE (1)

typedef struct Tree_node Tree_node;

struct Tree_node{
    char              data;    //数据区域
    Tree_node  *left_child;    
    Tree_node *right_child;
};                 

typedef Tree_node *Bin_tree;   //二叉树的根节点

//二叉树的接口

//创建二叉树
Bin_tree create_tree(char **str);    //创建二叉树
Bin_tree create_tree_by_pre_mid(char *pre_str, char *mid_str, int length);  
Bin_tree create_tree_by_mid_last(char *mid_str, char *last_str, int length);  

void destroy_tree(Bin_tree *root);    //销毁二叉树
void destroy_tree_nr(Bin_tree *root);   //非递归销毁二叉树

//        A      |      A
//       / \     |     / \
//      B   C    |    C   B
//     / \   \   |   /   / \
//    D   E   F  |  F   E   D
//
//    先序（根、左、右）  A  B  D  E  C
//    中序（左、根、右）  D  B  E  A  C
//    后序（左、右、根）  D  E  B  C  A
//    层序 （1----h）     A  B  C  D  E
void pre_order_print(Bin_tree root);    //前序递归遍历
void mid_order_print(Bin_tree root);    //中序递归遍历
void last_order_print(Bin_tree root);    //后序递归遍历

void pre_order_print_nr(Bin_tree root);    //前序非递归遍历
void mid_order_print_nr(Bin_tree root);    //中序非递归遍历
void last_order_print_nr(Bin_tree root);    //后序非递归遍历

void level_order_print(Bin_tree root);    //层序遍历

Bin_tree copy_binary_tree(Bin_tree root);    //二叉树的拷贝
Boolean is_binarytree_equal(Bin_tree root1,
                            Bin_tree root2);    //二叉树是否相等

Boolean is_full_binary_tree(Bin_tree root);   //判断是否是满二叉树
Boolean is_complete_binary_tree(Bin_tree root);   //判断是否是完全二叉树
Boolean is_balance_binary_tree(Bin_tree root);    //判断是否是平衡二叉树

int get_binarytree_height(Bin_tree root);    //得到二叉树的高度
int get_binarytree_node_count(Bin_tree root);   //得到二叉树的节点个数
int get_binarytree_leaf_count(Bin_tree root);    //得到二叉树的叶子节点个数
void swap_left_right(Bin_tree root);   //得到二叉树的镜像
int get_binarytree_level_count(Bin_tree root, int level);    //得到指定层级的节点个数

Tree_node *find_value(Bin_tree root, char value);    //找到指定值所在的节点
Tree_node *find_common_node(Bin_tree root, Tree_node *node1,
                            Tree_node *node2 );   //找到两个节点的最近公共节点

Tree_node *find_parent(Bin_tree root,
                       Tree_node *node);    //找到指定节点的双亲节点

Boolean is_include_tree(Bin_tree root1,
                        Bin_tree root2);    //二叉树是否包含

int get_largest_dir_count(Bin_tree root);   //得到二叉树的最大路径


//                   A
//                  / \
//                 B   C
//                / \
//               D   E
//              /     \                                    /   
//             F       G
//                    /
//                   H
                      
#endif
