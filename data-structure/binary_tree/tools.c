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

void swap(void *a, void *b, int length)
{
    void *temp = Malloc(length);
 
    memcpy(temp, a, length); 
    memcpy(a, b, length); 
    memcpy(b, temp, length);    

    free(temp);
}
