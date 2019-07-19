#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include "binary_tree.h"
#include "tools.h"
#include "queue.h"
#include "stack.h"

//二叉树的接口

//创建二叉树

static Tree_node *create_node(void);
static void destroy(Bin_tree root);
static int get_index(char *string, char value);
static int max(int a, int b);
static Tree_node *find_common(Bin_tree root,
                              Tree_node *node1, Tree_node *node2);


static int max(int a, int b)
{ 
    return b > a ? b : a;
}


static int get_index(char *string, char value)
{
    // abcdefg
    //
    //     e
    char *local = strchr(string, value);
    return local == NULL ? -1 : (local - string) / sizeof(char);
}

static void destroy(Bin_tree root)
{
    if(root != NULL){
        destroy(root->left_child);  
        destroy(root->right_child);
        free(root);
    }
}

static Tree_node *create_node(void)
{
    Tree_node *node = (Tree_node *)Malloc(sizeof(Tree_node));
    bzero(node, sizeof(Tree_node));
 
    return node;
}

Bin_tree create_tree_by_pre_mid(char *pre_str, 
                       char *mid_str, int length)    //通过先序和中序构建二叉树

{
    Bin_tree root = NULL;
    char root_value = 0;
    int index = -1;
    //     先序： ABCDEFGHIJ    确定当前序列中根地位置
    //     中序： CBEDFAHIGJ    得到某个节点地左右子树部分
    if(pre_str == NULL || mid_str == NULL || length <= 0){
        return root;
    }
    
    root_value = pre_str[0];    //获取当前序列地根节点数值
    root = create_node();
    root->data = root_value;
   
    index = get_index(mid_str, root_value);

    //创建完根结点后递归处理其左右子树序列
    root->left_child = create_tree_by_pre_mid(pre_str + 1, mid_str, index);
    root->right_child = create_tree_by_pre_mid(pre_str + index + 1, 
                                               mid_str + index + 1,   
                                               length - index - 1);
    return root;    
}


Bin_tree create_tree_by_mid_last(char *mid_str, 
                       char *last_str, int length);    //通过中序和后序构建二叉树

Bin_tree create_tree(char **str)
{
    Bin_tree root = NULL;

    //ABC##DE##F##GH#I##J##
    if(str != NULL && *str != NULL && **str != END){
        root = create_node();  
        root->data = **str;
   
        //处理完当前节点，然后递归地创建其左右孩子
        //++*str;
        (*str)++;
        root->left_child = create_tree(str);
        //++*str;
        (*str)++;
        root->right_child = create_tree(str);
    }

    return root;
}

void destroy_tree(Bin_tree *root)    //销毁二叉树
{
    if(root == NULL || *root == NULL){
        return ;
    }

    destroy(*root);
    *root = NULL;

}
void destroy_tree_nr(Bin_tree *root)   //非递归销毁二叉树
{
    //思路：
    //               
    //
    //               A
    //              / \
    //             B   C
    //
    // 1.在销毁n层节点之前，首先把n + 1的节点入队进行地址保存
    //
    Queue *queue = init_queue();
    Tree_node *p_node = NULL;

    if(root == NULL || *root == NULL){
        return ;    
    }

    p_node = *root;
    *root = NULL;
    in(queue, p_node);

    while(!is_queue_empty(queue)){
         get_queue_front(queue, (void **)&p_node);
         out(queue);
       
         //先记录p_node对应的下一层节点的地址，再销毁p_node
         if(p_node->left_child != NULL){
             in(queue, p_node->left_child);
         }

         if(p_node->right_child != NULL){
             in(queue, p_node->right_child);
         }
         
         free(p_node);
    }

    destroy_queue(&queue);
}

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
void pre_order_print(Bin_tree root)    //前序递归遍历
{
    //                  A
    //                /   \
    //               B     G   
    //              / \    / \
    //             C   D  H   J
    //                / \  \
    //               E   F  I
    //
    //
    //     先序： ABCDEFGHIJ    确定当前序列中根地位置
    //     中序： CBEDFAHIGJ    得到某个节点地左右子树部分
    //     后序： CEFDBIHJGA
    //
    //////////////////////////////////////////////////////////////////
    //
    //                     A
    //                    / \
    //                   B   C
    //                  / \
    //                 D   E
    //
    //               ABDEC   pre
    //               DEBCA   last
    ////////////////////////////////////////////////////////////////////
    //
    //                  A
    //                 /                        
    //                B
    //               / \
    //              D   E    
    //                          
    //         ABDE
    //
    //         DEBA
    //
    //                 A            A
    //                /              \
    //               B                B
    //              /                / \   
    //             D                D   E
    //            /                     
    //           E                       
    //
    //   
    //
    //
    //
    if(root != NULL){
         printf("%c ", root->data);
         pre_order_print(root->left_child);
         pre_order_print(root->right_child);
    }
}

void mid_order_print(Bin_tree root)    //中序递归遍历
{
    if(root != NULL){
         mid_order_print(root->left_child);
         printf("%c ", root->data);
         mid_order_print(root->right_child);
    }

}

void last_order_print(Bin_tree root)    //后序递归遍历
{
    if(root != NULL){
         last_order_print(root->left_child);
         last_order_print(root->right_child);
         printf("%c ", root->data);
    }

}


void pre_order_print_nr(Bin_tree root)    //前序非递归遍历
{
    Stack *stack = init_stack(); 
    Tree_node *p_node = NULL;

    if(root == NULL){
        return ;
    }

    p_node = root;
    push(stack, p_node);

    while(!is_stack_empty(stack)){
        get_top(stack, (void **)&p_node);
        printf("%c ", p_node->data);
        pop(stack);

        if(p_node->right_child != NULL){
            push(stack, p_node->right_child);
        }

        if(p_node->left_child != NULL){
            push(stack, p_node->left_child);
        }
    }

    destroy_stack(&stack);
     //
    //                  A
    //                /   \
    //               B     G   
    //              / \    / \
    //             C   D  H   J
    //                / \  \
    //               E   F  I
    //
    //  先序遍历：
    //
    //     借助栈，在打印当前节点后分别记录其右、左孩子
    //
    //
    //
    //     
    //    D
    //    G
    //
    //
    //        A  B  C
}

void mid_order_print_nr(Bin_tree root)    //中序非递归遍历
{
    Stack *stack = NULL;
    Tree_node *p_node = NULL;

    if(root == NULL){
        return ;
    }
  
    stack = init_stack();
    p_node = root;

    while(!is_stack_empty(stack) || p_node != NULL){
        while(p_node != NULL){  //首先找到当前节点最左边的节点
            push(stack, p_node);
            p_node = p_node->left_child;
        }

        get_top(stack, (void **)&p_node);
        printf("%c ", p_node->data);
        pop(stack);

        p_node = p_node->right_child;
    }
    destroy_stack(&stack);

    //                  A
    //                /   \
    //               B     G   
    //              / \    / \
    //             C   D  H   J
    //                / \  \
    //               E   F  I
    //
    //           CBEDFAHIGJ
    //
    //         思路：
    //
    //            1.使用栈进行回溯
    //            2.每打印完一个节点，要对其右孩子做处理
    //            3.每个节点都需要不断找到最左边的孩子进行打印
      
}

void last_order_print_nr(Bin_tree root)   //后序非递归遍历
{  
    Stack *stack = NULL;
    Tree_node *p_node = NULL;
    Tree_node *q_node = NULL;

    if(root == NULL){
        return ;
    }

    stack = init_stack();
    p_node = root;

    while(!is_stack_empty(p_node) || p_node != NULL){
        while(p_node != NULL){
            push(stack,p_node);
            p_node = p_node -> left_child;
        }

        get_top(stack,(void**)&p_node);
        if(p_node->right_child == NULL || p_node->right_child == q_node){
            printf("%c ",p_node->data);
            pop(p_node);
            q_node = p_node;
            p_node = NULL;
        }else{
            p_node = p_node -> right_child;
        }

    }

}
void level_order_print(Bin_tree root)    //层序遍历
{
    Queue *queue = NULL;
    Tree_node *p_node = NULL;    

    if(root == NULL){ 
        return ;
    }

    queue = init_queue();
    p_node = root;

    in(queue, p_node);
    while(!is_queue_empty(queue)){
        get_queue_front(queue, (void **)&p_node);
        out(queue);
        printf("%c ", p_node->data);

        if(p_node->left_child != NULL){
            in(queue, p_node->left_child);
        }
   
        if(p_node->right_child != NULL){
            in(queue, p_node->right_child);
        }
    }
    destroy_queue(&queue);
    //
    //                  A
    //                /   \
    //               B     G   
    //              / \    / \
    //             C   D  H   J
    //                / \  \
    //               E   F  I
    //
    //         A  B  G  C  D  H  J  E  F  I
    //
    //   队列进行层序遍历：
    //
    //         --->     --->
    //
    //         A  B  G  C  D  H  J  E  F  I
}

Bin_tree copy_binary_tree(Bin_tree root)    //二叉树的拷贝
{   
    Bin_tree result = NULL;
    //1.如果当前节点存在，则构建当前节点，
    //然后递归地创建当前节点地左右子树部分
    if(root != NULL){
        result = create_node();
        result->data = root->data;
        result->left_child = copy_binary_tree(root->left_child);
        result->right_child = copy_binary_tree(root->right_child);
    }

    return result;
}

Boolean is_binarytree_equal(Bin_tree root1,
                            Bin_tree root2)    //二叉树是否相等
{
    //1.相等：
    //（1）root1和root2都为NULL,相等
    //（2）root1和root2都存在，并且data相等，并且左（右）子树部分都相等
    if(root1 == NULL && root2 == NULL){
        return TRUE;
    }else if((root1 != NULL && root2 != NULL) 
          && root1->data == root2->data
          && is_binarytree_equal(root1->left_child, root2->left_child)
          && is_binarytree_equal(root1->right_child, root2->right_child)){
        return TRUE;
    }else{
        return FALSE;
    }
    //                  A
    //                /   \
    //               B     G   
    //              / \    / \
    //             C   D  H   J
    //                / \  \
    //               E   F  I
    //
    //               B
    //              / \
    //             C   D
}

Boolean is_full_binary_tree(Bin_tree root)   //判断是否是满二叉树
{
    int height = 0;
    int count  = 0;

    if(root == NULL){
        return TRUE;
    }    

    //得到二叉树地高度h和节点个数n
    //
    //判断:
    //    if (2^h - 1) == n,  满二叉树
    //    else   不是满二叉树
    height = get_binarytree_height(root);
    count = get_binarytree_node_count(root);

    return  ((int)pow(2, height) - 1) == count;

}

Boolean is_complete_binary_tree(Bin_tree root)   //判断是否是完全二叉树
{
    //                  A
    //                /   \
    //               B     G   
    //              / \    / 
    //             C   D  H   
    //                                                      /
    //                  
    //
    //     1.层序遍历:
    //
    //     2.分两个状态：(1)被遍历地当前节点既有左孩子又有右孩子（flag = 0）
    //                   (2)右孩子缺失，只有左孩子（flag = 1）
    //                   (3)flag为1的时候，后续的节点不是叶子节点
    //                      不是完全二叉树             
    
}

Boolean is_balance_binary_tree(Bin_tree root);    //判断是否是平衡二叉树
    //1.平衡条件：
    //
    //   左右子树高度差小于等于1，左右子树内部也要平衡



//求二叉树高度地非递归形式（作业）

int get_binarytree_height(Bin_tree root)    //得到二叉树的高度
{
    //                  A
    //                /   \
    //               B     G   
    //              / \    / \
    //             C   D  H   J
    //                / \  \
    //               E   F  I
    if(root == NULL){
        return 0;
    }    
   
    return 1 + max(get_binarytree_height(root->left_child),
                   get_binarytree_height(root->right_child));
}

int get_binarytree_node_count(Bin_tree root)   //得到二叉树的节点个数
{
    if(root == NULL){
        return 0;
    }
 
    //1 + 左（右）子树节点个数

    return 1 + get_binarytree_node_count(root->left_child)
             + get_binarytree_node_count(root->right_child);
}
int get_binarytree_leaf_count(Bin_tree root)    //得到二叉树的叶子节点个数
{
    //root->left_child == NULL && root->right_child == NULL
    if(root == NULL){
        return 0;
    }else if(root->left_child == NULL && root->right_child == NULL){
        return 1;
    }else{
        return get_binarytree_leaf_count(root->left_child)
             + get_binarytree_leaf_count(root->right_child);
    }
}

void swap_left_right(Bin_tree root)   //得到二叉树的镜像
{
//        A      |      A
//       / \     |     / \
//      B   C    |    C   B
//     / \   \   |   /   / \
//    D   E   F  |  F   E   D
   if(root == NULL || (root->left_child == NULL 
                    && root->right_child == NULL)){
       return ;
   }   

   swap(&(root->left_child), &(root->right_child), sizeof(Tree_node *));

   swap_left_right(root->left_child);
   swap_left_right(root->right_child);
}

int get_binarytree_level_count(Bin_tree root, int level)    //得到指定层级的节点个数
{
    //                  A
    //                /   \
    //               B     G   
    //              / \    / \
    //             C   D  H   J
    //                / \  \
    //               E   F  I
    int num_left =  0;
    int num_right = 0; 

    if(root == NULL || level < ONE || level > get_binarytree_height(root)){
        return 0;
    } 
    
    if(level == ONE){
        return 1;
    }

    num_left = get_binarytree_level_count(root->left_child, level - 1); 
    num_right = get_binarytree_level_count(root->right_child, level - 1);

    return num_left + num_right;    
}

Tree_node *find_value(Bin_tree root, char value)    //找到指定值所在的节点
{
    //                  A
    //                /   \
    //               B     G   
    //              / \    / \
    //             C   D  H   J
    //                / \  \
    //               E   F  I
    Tree_node *p_node = NULL;    

    if(root == NULL || root->data == value){
        return root;
    }     
  
    p_node = find_value(root->left_child, value);
    if(p_node == NULL){
        p_node = find_value(root->right_child, value);
    }

    return p_node;
}

static Tree_node *find_common(Bin_tree root,
                              Tree_node *node1, Tree_node *node2){
    // 从根节点开始：
    //
    // 如果node1和node2分别在root左右子树部分，则root为最近公共祖先；
    //
    // 如果在左（右），则对root的左（右）子树部分进行递归的处理，直到满足
    //
    // node1 和node2在不同侧的情况
    if(find_value(root->left_child, node1->data)){
        if(find_value(root->right_child, node2->data)){
            return root;
        }else{ 
            return find_common(root->left_child, node1, node2);
        }
    }else{
        if(find_value(root->left_child, node2->data)){ 
            return root;
        }else{ 
            return find_common(root->right_child, node1, node2);
        }
    }
}

Tree_node *find_common_node(Bin_tree root, Tree_node *node1,
                            Tree_node *node2 )   //找到两个节点的最近公共节点
{
    //                  A
    //                /   \
    //               B     G   
    //              / \    / \
    //             C   D  H   J
    //                / \  \
    //               E   F  I
    //
    //  1.如果出现node1和node2有继承关系，则返回高度较高节点的双亲节点
    //
    //    find_value
    //    find_parent
    //
    int height1 = get_binarytree_height(node1);
    int height2 = get_binarytree_height(node2);

    //处理包含关系
    if(height1 > height2){   
        if(find_value(node1, node2->data) != NULL){
            return find_parent(root, node1);         
        }
    }else if(height1 < height2){
        if(find_value(node2, node1->data) != NULL){
            return find_parent(root, node2);
        }
    }
  
    //处理非包含关系
    return find_common(root, node1, node2);
}

Tree_node *find_parent(Bin_tree root,
                       Tree_node *node)    //找到指定节点的双亲节点
{
    Tree_node *p_node = NULL;

    if(root == NULL || root->left_child == node 
                    || root->right_child == node){
        //root不存在或者root是所要找的双亲节点
        return root;
    }
    p_node = find_parent(root->left_child, node); 
    if(p_node == NULL){ 
        p_node = find_parent(root->right_child, node);
    }
    return p_node;
}

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

int get_largest_dir_count(Bin_tree root);   //得到二叉树的最大路径

    //      
    //      <编程之美> 
    //                  A
    //                /   \
    //               B     G   
    //              / \    / \
    //             C   D  H   J
    //                / \  \
    //               E   F  I
   

// 《TCP/IP详解》 、《unix环境高级编程》、《unix网络编程》、《http权威指南》
//  《linux高性能服务器编程》

