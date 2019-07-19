#ifndef _LIST_H_
#define _LIST_H_

#include "tools.h"


typedef struct List_node
{
    int     data;            //数据域
    struct  List_node *next; //指针域
}List_node;


List_node *init_list(void);        //链表的初始化
void destroy_list(List_node **head); //链表的销毁
Boolean push_front(List_node *head,int value);//头部插入
Boolean push_back(List_node *head,int value);//尾部插入
Boolean pop_front(List_node *head);   //头部删除
Boolean pop_back(List_node *head);    //尾部删除
Boolean delete_list_node(List_node *head,  
                         List_node *node); //删除某个指针的值
Boolean find_value_node(List_node *head,
                        int value,
                        List_node **node); //找到指定值的地址 
void show_list(List_node *head);           //显示链表
void sort_list_ascend(List_node *head);    //升序排序
void sort_list_descend(List_node *head);   //降序排序
int get_list_length(List_node *head);      //链表的长度



#endif