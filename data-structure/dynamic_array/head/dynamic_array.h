#ifndef  _DYNAMIC_ARRAY_H_
#define  _DYNAMIC_ARRAY_H_

#include "tools.h"
#include "iterator.h"


typedef struct Array Array;
typedef unsigned char Boolean;

typedef  struct Array
{
     void   **data;   //动态数组数据
     int    capacity; //动态数组的容量
     int    count;    //数组元素个数

     void      *(*copy)(void *src_value);   //元素的拷贝
     Boolean    (*match)(void *value1,void *value2);//元素的匹配
     void       (*free)(void *ptr);   //元素的释放

     //动态数组的操作
     Boolean  (*push_front)(Array *array,void *value);
     Boolean  (*push_back)(Array *array,void *value);
     Boolean  (*pop_front)(Array *array);
     Boolean  (*pop_back)(Array *array);

     //迭代器操作
     void *(*iter_head)(Iterator *iter,Array *array);
     void *(*iter_tail)(Iterator *iter,Array *array);
     void *(*iter_next)(Iterator *iter,Array *array);
     void *(*iter_prev)(Iterator *iter,Array *array);
}Array;


//动态数组操作的接口
Array *init_array(int init_size);
void  destroy_array(Array **array);
void array_clean(Array *array);

Boolean array_prev_insert(Array *array,int index,void *value);
Boolean array_next_insert(Array *array,int index,void *value);
int     get_array_count(Array *array);
void   *get_array_index(Array *array,int index);
Boolean delete_index_value(Array *array,int index);
Boolean delete_range_value(Array *array,int begin,int end);
int find_value(Array *array,void *value);

#endif











