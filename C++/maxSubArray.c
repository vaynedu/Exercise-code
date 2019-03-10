//子数组和最大  动态规划dp
#include <stdio.h>  
#include <stdlib.h>  


#define mymax(a,b) ((a)>(b)?(a):(b))

int main()  
{  
    int i = 0;
    int a[8] = {1,-2,3,10,-4,7,2,-5};
    int dp[8] = {0};
    int answer = a[0];

    dp[0] = a[0];
    
    for(i =1; i < 8; i++){
       dp[i] = mymax(dp[i-1]+a[i],a[i]);
       answer = mymax(answer,dp[i]);
    }

    printf("answer = %d\n",answer);
    return 0;  
}   



