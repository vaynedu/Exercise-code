#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void min_max_value(int *a,int length,int *max,int *min)
{
    int i = 0;
    *max = a[0];
    *min = a[0];
    for(i = 1; i < length; i++ ){
        if(*max < a[i] )
            *max = a[i];
        if(*min > a[i])
            *min = a[i];
    }//end for
}

void count_sort(int *a,int length)
{
      int  i = 0;
      int  j = 0;
      int max = 0;
      int min = 0;
      int c_size = 0;
      int *count = NULL;
      if(a == NULL || length < 2){
           return ;
      }// end if

      min_max_value(a,length,&max,&min);
      c_size = max - min + 1;

      printf("max = %d,min = %d,c_size = %d\n",max,min,c_size);
      count = (int *)malloc(sizeof(int) * c_size);
      bzero(count,sizeof(int) * c_size);

      for(i = 0; i < length; i++){
          count[a[i] - min]++;
      }//end for

      for(i = 0; i < c_size; i++){
         while(count[i]--){
             a[j++] = i + min;
         }//end while
      }//end for
}


void print_sort(int *a,int n)
{
    int i = 0;
    for(i = 0; i < n; i++){
       printf("%d ",a[i]);
    }

    printf("\n");
}

int main(int argc,char *argv[])
{
    int a[10] = {18,19,18,19,19,29,21,20,25,27};

    count_sort(a,10);

    print_sort(a,10);

    return 0;
}
