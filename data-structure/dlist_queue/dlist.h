#ifndef _DLIST_H_
#define _DLIST_H_

#include "tools.h"

//   A \ esc j .   vim实用技巧

typedef void (*Print_func)(void *value);

//通用双端链表的节点信息
typedef struct Dlist_node{
    struct Dlist_node *prev;    //指向前一个节点
    struct Dlist_node *next;    //指向后一个节点
    void              *data;    //数据域
}Dlist_node;

//通用双端链表的控制信息
typedef struct Dlist{
    struct Dlist_node *head;    //指向头结点
    struct Dlist_node *tail;    //指向尾节点
    int               count;    //链表节点个数
    
    //添加数据域的释放策略
    void (*free)(void *ptr);
    //匹配链表节点数据域是否“相等”
    Boolean (*match)(void *value1, void *value2);
    //拷贝链表节点数据域
    void *(*copy_node)(void *value);
}Dlist;

//通用双端链表的接口
Dlist *init_dlist(void);    //双端链表的初始化
void destroy_dlist(Dlist **dlist);    //双端链表的销毁

Boolean push_front(Dlist *dlist, void *value);    //头部插入
Boolean push_back(Dlist *dlist, void *value);    //尾部插入
Boolean pop_front(Dlist *dlist);    //头部删除
Boolean pop_back(Dlist *dlist);    //尾部删除
Boolean insert_prev(Dlist *dlist, Dlist_node *node, void *value);   //插入到链表某个节点的前边
Boolean insert_next(Dlist *dlist, Dlist_node *node, void *value);   //插入到链表某个节点的后边
Boolean remove_dlist_node(Dlist *dlist, Dlist_node *node, void **value);   //删除某个节点
void    show_dlist(Dlist *dlist, Print_func print);    //显示双端链表信息

Boolean get_front(Dlist *dlist, void **value);   //得到第一个节点数据域
Boolean get_tail(Dlist *dlist, void **value);   //得到最后一个节点数据域
int get_dlist_count(Dlist *dlist);   //得到链表节点数量

#endif


