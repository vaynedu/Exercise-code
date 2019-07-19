#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "tools.h"
typedef struct Queue
{
    Dlist *dlist;   //封装双端链表为队列的控制信息
}Queue;

//队列的接口
Qeuue *queue_init(void);   //对列的初始化
void destroy_queue(Queue **queue);    //队列的销毁
void in(Queue *queue, void *value);   //入队操作
Boolean out(Queue *queue);    //出队操作
Boolean get_queue_front(Queue *queue, void **value);   //得到队首元素
Boolean is_queue_empty(Queue *queue);   //判断队列是否为空
int get_queue_count(Queue *queue);   //得到队列元素个数

#endif

