#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TRUE  (1)
#define FALSE (0)
#define ZERO  (0)

typedef unsigned char Boolean;

//工具类接口
void *Malloc(size_t size);
void swap(void *a, void *b, int length);

#endif
