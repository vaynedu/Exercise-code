#include <stdio.h>
#include "hash.h"
#include "ds_tools.h"

#define TEST_SIZE (100)

int int_hash_func(const void *key);
void print_int(void *value);

void print_int(void *value)
{
    printf("%d ", *(int *)value);
}

int int_hash_func(const void *key)
{
    return  *(int *)key;
}

int main(int argc, char **argv)
{
    Hash *hash = init_hash(10, int_hash_func);   //hash表的初始化  
    int *array = (int *)ds_malloc(sizeof(int) * TEST_SIZE);
    int i = 0;

    //生成随机值
    for(i = 0; i < TEST_SIZE; ++i){
        array[i] = rand() % 100; 
    }

    //hash表元素插入
    for(i = 0; i < TEST_SIZE; ++i){
        hash_insert(hash, &array[i]);
    }

    //显示hash表
    show_hash_table(hash, print_int);

    destroy_hash(&hash);
    return 0;
}
