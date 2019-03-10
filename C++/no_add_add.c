// 不用加法实现加法

#include <stdio.h>  
#include <stdlib.h>  


#if 0
int add(int a,int b)
{
    char *c = NULL;
    
    c = (char *)a;

    //return (int)&c[b];
    return (int)(c+b);
}
#endif


#if 1
int add(int a,int b)
{
    int sum = 0;
    int temp = 0;

    while(b != 0){
       sum = a ^ b;
       temp = (a & b) << 1;

       a = sum;

       b = temp;
    }

    return a;
}
#endif 

int main()  
{  
    printf("result = %d\n",add(1,2));
    return 0;  
}   