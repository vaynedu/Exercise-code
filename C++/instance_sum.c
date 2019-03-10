#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//代码没有时间写完了，思路就是申请一个额外数组，存储两两之间的质数的和，最后在重新遍历一次b数组
int main()
{
      int i = 0;
      int j = 0;
      int n = 0;
      int m = 0;
      int k = 0;
      int *a= NULL;
      int *b = NULL;
      int count = 0;
      scanf("%d",&n);
                 
      a = (int *)malloc(sizeof(int) * n);
      b = (int *)malloc(sizeof(int) * (n - 1));
      memset(b,0x00,sizeof(int) * (n-1));

      for(i = 0; i < n; i++){
         scanf("%d",&a[i]);
      }
      
      for(i = 0; i < n; i++){
          for(j = a[i];  j < a[i+1]; j++){
               for(k = 2; k < j; k++){
                     if(j % k == 0){
                         break;
                     }
               }
               if(k == j ){
                   b[m]++;
               }
                 //printf("%d\n",b[i]);
          }
           m++;
      }//end for

      
      for(k = 0; k < n - 1; k++){
        for(i = k; i < n -1; i++){
           for(j = k; j <= i; j++){
               count += b[j];
           }
        }
      }//end for

      printf("count = %d\n",count);

      return 0;
}