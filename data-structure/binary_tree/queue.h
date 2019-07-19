#ifndef _QUEUE_H_
#define _QUEUE_H_

#include"dlist.h"

typedef struct Queue{
    Dlist *dlist;   //用双端链表模仿队列
}Queue;

//队列操作接口
Queue   *init_queue(void)                          ;    //初始化队列
void    destroy_queue(Queue **queue)               ;    //队列的销毁
Boolean in(Queue *queue, void *value)              ;    //入队
Boolean out(Queue *queue)                          ;    //出队
Boolean get_queue_front(Queue *queue, void **value);    //得到队首元素
Boolean is_queue_empty(Queue *queue);   //判断队列是否为空
int     get_queue_count(Queue *queue)                    ;    //得到队列元素个数


#endif
