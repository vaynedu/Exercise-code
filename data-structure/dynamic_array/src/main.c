#include "dynamic_array.h"
#include "tools.h"
#include "iterator.h"
#include <stdio.h>


void print_int(void *value);

void print_int(void *value)
{
    printf("%d ",*(int *)value);
}

int main(int argc,char *argv[])
{
    Array *array = NULL;
    Iterator  iter;
    int arr[] = {1,2,5,125,521};
    int arr_len = sizeof(arr) / sizeof(arr[0]);
    int i = 0;


    array = init_array(20);  //初始化动态数组

    for(i = 0; i < arr_len; i++){
        array->push_back(array,&arr[i]);
    }

    //打印动态数组元素
    foreach(iter,array){
        print_int(iter.ptr);
    }
    printf("\n");

    //头部删除元素
    for(i = 0; i < 3; i++){
        array->pop_front(array);
    }

    //打印动态数组元素
    foreach(iter,array){
        print_int(iter.ptr);
    }
    printf("\n");

    //销毁动态数组
    destroy_array(&array);
    
    return 0;
}