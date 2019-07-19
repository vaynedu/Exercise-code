#ifndef _RBTREE_H_
#define _RBTREE_H_

#define ZERO    (0)
#define RED     (0)
#define BLACK   (1)

typedef struct Rbtree_node
{
    int                data       ;    //数据   
    int                color      ;    //节点颜色    
    struct Rbtree_node *left      ;    //左孩子
    struct Rbtree_node *right     ;    //右孩子
    struct Rbtree_node *parent    ;    //双亲节点
}Rbtree_node;

typedef Rbtree_node *Rbtree;

//红黑数的接口
Rbtree_node *find_max_node(Rbtree root)            ;    //找到红黑树中的最大值节点
Rbtree_node *find_min_node(Rbtree root)            ;    //找到红黑树中的最小值节点
Rbtree_node *rb_search(int data, Rbtree root)      ;    //返回上述查找过程的查找结果
Rbtree      rb_insert(int data, Rbtree root)       ;    //红黑树的插入操作
Rbtree      rb_delete(int data, Rbtree root)       ;    //红黑数的删除操作
void        preorder_print(Rbtree root)            ;    //先根序遍历树 
#endif
