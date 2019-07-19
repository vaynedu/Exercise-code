#ifndef  _ITERATOR_H_
#define  _ITERATOR_H_

typedef struct Iterator
{
    void *ptr;
    int  index;
    int  size;           
}Iterator;

/*
 * 正向遍历容器中的元素
 * iter         迭代器
 * container    容器地址
 * */
#define  FOREACH(iter,container) \
            for(container->iter_head(&(iter),container); \
               (iter).ptr; \
               container->iter_next(&(iter),container))

#define  foreach FOREACH

/*
 * 反向便利容器中的元素
 * iter         迭代器
 * container    容器地址
 * */

#define FOREACH_REVERSE(iter,container) \
            for(container->iter_tail(&(iter),container); \
               (iter).ptr; \
               container->(&(iter),container))


#define  foreach_reverse  FOREACH_REVERSE




#endif