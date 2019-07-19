//防止头文件的内容被重复包含
#ifndef _DLIST_H_
#define _DLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define ZERO   (0)
#define ONLY_ONE (1)
#define TRUE    (1)
#define FALSE   (0)

struct Dlist;
typedef struct Dlist Dlist;             //双端链表控制信息

struct Dlist_node;
typedef struct Dlist_node Dlist_node;   //双短链表节点信息

typedef unsigned char Boolean;          //C语言中的布尔值

//链表控制信息
struct Dlist{   
    struct Dlist_node *head;   //指向双端链表的头节点
    struct Dlist_node *tail;   //指向双端链表的尾节点
    int               count;   //双端链表中的元素个数

    //释放链表节点数据域
    void    (*free)(void *ptr);    //void (*)(void *ptr)  free;
    //匹配链表节点数据域
    Boolean (*match)(void *val1, void *val2);
    //拷贝链表节点数据域
    void    *(*copy_node)(void *src);
};

//链表节点信息
struct Dlist_node{
    struct Dlist_node *prev;    //前一个节点指针
    struct Dlist_node *next;    //后一个节点指针
    void              *data;    //数据（指针）
};



typedef void (*Print_func)(void *value);
//typedef void (*)(void *value) Print_func;

//双端链表的接口(ADT)
Dlist      *init_dlist(void)                    ;    //链表的初始化
void       destroy_dlist(Dlist **dlist)         ;    //链表的销毁
Boolean    push_front(Dlist *dlist, void *value);    //链表头部插入
Boolean    push_back(Dlist *dlist, void *value) ;    //链表尾部插入
Boolean    pop_back(Dlist *dlist)               ;    //链表尾部删除
Boolean    pop_front(Dlist *dlist)              ;    //链表头部删除
Boolean    insert_prev_node(Dlist *dlist,
             Dlist_node *node, void *value)     ;    //插入指定节点的前边
Boolean    insert_next_node(Dlist *dlist,
             Dlist_node *node, void *value)     ;    //插入指定节点的后边
Boolean    remove_dlist_node(Dlist *dlist,
             Dlist_node *node, void **value)             ;    //删除链表中的节点    
void       print_dlist(Dlist *dlist, Print_func print)   ;    //打印双端链表
Dlist_node  *get_index_node(Dlist *dlist, int index)     ;    //得到下标为index的链表元素
Boolean    get_front(Dlist *dlist, void **value)         ;    //得到链表头节点的数据域
Boolean    get_tail(Dlist *dlist, void **value)          ;    //得到链表尾节点的数据域
int        get_dlist_count(Dlist *dlist)                 ;    //得到链表元素个数


//
void print_int(void *value);    //打印整形值
 
#endif
