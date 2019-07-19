#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE        (1)
#define FALSE       (0)
#define ZERO        (0)
#define ONLY_ONE   (1)
#define ERROR      (-1)


//  定义也就是像C++中的bool类型
typedef unsigned char Boolean;


//工具类接口
void *Malloc(size_t size);               //申请内存的包裹函数
void swap(void *a, void *b, int length);// 实现交换 memcpy内存的拷贝

#endif
