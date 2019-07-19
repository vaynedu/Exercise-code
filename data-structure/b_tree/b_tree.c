#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "b_tree.h"

//B树的操作接口

static B_tree buy_node(void)
{
    B_tree root = (Tree_node *)Malloc(sizeof(Tree_node));
    bzero(root, sizeof(Tree_node));

    return root;
}

static B_tree     make_tree_node(void)       //B树的创建
{
    int i = 0;

    B_tree root = buy_node();
    //对节点的各个变量进行初始化
    root->key_count = 0;
    root->is_leaf = TRUE;
    root->key = (int *)Malloc(sizeof(int) * MAX_KEY_COUNT);
    root->child = (struct Tree_node **)
                  Malloc(sizeof(struct Tree_node *) * MAX_CHILD_COUNT);
    root->parent = NULL;
    for(i = 0; i < MAX_CHILD_COUNT; ++i){
        root->child[i] = NULL;
    }

    return root;
}

//分裂B树中的节点
static void b_tree_split_child(Tree_node *split_node, int index_child)
{
    Tree_node *new_child = make_tree_node();
    new_child->key_count = DEGREE - 1;    //调整新节点的关键字个数
    int i = 0;

    //将满子节点的后半部分关键字复制到新的节点
    for(i = 0; i < DEGREE - 1; ++i){
        new_child->key[i] = split_node->child[index_child]->key[DEGREE + i];
    }
    //把之前那个满节点的关键字个数减少到DEGREE - 1
    split_node->child[index_child]->key_count = DEGREE - 1;
    //如果它的第index_child孩子不是叶子节点，则把index_child的后DEGREE孩子也
    //赋值给new_child节点
    if(split_node->child[index_child]->is_leaf != TRUE){
        new_child->is_leaf = FALSE;
        for(i = 0; i < DEGREE - 1; ++i){
            new_child->child[i] = split_node->child[DEGREE + i];
        }
    }
    //提升第index_child个节点的中间关键字到split_node处来分隔
    //split_node->child[index_child]和new_child.
    for(i = split_node->key_count; i >= index_child; i--){
        split_node->child[i + 1] = split_node->child[i];
    }
    //新的节点在以前节点的右边
    split_node->child[index_child + 1] = new_child;
    split_node->key_count++;
    for(i = split_node->key_count - 1; i >= index_child; --i){
        split_node->key[i + 1] = split_node->key[i];
    }
    split_node->key[index_child] = 
        split_node->child[index_child]->key[DEGREE - 1];
}

//向为满的节点中插入指定关键字
static void b_tree_insert_nonfull(Tree_node *nonfull, int key_value)
{
    int i = nonfull->key_count - 1;    //指定最后一个关键字的下标

    if(nonfull->is_leaf == TRUE){    //如果该节点没有叶子节点
        //找到key_value的合适插入位置
        while(i >= 0 && key_value < nonfull->key[i]){ 
            nonfull->key[i + 1] = nonfull->key[i];
            i--;
        }
        i = i + 1;
        nonfull->key_count++;
        nonfull->key[i] = key_value;
    }else{
        //如果有叶子节点，则需要递归的在其叶子节点中找到合适的插入位置
        while(i >= 0 && key_value < nonfull->key[i]){
           i--;
        }
        i = i + 1;
        //查看要插入的节点是否已满
        if(nonfull->child[i]->key_count == MAX_KEY_COUNT){ 
             b_tree_split_child(nonfull, i);
             if(key_value > nonfull->key[i]){ 
                 i = i + 1;
             }
        }  
        b_tree_insert_nonfull(nonfull->child[i], key_value);
    }
}

B_tree create_tree(void)   //创建B树
{
   return make_tree_node(); 
}

void      destroy_b_tree(B_tree root)                   //B树的销毁
{
    if(root == NULL){
        return ;
    }

    //首先销毁B树中的所有孩子节点，在销毁节点本身

}

//从以当前节点为根节点的子树中，寻找key_value所在的点
Tree_node *b_tree_search(B_tree root, int key_value)   
{
    int i = 0;

    if(root == NULL){ 
        return NULL;
    }

    //关键字没有被遍历完，并且要查找的关键字大于当前下标的关键
    while(i < root->key_count && key_value > root->key[i]){
        i++;
    }

    //找到指定的关键字
    if(i < root->key_count && key_value == root->key[i]){
        return root;
    }
    //如果在当前节点的关键字匹配失败，并且当前节点没有孩子
    //则查找失败，否则继续在当前关键字所对应孩子节点的关键
    //字序列中进行查找
    if(root->is_leaf == TRUE){
        return NULL;
    }
    return b_tree_search(root->child[i], key_value);
}

//在b_tree中加入新的关键字
void      b_tree_insert(B_tree *root, int key_value)  
{
    Tree_node*p_node = NULL; 
    B_tree new_root = NULL;  

    if(root == NULL || *root == NULL){
        return ;  
    }

    p_node = *root;
    if(p_node->key_count == MAX_KEY_COUNT){
        //当前节点中关键字个数已满，则需要将原来的根节点分裂，一个新的
        //节点new_root成为根
        //   eg: t = 4
        new_root = make_tree_node();
        new_root->child[FIRST] = *root;
        new_root->is_leaf = FALSE;
        *root = new_root; 

        //分裂的过程输入的两个参数分别是一个非满的内部节点root和一个使
        //root->child[i]为满子节点的下标i
        b_tree_split_child(new_root, 0);
        b_tree_insert_nonfull(new_root, key_value);
    }else{
        //当前节点中的关键字个数未满，则直接插入
        b_tree_insert_nonfull(*root, key_value);
    }
}

//从以当前节点为根节点的树中删除key_value关键字
void      b_tree_delete(B_tree root, int key_value) 
{
    
}

void      print_b_tree(B_tree root)                     //打印B树信息
{
    int i = 0;
    int key_count = 0;

    if(root == NULL){ 
        return ;
    }
 
    key_count = root->key_count;
    //输出当前节点的关键字
    printf("[");
    for(i = 0; i < key_count; ++i){ 
        printf("%d", root->key[i]);
        if(i  != root->key_count - 1){
            printf(" ");
        }
    }
    printf("]");
    //递归的输出所有子树
    for(i = 0; i <= key_count; ++i){
        print_b_tree(root->child[i]);
    }
}


