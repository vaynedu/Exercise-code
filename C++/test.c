/*==========================================================
     > File Name: test.c
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Tue 19 Jul 2016 06:47:45 PM CST
===========================================================*/
#include <stdio.h>
#include "ds_tools.h"


union X
{
    int32_t a;
    struct{
       int16_t b;
       int16_t c;
    };

};

int main(int argc,char *argv[])
{
    union X x;

    x.a = 0x12345678;
    printf("%d\n",sizeof(union X));
    printf("x.a = %x\n",x.a);
    printf("%x,%x\n",x.b,x.c);

    printf("x.a = %p\n",&x.a);
    printf("x.b = %p\n",&x.b);
    printf("x.c = %p\n",&x.c);

    int i = 0;
    int m = 0x12345678;
    char *n =(char *)&m;

    printf("%x %p\n",*n,n);
    n++;
    printf("%x %p\n",*n,n);
    n++;
    printf("%x %p\n",*n,n);
    n++;
    printf("%x %p\n",*n,n);

    return 0;
}















