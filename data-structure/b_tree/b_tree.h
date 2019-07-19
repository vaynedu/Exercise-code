#ifndef _B_TREE_H_
#define _B_TREE_H_

// B树的节点个树以及关键字都与B树的度（degree）有关,其满足这样的关系：
//
//1.除了根节点以外，每个节点必须至少有 t - 1 个关键字，因此除了根节点
//以外的每个内部节点至少有t个孩子。如果树非空，则根节点至少有一个关键
//字。
//
//2.每个节点最多可包含2t - 1个关键字。因此一个内部节点最多含有2t个孩子，
//当一个节点恰好有2t - 1个关键字时，则称该节点是满的。
//
// 
#include "tools.h"

#define DEGREE   (200)   //树的度数

#define TRUE  (1)
#define FALSE  (0)

#define MAX_KEY_COUNT    (2 * (DEGREE) - 1)
#define MAX_CHILD_COUNT  (2 * (DEGREE))

#define FIRST    (0)

typedef unsigned char Boolean;

typedef struct Tree_node{
    int              key_count;    //指示该节点的关键字个数
    int                   *key;    //该节点关键字数组
    Boolean            is_leaf;    //该节点是否是叶子节点
    struct Tree_node   **child;    //该节点的所有孩子节点
    struct Tree_node   *parent;    //指向该节点的父节点
}Tree_node;

typedef Tree_node *B_tree;

//B树的操作接口

B_tree    create_tree(void)    ;   //B树的创建
void      destroy_b_tree(B_tree root)               ;    //B树的销毁
//从以当前节点为根节点的子树中，寻找key_value所在的节点
Tree_node *b_tree_search(B_tree root, int key_value);   
//在b_tree中加入新的关键字
void      b_tree_insert(B_tree *root, int key_value) ; 
//从以当前节点为根节点的树中删除key_value关键字
void      b_tree_delete(B_tree root, int key_value) ;
void      print_b_tree(B_tree root)                 ;    //打印B树信息

#endif
