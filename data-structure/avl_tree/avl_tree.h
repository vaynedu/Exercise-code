#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

typedef struct Avl_node{
    int               data;    //数据域
    int             height;    //该节点的高度
    struct Avl_node  *left;    //左孩子
    struct Avl_node *right;    //右孩子
}Avl_node;

typedef Avl_node *Avl_tree;    //avl树

#define ONE     (1)
#define ZERO    (0)
#define max(a, b)  ((a) < (b) ? (b) : (a))

//avl树接口
int      get_tree_height(Avl_tree root)         ;    //得到avl树的高度
void     preorder_avltree(Avl_tree root)        ;    //前序遍历avl树
void     inorder_avltree(Avl_tree root)         ;    //中序遍历avl树
void     postorder_avltree(Avl_tree root)       ;    //后序列遍历avl树
//查找数据域为value的节点
Avl_node *find_node(Avl_tree root, int value)   ; 
Avl_node *get_max_node(Avl_tree root)           ;    //找到值最大的节点
Avl_node *get_min_node(Avl_tree root)           ;    //找到值最小的节点
//将节点插入到avl树中
Avl_tree avltree_insert(Avl_tree root, int data);    
//从avl树中删除指定数值
Avl_tree avltree_delete(Avl_tree root, int data);
//销毁avl树
void destroy_avltree(Avl_tree root);

#endif
