#include "dlist.h"
#include "tools.h"


void       destroy_dlist(Dlist **dlist)    //链表的销毁
{
    Dlist_node *p_node = NULL;

    if(dlist == NULL || *dlist == NULL){
        return ;
    }

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

static Dlist_node *buy_node(void)
{
    Dlist_node *result = (Dlist_node *)Malloc(sizeof(Dlist_node));
    bzero(result, sizeof(Dlist_node));

    return result;
}

Boolean    push_front(Dlist *dlist, void *value)    //链表头部插入
{
    Dlist_node *node = NULL;

    if(dlist == NULL || value == NULL){
        return FALSE;
    }
 
    node = buy_node();
    node->data = value;

    if(dlist->count == ZERO){    //链表没有元素时
        dlist->head = dlist->tail = node;
    }else{
        node->next = dlist->head;
        dlist->head->prev = node;
        dlist->head = node;
    }
    dlist->count++;
    return TRUE;
}

Boolean    push_back(Dlist *dlist, void *value)    //链表尾部插入
{
    Dlist_node *node = NULL;

    if(dlist == NULL || value == NULL){
        return FALSE;
    }

    node = buy_node();
    node->data =value;

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
Boolean    pop_back(Dlist *dlist)    //链表尾部删除
{
    Dlist_node *p_node = NULL;

    if(dlist == NULL || dlist->count == ZERO){
        return FALSE;
    }

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
Boolean    pop_front(Dlist *dlist)    //链表头部删除
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
    if(dlist->free != NULL){
        dlist->free(p_node->data);
    }
    free(p_node);
    dlist->count--;
    return TRUE;
}

Dlist_node *get_index_node(Dlist *dlist, int index)   //得到下标为index的链表节点
{
    Dlist_node *node = NULL;
    int move_count = 0;

    if(dlist == NULL || dlist->count == ZERO
    || index < ZERO || index >= dlist->count){
         return NULL;
    }

    node = dlist->head;
    move_count = index;

    //找到指定下标元素
    while(move_count--){
        node = node->next;
    }

    return node;
}

Boolean    remove_dlist_node(Dlist *dlist, 
               Dlist_node *node, void **value)    //删除指定节点
{
    if(dlist == NULL || node == NULL){
        return FALSE;
    }

    if(value != NULL){    //取得被删除节点数据域信息
        *value = node->data;
    }

    if(node->next == NULL){    //node在尾部
        pop_back(dlist);
    }else if(node->prev == NULL){
        pop_front(dlist);
    }else{
        node->prev->next = node->next;
        node->next->prev = node->prev;
        if(dlist->free != NULL){
            dlist->free(node->data); 
        }
        free(node);   //Free(node)
        dlist->count--;
    
        /*
 *
 * #define Free(node) (node->prev->next = node->next;) \
 *                    (node->next->prev = node->prev;) \
 *                    
 *
 * */
    }
    return TRUE;
}

Boolean    insert_next_node(Dlist *dlist,
               Dlist_node *node, void *value)    //插入到指定节点的后边
{
    Dlist_node *p_node = NULL;

    if(dlist == NULL || node == NULL || value){
        return FALSE;
    }
  
    p_node = buy_node();
    p_node->data = value;

    p_node->prev = node;
    p_node->next = node->next;
    if(node->next == NULL){
        dlist->tail = p_node;
    }else{
        node->next->prev = p_node;
    }
    node->next = p_node;
    dlist->count++;
    return TRUE;
}

Boolean    insert_prev_node(Dlist *dlist,
               Dlist_node *node, void *value)    //插入到指定节点的前边
{
    Dlist_node *p_node = NULL;

    if(dlist == NULL || node == NULL || value == NULL){
        return FALSE;
    }
   
    p_node = buy_node();
    p_node->data = value;

    //进行插入操作
    p_node->next = node;
    p_node->prev = node->prev;
    if(node->prev == NULL){    //node为第一个节点
        dlist->head = p_node;
    }else{    //node不是第一个节点
        node->prev->next = p_node;
    }
    node->prev = p_node;
    dlist->count++; 
    return TRUE;
}

void print_int(void *value)
{
    printf("%d ", *(int *)value);
}
void print_dlist(Dlist *dlist, Print_func print)    //打印链表信息
{
    Dlist_node *p_node = NULL;

    if(dlist == NULL || dlist->count == ZERO){
        return ;
    }

    for(p_node = dlist->head; p_node ; p_node = p_node->next){
        print(p_node->data);
    }
    printf("\n");
}


Dlist *init_dlist(void)    //双端链表的初始化
{
    Dlist *dlist = NULL; 
   
    dlist = (Dlist *)Malloc(sizeof(Dlist));
    bzero(dlist, sizeof(Dlist));   //对dlist进行初始化

    return dlist;
}

Boolean get_front(Dlist *dlist, void **value)
{
    if(dlist == NULL || dlist->count == ZERO){
        return FALSE;
    }
    
    if(value != NULL){
        *value = dlist->head->data;
    }
    return TRUE;
}

Boolean get_tail(Dlist *dlist, void **value)
{
    if(dlist == NULL || dlist->count == ZERO){ 
        return FALSE;
    }
   
    if(value != NULL){
         *value = dlist->tail->data;
    }
    return TRUE;
}

int get_dlist_count(Dlist *dlist)
{
    if(dlist == NULL){
        return -1;
    }
    return dlist->count;
}
