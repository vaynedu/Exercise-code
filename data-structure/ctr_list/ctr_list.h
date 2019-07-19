#ifndef _CTR_LIST_H_
#define _CTR_LIST_H_

#include "tools.h"

struct List_node;    //声明一个类型

//链表控制信息
typedef struct List
{
    struct List_node *head;    //指向链表头部
    struct List_node *tail;    //指向链表尾部
    int              count;    //链表节点数量
}List;

//链表节点信息
typedef struct List_node
{
    int               data;    //数据域
    struct List_node *next;    //指针域
}List_node;


//  lua
//  C语言接口与实现   lcc

//链表的接口
List      *init_list(void)                        ;    //链表的初始化
void      destroy_list(List **list)               ;    //链表的销毁
Boolean   push_front(List *list, int value)       ;    //头部插入
Boolean   push_back(List  *list, int value)       ;    //尾部插入
Boolean   pop_front(List *list)                   ;    //头部删除
Boolean   pop_back(List *list)                    ;    //尾部删除
void      show_list(List *list)                   ;    //显示链表信息
void      sort_list_ascend(List *list)            ;    //升序排列
void      sort_list_descent(List *list)           ;    //降序排列
int       get_list_count(List *list)              ;    //得到链表节点数量

///
List      *merge_two_lists(List *list1, List *list2)       ;    //合并两个有序链表
List      *merge_two_lists_recure(List *list1, List *list2);    //合并两个有序链表（递归）
List_node *find_revise_node(List *list, int num)           ;   //找到链表的倒数第num个节点
List_node *find_mid_node(List *list)                       ;    //找到链表的中间节点
List      *reverse_list(List *list)                        ;    //逆置一个链表
List      *list_dump(List *list)                           ;    //链表的拷贝
void      reverse_show_list(List *list)                    ;    //逆序输出链表信息
Boolean   is_list_intersect(List *list1, List *list2)      ;    //判断链表是否有交点
List_node *get_first_common_node(List *list1, List *list2) ;    //得到第一个交点
void      delete_one_node(List *list, List_node *node)     ;    //在O（1）的时间复杂度删除节点

Boolean has_circle(List *list,List_node **instersect)      ;    //判断一个链表是否有环
List_node *find_circle_first_node(List *list)              ;    //找到循环链表的第一个节点