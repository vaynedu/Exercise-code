#include "ds_tools.h"

//包裹malloc函数
void *ds_malloc(int size)
{
    void *result = NULL;
    result = malloc(size);
    if(result == NULL){
        fprintf(stderr,"malloc error..............................\n");
        exit(1);
    }
    return result;
}
// 自己交换函数
void ds_swap(void *a,void *b,int length)
{
    void *temp = ds_malloc(length);

    memcpy(temp,a,length);
    memcpy(a,b,length);
    memcpy(b,temp,length);

    free(temp);
}

void *ds_realloc(void *ptr, size_t size)
{
    void *result = realloc(ptr, size);
    if(result == NULL){
        fprintf(stderr, "the memory is full!\n");
        exit(1);
    }
    return result;
}
