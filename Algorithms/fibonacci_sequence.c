/*******************************************************************
*    > F-Name :  fibonacci_sequence.c
*    > Author :  vaynedu
*    > E-mail :  1219345363@qq.com
*    > C-time :  Sat 20 Jul 2019 03:21:38 PM CST
*******************************************************************/

#include<stdio.h>
#include<stdint.h>


uint64_t finonacci(int n)
{
	if( n == 1 || n == 2)
	{
		return 1;
	}
	
	return finonacci(n - 1) + finonacci(n - 2);  


}

int main()
{
	int n = 20;


	printf("n = %d, ", n, finonacci(n));
}

