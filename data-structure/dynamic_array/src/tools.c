//tools.c文件
#include "tools.h"

void *Malloc(size_t size)
{
    void *result = malloc(size);
    if(result == NULL){
        fprintf(stderr, "the memory is full!\n");
        exit(1);
    }
    return result;
}

void *Realloc(void *ptr, size_t size)
{ 
    void *result = realloc(ptr, size);
    if(result == NULL){
        fprintf(stderr, "the memory is full!\n");
        exit(1);
    }
    return result;
}