#include "avl_tree.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

static int height(Avl_tree node)
{
    if(node == NULL){
        return -1;
    }
    return node->height;
}

static Avl_node *buy_node(void)
{
    Avl_node *result = (Avl_node *)Malloc(sizeof(Avl_node));
    if(result == NULL){
        fprintf(stderr, "the memory is full!\n");
        exit(1);
    }
    bzero(result, sizeof(Avl_node));
    return result;
}


int      get_tree_height(Avl_tree root)    //得到avl树的高度
{
    return height(root);
}

void     preorder_avltree(Avl_tree root)    //前序遍历avl树
{
    if(root != NULL){
        printf("%d ", root->data);
        preorder_avltree(root->left);
        preorder_avltree(root->right);
    }
}

void     inorder_avltree(Avl_tree root)    //中序遍历avl树
{
    if(root != NULL){
        inorder_avltree(root->left);
        printf("%d ", root->data);
        inorder_avltree(root->right);
    }
}

void     postorder_avltree(Avl_tree root)    //后序列遍历avl树
{
    if(root != NULL){
        postorder_avltree(root->left);
        postorder_avltree(root->right);
        printf("%d ", root->data);
    }
}

//查找数据域为value的节点
Avl_node *find_node(Avl_tree root, int value)
{
    if(root == NULL || root->data == value){
        return root;
    }
    if(value < root->data){
        return find_node(root->left, value);
    }else{
        return find_node(root->right, value);
    }
}

static Avl_node *find_node1(Avl_tree root, int value)
{
    Avl_node *p_node = root;
    
    while(p_node != NULL){
        //如果当前节点的值大于被查找的值，则继续比较当前节点的左孩子
        //如果当前节点的值小于被查找的值，则继续比较当前节点的右孩子
        if(p_node->data > value){
            p_node = p_node->left;
        }else if(p_node->data < value){
            p_node = p_node->right;
        }else{
            //当前节点的值符合要求
            return p_node;
        }
    }
    return NULL;
}
 
Avl_node *get_max_node(Avl_tree root)    //找到值最大的节点
{
    Avl_node *p_node = root;

    while(p_node->right != NULL){
        p_node = p_node->right;
    }

    return p_node;
}

Avl_node *get_min_node(Avl_tree root)    //找到值最小的节点
{
    Avl_node *p_node = root;
    
    while(p_node->left != NULL){
        p_node = p_node->left;
    }
   
    return p_node;
}

static int avl_node_height(Avl_node *node)
{
    return max(height(node->left), height(node->right)) + 1;
}

//单旋（左旋）
static Avl_node *avl_rotate_left(Avl_node *node)
{
    Avl_node *new_root = NULL;
  
    new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;

    //旋转完后修改当前节点的高度（有顺序要求）
    node->height = avl_node_height(node);
    new_root->height = avl_node_height(new_root);
    
    return new_root;
}

//单旋（右旋）
static Avl_node *avl_rotate_right(Avl_node *node)
{
    Avl_node *new_root = NULL;
   
    new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;

    //旋转完后修改当前节点的高度（右顺序要求）
    node->height = avl_node_height(node);
    new_root->height = avl_node_height(new_root);

    return new_root;
}

//双旋(先左再右)
static Avl_node *avl_rotate_left_right(Avl_node *node)
{
    node->left = avl_rotate_left(node->left);
    return avl_rotate_right(node);
}
//双旋(先右再左)
static Avl_node *avl_rotate_right_left(Avl_node *node)
{
    node->right = avl_rotate_right(node->right);
    return avl_rotate_left(node);
}

//将节点插入到avl树中
Avl_tree avltree_insert(Avl_tree root, int data)
{
    int height_diff = 0;

    if(root == NULL){
        //插入的节点为整个avl树的根节点
        root = buy_node();
        root->data = data;
    }else if(data < root->data){
        //将data插入到root的左子树中
        root->left = avltree_insert(root->left, data);
        //插入节点后，需要进行平衡的判断（左右子树的高度差不能大于1）
        height_diff = height(root->left) - height(root->right);
        if(height_diff > ONE){
            //根据插入节点的位置判断是插入“内侧”还是“外侧”
            if(data < root->left->data){
                root = avl_rotate_right(root);
            }else{
                root = avl_rotate_left_right(root);
            }
        }
    }else if(data > root->data){
        //将data插入到root的右子树中
        root->right = avltree_insert(root->right, data);
        //插入节点后，需要进行平衡的判断（左右子树的高度差不能大于1）
        height_diff = height(root->right) - height(root->left);
        if(height_diff > ONE){
            //判断插入节点是在“内侧”还是“外侧”
            if(data > root->right->data){
                root = avl_rotate_left(root);
            }else{
                root = avl_rotate_right_left(root);
            }
        }
    }else{
        //data == root->data
        //说明树中已经存在该节点，插入失败
        fprintf(stderr, "the tree_node has been created!\n");
    }

    root->height = avl_node_height(root);
    return root;
}

//节点删除具体操作
static Avl_tree delete_node(Avl_tree root, Avl_node *node)
{
    int      height_diff = 0   ;
    Avl_node *p_node     = NULL;
    Avl_node *left_max   = NULL; 
    Avl_node *right_min  = NULL;
    Avl_node *temp       = NULL;

    if(root == NULL || node == NULL){
        return NULL;
    }
    
    if(node->data < root->data){    //待删除的节点在root左子树
        root->left = delete_node(root->left, node);
        //删除节点后，如果avl树失去平衡(左右子树高度差大于1)
        //，则需要进行相应的调整
        height_diff = height(root->right) - height(root->left);
        if(height_diff > ONE){
            p_node = root->right;
            //判断是单旋还是双旋
            if(height(p_node->left) > height(p_node->right)){   //双旋
                root = avl_rotate_right_left(root);
            }else{    //单旋
                root = avl_rotate_left(root);
            }
        }
    }else if(node->data > root->data){    //待删除的节点在root右子树
        root->right = delete_node(root->right, node);
        height_diff = height(root->left) - height(root->right);
        if(height_diff > ONE){
            p_node = root->left;
            if(height(p_node->right) > height(p_node->left)){
                root = avl_rotate_left_right(root);
            }else{
                root = avl_rotate_right(root);
            }
        }
    }else{    //root就是对应的删除节点
        //root的左右孩子都不为空
        if((root->left != NULL) && (root->right != NULL)){
            //如果左子树比右子树高，则：
            //1.找出root的左子树中的最大值节点
            //2.将该节点的值赋值给root
            //3.删除该最大值节点
            //删除左子树的最大节点后，该树依然平衡 
            if(height(root->left) > height(root->right)){
                 left_max = get_max_node(root->left);
                 root->data = left_max->data;
                 root->left = delete_node(root->left, left_max);
            }else{
                //如果root的左子树不比右子树高，则：
                //1.找出root的右子树中最小的节点
                //2.将该结点的值赋值给root
                //3.删除该最小节点
                right_min = get_min_node(root->right);
                root->data = right_min->data;
                root->right = delete_node(root->right, right_min);
            }
        }else{   //被删除节点的左右孩子有一个为空 
            temp = root;
            if(root->left != NULL){
                root = root->left;
            }else{
                root = root->right;
            }
            free(temp);
        }
    }
    return root;
}

//调整整课树节点的高度
static int adjust_node_height(Avl_tree root)
{
    int l_height = 0;
    int r_height = 0;

    if(root == NULL){    //该节点不存在，高度为-1
        return -1;
    }else if((root->left == NULL)
          && (root->right == NULL)){   //叶子节点，高度为0
        return 0;
    }else{   //非叶子节点，高度为左右子树中的最大值加1
        l_height = adjust_node_height(root->left);
        r_height = adjust_node_height(root->right);
        return max(l_height, r_height) + 1;
    }
}

//从avl树中删除指定数值
Avl_tree avltree_delete(Avl_tree root, int data)
{
    Avl_node *node = NULL;

    //如果该节点存在则执行删除操作
    if((node = find_node(root, data)) != NULL){
        root = delete_node(root, node);
        adjust_node_height(root);
    }

    return root;
}

//销毁avl树
void destroy_avltree(Avl_tree root)
{
    if(root == NULL){
        return ;
    }
    
    destroy_avltree(root->left);
    destroy_avltree(root->right);
    free(root);
}
