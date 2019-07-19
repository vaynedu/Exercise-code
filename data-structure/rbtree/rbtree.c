#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "rbtree.h"
#include "tools.h"

//红黑树的接口

//创建新的节点
static Rbtree_node *buy_node(void)
{
    Rbtree_node *result = (Rbtree_node *)Malloc(sizeof(Rbtree_node));
    bzero(result, sizeof(Rbtree_node));
    
    return result;
}

//找到红黑树的最大值节点
Rbtree_node *find_max_node(Rbtree root)
{
    Rbtree_node *p_node = root;

    //从根结点一直寻找它最右边的节点，该结点为二叉搜索树的最大值
    while(p_node != NULL){
        p_node = p_node->right;
    } 
    return p_node;
}

//找到红黑树的最小值节点
Rbtree_node *find_min_node(Rbtree root)
{
    Rbtree_node *p_node = root;
   
    //从根结点一直寻找它最左边的节点，该节点为二叉搜索树的最小值
    while(p_node != NULL){
        p_node = p_node->left;
    }
   
    return p_node;
}

//左旋
static Rbtree rb_rotate_left(Rbtree_node *node, Rbtree root)
{
    Rbtree_node *right = node->right;
    
    //原node的右孩子变为right的左孩子
    if((node->right = right->left)){
        //如果right的左孩子不为空，则修改其父节点的指向
        right->left->parent = node;
    }
    right->left = node;

    //修改node父节点左孩子或者右孩子的指向    
    if((right->parent = node->parent)){
        if(node == node->parent->right){
            node->parent->right = right;
        }else{
            node->parent->left = right;
        }
    }else{
        root = right;
    }
    node->parent = right;
    
    return root;
}

//右旋
static Rbtree rb_rotate_right(Rbtree_node *node, Rbtree root)
{
    Rbtree_node *left = node->left;

    if((node->left = left->right)){ 
        left->right->parent = node;
    }
    left->right = node;

    if((left->parent = node->parent)){ 
        if(node == node->parent->right){
            node->parent->right = left;
        }else{
            node->parent->left = left;
        }
    }else{
        root = left;
    }
    node->parent = left;
    
    return root;
}


//红黑树查找节点
static Rbtree_node *rb_search_auxiliary(int data, 
           Rbtree root, Rbtree_node **save)
{
    Rbtree_node *node = root;
    Rbtree_node *parent = NULL;
    int result = 0;
   
    while(node != NULL){
        //1.如果当前节点的值等于查找的值，直接返回；
        //2.如果当前节点的值小于查找的值，则用其右孩子和查找的值比较；
        //3.如果当前节点的值大于查找的值，则用其左孩子和查找的值比较；
        parent = node;
        result = node->data - data;
        if(ZERO < result){
            node = node->left;
        }else if(ZERO > result){
            node = node->right;
        }else{ 
            return node;
        }
    }
    //说明红黑树中没有该值，但是记录下了要插入该值的双亲节点
    if(save != NULL){
        *save = parent;
    }
   
    return NULL;
}

//返回上述查找过程的查找结果
Rbtree_node *rb_search(int data, Rbtree root)
{
    return rb_search_auxiliary(data, root, NULL);
}


//红黑树插入后的调整工作
//插入的情况有5种：
//1.新的节点N位于树的根上，没有父节点
//2.新节点的父节点P是黑色
//3.父节点P，叔叔节点U，都是红色
//4.父节点P是红色，叔叔节点U是黑色或者NULL，且N为右孩子
//5.父节点P是红色，叔叔节点U是黑色或者NULL，且N为左孩子
static Rbtree rb_insert_rebalance(Rbtree_node *node, Rbtree root)
{
    Rbtree_node *parent  = NULL;    //父亲节点
    Rbtree_node *gparent = NULL;    //祖父节点
    Rbtree_node *uncle   = NULL;    //叔叔节点

    //parent为node的双亲节点，且当双亲节点的颜色为红色
    while((parent = node->parent) && parent->color == RED){
        gparent = parent->parent;   //gparent为祖父节点
        if(parent == gparent->left){  //双亲节点为左孩子，祖父节点为右孩子
            uncle = gparent->right;
            //case1 :node的叔叔是红色
            if(uncle != NULL && uncle->color == RED){
                uncle->color = BLACK;
                parent->color = BLACK;
                gparent->color = RED;
                node = gparent;
            }else{    //case2 :node的叔叔是黑色的
                if(parent->right == node){    //且z为右孩子
                    root = rb_rotate_left(parent, root);
                    swap(&parent, &node, sizeof(parent));
                } 
                
                //case3 :node的叔叔节点是黑色的，此时node成为了左孩子
                //case3是由case2转换过来的
                parent->color = BLACK;
                gparent->color = RED;
                root = rb_rotate_right(gparent, root);
            }
        }else{
            //双亲节点为祖父节点的右孩子，叔叔节点为左孩子
            uncle = gparent->left;
            if(uncle != NULL && uncle->color == RED){
                //case1: node的叔叔节点是红色
                uncle->color = BLACK;
                parent->color = BLACK;
                gparent->color = RED; 
                node = gparent;
            }else{    //case2: node的叔叔节点是黑色的，且node为左孩子
                if(parent->left == node){
                    root = rb_rotate_right(parent, root);
                    swap(&parent, &node, sizeof(parent));
                }

                //case3:由情况2变化而来
                parent->color = BLACK;
                gparent->color = RED;
                root = rb_rotate_left(gparent, root);
            }
        } 
    }
    
    root->color = BLACK;
    return root; 
}


//红黑树的插入操作
Rbtree rb_insert(int data, Rbtree root)
{
    Rbtree_node *parent = NULL;
    Rbtree_node *node   = NULL;
 
    //该数值在红黑树中已经存在，无需进行插入
    if((node = rb_search_auxiliary(data, root, &parent)) != NULL){
        return root;
    }
    
    node = buy_node();   //构造新节点
    node->data = data;
    node->parent = parent;
    node->left = node->right = NULL;
    node->color = RED;  

    if(parent != NULL){
        if(parent->data > data){
            parent->left = node;
        }else{
            parent->right = node;
        }
    }else{
        //要插入的节点是红黑树的第一个节点
        root = node;    
    }
   
    //插入节点后，对红黑树进行调整
    return rb_insert_rebalance(node, root);   
}

//红黑树删除后的调整
//
//红黑树的调整一共有四种情况：
//    1.当前节点是黑色，当前兄弟节点为红色（此时父节点和兄弟节点的子
//    节点为黑色）
//    2.当前节点是黑色，且当前节点的兄弟节点是黑色，并且兄弟节点的两
//    个子节点全为黑色
//    3.当前节点是黑色，兄弟节点是黑色，兄弟节点的左孩子是红色，
//    右孩子是黑色
//    4.当前节点是黑色，兄弟节点是黑色，兄弟节点的右孩子是红色，
//    左孩子颜色任意
static Rbtree rb_delete_rebalance(Rbtree_node *node,
           Rbtree_node *parent, Rbtree root)
{
    Rbtree_node *other   = NULL;   //当前节点的兄弟节点 
    Rbtree_node *o_left  = NULL;   //兄弟节点的左孩子
    Rbtree_node *o_right = NULL;   //兄弟节点的右孩子

    while( (node == NULL || node->color == BLACK) && node != root){
        if(parent->left == node){
            //找到兄弟节点的位置
            other = parent->right;
            if(other->color == RED){    //case1:兄弟节点为红色
                other->color = BLACK;
                parent->color = RED;
                root = rb_rotate_left(parent, root);
                other = parent->right;
            }

            if((other->left == NULL || other->left->color == BLACK)
            && (other->right == NULL || other->right->color == BLACK)){
                //case2:兄弟节点是黑色，且兄弟节点的两个孩子也是黑色
                other->color = RED;
                node = parent;
                parent = node->parent;
            }else{
                //case3:兄弟节点是黑色，且兄弟节点的左孩子是红色，
                //右孩子是黑色的
                if(other->right == NULL || other->right->color == BLACK){
                    if((o_left = other->left)){
                        o_left->color = BLACK;    //左孩子由红色变成黑色
                    }
                    other->color = RED;
                    root = rb_rotate_right(other, root);
                    other = parent->right;
                }

                //case4:兄弟节点是黑色
                //把兄弟节点染成当前节点父节点的颜色
                //把当前及诶但父节点染成黑色
                other->color = parent->color;
                parent->color = BLACK;
                if(other->right != NULL){
                    other->right->color = BLACK;
                }
                root = rb_rotate_left(parent, root);   
                node = root;
                break ;
            } 
        }else{
            other = parent->left;
            if(other->color == RED){   //case1
                 other->color = BLACK;
                 parent->color = RED;
                 root = rb_rotate_right(parent, root);
                 other = parent->left;
            }
             
            //case2
            if((other->left == NULL || other->left->color == BLACK)
            && (other->right == NULL || other->right->color == BLACK)){
                other->color = RED;
                node = parent;
                parent = node->parent;
            }else{
                if(other->left == NULL || other->left->color == BLACK){
                    if((o_right = other->right)){
                        o_right->color = BLACK;
                    }
                    other->color = RED;
                    root = rb_rotate_left(other, root);
                    other = parent->left;
                }
                other->color = parent->color;
                parent->color = BLACK;
                if(other->left != NULL){
                    other->left->color = BLACK;
                }
                root = rb_rotate_right(parent, root);
                node = root;
                break ;
            }            
        }
    }

    if(node != NULL){
        node->color = BLACK;   //最后将node改为黑色
    }
    
    return root;
}

//红黑数的删除 操作
Rbtree rb_delete(int data, Rbtree root)
{
    Rbtree_node *child  = NULL; 
    Rbtree_node *parent = NULL;
    Rbtree_node *old    = NULL;
    Rbtree_node *left   = NULL; 
    Rbtree_node *node   = NULL;
    //记录下被删除的节点是红色还是黑色,如果是黑色的话删除元素会影响
    //红黑树每条路线上黑色节点的数量，需要对红黑树进行调整
    int         color   = RED ;   

    //判断红黑树是否存在该节点
    if((node = rb_search_auxiliary(data, root, NULL)) == NULL){
        fprintf(stderr, "value %d is not exist!\n", data);
        return root;
    }
 
    //用old记录被删除的节点
    old = node;

    if(node->left && node->right){
        //3.node的节点拥有左右孩子，选择node的右儿子中的最小元素
        //，将它放到待删除节点的位置。
        node = node->right;
        while((left = node->left) != NULL){
            node = left;
        }
        //最小值拥有右孩子
        child = node->right;
        parent = node->parent;
        color = node->color;
    
        if(child != NULL){
            child->parent = parent;   
        }
        if(parent != NULL){
            if(node == parent->left){
                parent->left = child;
            }else{
                parent->right = child;
            }
        }else{
            //          root
            //         /   /
            //     left   right 
            root = child;            
        }

        if(node->parent == old){
            parent = node;
        }

        //用子树中最小的节点完全替代被删除的节点
        node->parent = old->parent;
        node->left = old->left;
        node->right = old->right;
        node->color = old->color;

        if(old->parent != NULL){
            if(old->parent->left == old){
                old->parent->left = node;
            }else{
                old->parent->right = node;
            }
        }else{
            root = node;
        }
        old->left->parent = node;
        if(old->right != NULL){
            old->right->parent = node;
        }
    }else{
        //1.没有儿子及诶但，直接把父节点的对应儿子指针设为NULL
        //2.只有一个儿子，那么把父节点的相应儿子指针指向儿子的独生子
        if(node->left == NULL){
            //如果左孩子为空，则把右孩子赋值给child
            child = node->right;
        }else if(node->right == NULL){
            //否则把左孩子赋值给child
            child = node->left;
        }
        parent = node->parent;
        color = node->color;
              
        if(child != NULL){
            child->parent = parent;
        }
        if(parent != NULL){
            if(parent->left == node){
                parent->left = child;
            }else{
                parent->right = child;
            }
        }else{
            //只用当被删除的节点为根节点时才会出现父节点为空
            root = child;
        }
    }
    //删除指定值的节点
    free(old); 
  
    if(color == BLACK){
        //此时的child在被删除节点的位置
        root = rb_delete_rebalance(child, parent, root);
    }
  
    //返回调整后的根节点
    return root;
}

void preorder_print(Rbtree root)
{
    if(root != NULL){
        printf("%d  ", root->data);
        preorder_print(root->left);
        preorder_print(root->right);
    }
}
