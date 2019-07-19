#include "dlist.h"

static Dlist_node *create_node(void);

static Dlist_node *create_node(void)
{
    Dlist_node *node = (Dlist_node *)ds_malloc(sizeof(Dlist_node));
    bzero(node, sizeof(Dlist_node));

    return node;
}

//通用双端链表的接口
Dlist *init_dlist(void)    //双端链表的初始化
{
    Dlist *dlist = (Dlist *)ds_malloc(sizeof(Dlist));
    bzero(dlist, sizeof(Dlist));

    return dlist; 
}

void destroy_dlist(Dlist **dlist)    //双端链表的销毁
{
    Dlist_node *p_node = NULL;

    if(dlist == NULL || *dlist == NULL){  
        return ;
    }

    //先释放链表节点信息，再释放链表控制信息
    //
    //在释放链表节点信息时，需要判断是否释放数据域所指向的空间
    p_node = (*dlist)->head;
    while((*dlist)->head != NULL){
        (*dlist)->head = p_node->next;
        if((*dlist)->free != NULL){
            (*dlist)->free(p_node->data);
        }
        free(p_node);
        p_node = (*dlist)->head;
    }

    free(*dlist);
    *dlist = NULL;
}

Boolean push_front(Dlist *dlist, void *value)    //头部插入
{
    Dlist_node *node = NULL;

    if(dlist == NULL || value == NULL){
        return FALSE;
    }

    //生成链表节点
    node = create_node();
    node->data = value;

    if(dlist->count == ZERO){    //之前链表为空
        dlist->head = dlist->tail = node;  
    }else{
        node->next = dlist->head;
        dlist->head->prev = node;
        dlist->head = node;
    }
    dlist->count++;
    return TRUE;
}

Boolean push_back(Dlist *dlist, void *value)    //尾部插入
{
    Dlist_node *node = NULL;

    if(dlist == NULL || value == NULL){
        return FALSE;
    }

    node = create_node();
    node->data = value;

    //对链表为空或非空区别处理
    if(dlist->count == ZERO){
        dlist->head = dlist->tail = node;
    }else{
        node->prev = dlist->tail;
        dlist->tail->next = node;
        dlist->tail = node;
    }
    dlist->count++;
    return TRUE;
}

Boolean pop_front(Dlist *dlist)    //头部删除
{
    Dlist_node *p_node = NULL;

    if(dlist == NULL || dlist->count == ZERO){
        return FALSE;
    }

    p_node = dlist->head;

    if(dlist->count == ONLY_ONE){
        dlist->head = dlist->tail = NULL;
    }else{
        dlist->head = p_node->next;
        dlist->head->prev = NULL;
    }

    //在释放节点信息之前，先要判断数据域的指向是否需要释放
    if(dlist->free != NULL){
        dlist->free(p_node->data);
    }

    free(p_node);
    dlist->count--;
    return TRUE;
} 

Boolean pop_back(Dlist *dlist)    //尾部删除
{
    Dlist_node *p_node = NULL;

    if(dlist == NULL || dlist->count == ZERO){
        return FALSE;
    }

    //让p_node 指向最后一个节点
    p_node = dlist->tail;

    if(dlist->count == ONLY_ONE){
        dlist->head = dlist->tail = NULL;
    }else{
        dlist->tail = p_node->prev;
        dlist->tail->next = NULL;
    } 

    if(dlist->free != NULL){
        dlist->free(p_node->data);
    }
    free(p_node); 
    dlist->count--;
    return TRUE;
}

Boolean insert_prev(Dlist *dlist, Dlist_node *node, void *value)   //插入到链表某个节点的前边
{
    Dlist_node *p_node = NULL;

    if(dlist == NULL || node == NULL || value == NULL){
        return FALSE;
    }

    //创建节点存储value
    p_node = create_node();
    p_node->data = value;

    //进行节点的插入
    //1.当前链表值有一个节点
    //2.一般情况（多个节点）

    p_node->next = node;
    p_node->prev = node->prev;
    if(node->prev == NULL){    //node为第一个节点
        dlist->head = p_node;
    }else{    //不是第一个节点
        node->prev->next = p_node;
    }
    node->prev = p_node;
    dlist->count++;
}

Boolean insert_next(Dlist *dlist, Dlist_node *node, void *value)   //插入到链表某个节点的后边
{
    return FALSE;
}

Boolean remove_dlist_node(Dlist *dlist, Dlist_node *node, void **value)   //删除某个节点
{
    return FALSE;
}

void    show_dlist(Dlist *dlist, Print_func print)    //显示双端链表信息
{
    Dlist_node *p_node = NULL;

    if(dlist != NULL && dlist->count > 0){
        for(p_node = dlist->head; p_node; p_node = p_node->next){
            print(p_node->data);
        }
        printf("\n");
    }  
}

Boolean get_front(Dlist *dlist, void **value)   //得到第一个节点数据域
{
    if(dlist == NULL || dlist->count == ZERO){
        return FALSE;
    }
    
    if(value != NULL){
        *value = dlist->head->data;
    }
    return TRUE;
}

Boolean get_tail(Dlist *dlist, void **value)   //得到最后一个节点数据域
{
    if(dlist == NULL || dlist->count == ZERO){ 
        return FALSE;
    }
    
    if(value != NULL){
        *value = dlist->tail->data;
    }
    return TRUE;
}

int get_dlist_count(Dlist *dlist)   //得到链表节点数量
{
    if(dlist == NULL){
        return ERROR;
    }
    return dlist->count;
}



