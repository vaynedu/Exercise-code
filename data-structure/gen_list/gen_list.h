#ifndef _GEN_LIST_H_
#define _GEN_LIST_H_

#define MATCH     (0)
#define NOT_MATCH (1)

#include "tools.h"


//广义表节点类型
typedef enum {
    HEAD = 0,    //子表类型（头结点）
    INT,         //整型类型     
    CHARACTER,   //子符类型
    LIST         //子表地址
}Node_type;

//广义表的节点结构
typedef struct Gen_node{
    //1.标志（类型）  int char list head
    Node_type          n_type;
    //2.实际存储的值   int  char  (Gen_node *)
    union {
        int         int_value;
        char       char_value;
        int         head_flag;  
        struct Gen_node *head;
    } value;    //根据节点类型选取不同的值
    //3.next指针
    struct Gen_node     *next;    //指向广义表的下一个元素
}Gen_node;

typedef struct Gen_node *Gen_list;

//广义表接口
Gen_list init_genlist(char *input_str)      ;    //广义表的创建   
void     destroy_genlist(Gen_list *gen_list);    //广义表的销毁
int      get_genlist_count(Gen_list gen_list);    //得到广义表的元素个数
int      get_genlist_depth(Gen_list gen_list);    //得到广义表的深度
Gen_list copy_genlist(Gen_list gen_list)     ;    //广义表的拷贝
void show_genlist(Gen_list gen_list)        ;    //显示广义表信息



//(15, 'c', (20, 'd', (30, 'f')), ('g', 'i'), 60)
//
// char *str1 = "(12)";
//
// char str2[5] = {0};
//
// strncpy(str2, str1 + 1, 2);
//
//获取广义表元素内容：
//
//1.去掉括号
//2.以逗号作为分界线，取出其中的元素

//
//('c')
//
#endif
