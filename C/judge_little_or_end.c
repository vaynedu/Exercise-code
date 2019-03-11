/*==========================================================
     > File Name: test.c
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Tue 19 Jul 2016 06:47:45 PM CST
===========================================================*/
#include <stdio.h>
#include <stdint.h> 

// 大端字节序：高字节存放在低地址
// 小端字节序：高字节存放在高地址
/*==========================================================
 *          1   2
 *   x.c    3   4
 *          5   6   
 *  x.a x.b 7   8
 * =========================================================*/

//print
/*==========================================================
sizeof(union X) = 4
x.a = 12345678
x.b = 5678, x.c = 1234
x.a = 0x7fffa4fcc350
x.b = 0x7fffa4fcc350
x.c = 0x7fffa4fcc352
---------------------------------------------------------------
12345678 0x7fffa4fcc34c
78 0x7fffa4fcc34c
56 0x7fffa4fcc34d
34 0x7fffa4fcc34e
12 0x7fffa4fcc34f
---------------------------------------------------------------
little
 *=========================================================*/





union X
{
    int32_t a;
    struct{
       int16_t b;
       int16_t c;
    };

};

union U
{
   int32_t value;
   char c;
};



int main(int argc,char *argv[])
{
    union X x;

    x.a = 0x12345678;
    printf("sizeof(union X) = %d\n",sizeof(union X));
    printf("x.a = %x\n",x.a);
    printf("x.b = %x, x.c = %x\n",x.b,x.c);

    printf("x.a = %p\n",&x.a);
    printf("x.b = %p\n",&x.b);
    printf("x.c = %p\n",&x.c);

    printf("---------------------------------------------------------------\n");
    int i = 0;
    int m = 0x12345678;
    char *n =(char *)&m;
    
    printf("%x %p\n",m,&m);

    printf("%x %p\n",*n,n);
    n++;
    printf("%x %p\n",*n,n);
    n++;
    printf("%x %p\n",*n,n);
    n++;
    printf("%x %p\n",*n,n);

    printf("---------------------------------------------------------------\n");
    
    union U u; 
    u.value=0x12345678;

    if(u.c == 0x78){
       printf("little\n");
    }else{
       printf("big\n");
     }
    

    return 0;
}

