//队列操作接口
#include "dlist.h"
#include "queue.h"
#include "tools.h"
#include <strings.h>

Queue   *init_queue(void)    //初始化队列
{
    Queue *queue = (Queue *)Malloc(sizeof(Queue));
    queue->dlist = (Dlist *)malloc(sizeof(Dlist));
    if(queue->dlist == NULL){
        free(queue);
        fprintf(stderr, "the memory is full!\n");
        exit(1);
    }
    bzero(queue->dlist, sizeof(Dlist));
    return queue;
}

void    destroy_queue(Queue **queue)    //队列的销毁
{
    if(queue == NULL || *queue == NULL){
        return ;
    }
    
    //先释放双端链表，再队列控制信息
    destroy_dlist(&((*queue)->dlist));
    free(*queue);
    *queue = NULL;
}

Boolean is_queue_empty(Queue *queue)    //判空
{
    return get_queue_count(queue) == ZERO;
}

Boolean in(Queue *queue, void *value)    //入队
{
    if(queue == NULL || value == NULL){
        return FALSE;
    }
    
    push_back(queue->dlist, value);
    return TRUE;
}

Boolean out(Queue *queue)    //出队
{
    if(queue == NULL || is_queue_empty(queue)){
        return FALSE;
    }
    return pop_front(queue->dlist);
}
Boolean get_queue_front(Queue *queue, void **value)    //得到队首元素
{
    if(queue == NULL || is_queue_empty(queue)){
        return FALSE;
    }
    if(value != NULL){ 
       return get_front(queue->dlist, value);
    }
    return FALSE;
}
int     get_queue_count(Queue *queue)    //得到队列元素个数
{
    if(queue == NULL){
        return -1;
    }
    return get_dlist_count(queue->dlist);
}

