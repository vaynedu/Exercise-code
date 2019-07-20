/*******************************************************************
*    > F-Name :  cal_100_factorial.c
*    > Author :  vaynedu
*    > E-mail :  1219345363@qq.com
*    > C-time :  Sat 20 Jul 2019 07:28:35 PM CST
*******************************************************************/



/*
 *
 * 计算100的阶乘
 *
 * 目前最大整数应该就是uint64_t 
 *
 * 如果想存更大的数字怎么办? 比如100的阶乘?  就可以用数组来实现
 *
 * */


#include<stdio.h>
#include<string.h>

#define MAXLEN  500
int a[MAXLEN];

void factorial(int *a,int n,int *start)
{
    int i = 0;
    int j = 0;
    int temp = 0;
    int carry_bit = 0;
    int k = MAXLEN - 2;
    int factorial_num = 2;

    a[MAXLEN - 1] = 1;                                                                                                                                                                       

    /*
	 * 每次阶乘一个数字，从末尾开始计算
	 *
	 * 将各个位置数字全部乘一遍，carry_bit表示进位
	 *
	 * 其实也是用数组，按照乘法的原理
	 * */


    for(i = 1; i < n; i++){
        for(j = MAXLEN - 1; j > k;j--){
             temp = a[j] * factorial_num + carry_bit;
             a[j] = temp % 10;
             carry_bit = temp /10;
        }//end for

        while(carry_bit){
             a[k--] += carry_bit % 10;
             carry_bit /= 10;
        }//end for

        factorial_num++;
    }//end for

    *start = k;

}


void print_array(int *a,int start)
{    
     int i = 0;
     
     for(i = start + 1; i < MAXLEN; i++){
         printf("%d",a[i]);
     }//end for
     
     printf("\n");
}


int main(int argc,char *argv[])
{
    int n = 100;
    int start = 0;

    //scanf("%d",&n);

    factorial(a,n,&start);

    print_array(a,start);

    return 0;
}
