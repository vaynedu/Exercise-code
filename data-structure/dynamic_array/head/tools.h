//tools.h文件，包含malloc和realloc的包裹函数
#ifndef _TOOLS_H_
#define _TOOLS_H_

// git svn
#include <stdio.h>
#include <stdlib.h>

#define TRUE   (1)
#define FALSE  (0)
#define ERROR  (-1)
#define ZERO   (0)

void *Malloc(size_t size)            ;    //申请指定大小堆空间
void *Realloc(void *ptr, size_t size);    //重新申请指定大小堆空间

#endif
