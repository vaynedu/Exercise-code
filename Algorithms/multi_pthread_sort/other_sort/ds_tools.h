#ifndef DS_TOOLS_H
#define DS_TOOLS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define  TRUE    (1)
#define  FALSE   (0)
#define ERROR  (-1)
#define ZERO   (0)



#define return_if_fail(p) if(!(p))    \
        {printf("%s:%d failed\n",     \
        __func__,__LINE__); return;}  \



#define return_val_if_fail(p,ret) if(!(p))  \
        {printf("%s:%d failed\n",           \
         __func__,__LINE__); return (ret);} \
        


typedef unsigned char Boolean;




// 包裹malloc函数
void *ds_malloc(int size);

// 自己的交换函数
void ds_swap(void *a,void *b,int length);

//重新申请指定大小堆空间
void ds_realloc(void *ptr,size_t size);

#endif
