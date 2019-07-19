#include "queue.h"


//队列的初始化
Queue *init_queue(void)
{
    Queue *queue = (Queue *)Malloc(sizeof(Queue));
    queue->dlist = init_dlist();
    bzero(queue,sizeof(Queue));

    return queue;
}

//队列的销毁
void destroy_queue(Queue **queue)
{
    if(queue == NULL || *queue == NULL){
      return ;
    }
     
    destroy_dlist(&((*queue)->dlist));
    free(*queue);
    *queue = NULL;

}

//入队操作
void in_queue(Queue *queue,void *value)
{
   if(queue == NULL || value == NULL){
      return ;
   }

   push_back(queue->dlist,value);

}

//出队操作
Boolean out_queue(Queue *queue)
{
    if(queue == NULL || is_queue_empty(queue)){
      return FALSE;
    }

    pop_front(queue->dlist);

    return TRUE;
}


//得到队首元素
Boolean is_queue_empty(Queue *queue)
{

  return queue->dlist->count == ZERO;
}


//判断队列是否为空
Boolean get_queue_front(Queue *queue,void **value)
{
  if(queue == NULL ||  value == NULL 
    || is_stack_empty(queue)
    || get_front(queue->dlist,value) == FALSE){
        return FALSE;
   }
   
  return TRUE;
}


//得到队列元素个数
int get_queue_count(Queue *queue)
{
  if(queue == NULL){
    return ERROR;
  }
  return get_dlist_count(queue->dlist);
}




















