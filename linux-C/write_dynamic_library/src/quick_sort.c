#include <stdio.h>

void quick_sort(int *a,int low,int high)
{
    int i = low;
    int j = high -1;
    int key = a[low];

    if(a == NULL || low >= high){
         return ;
    }
     while(i < j){
        while(i < j && a[j] > key){
              j--;
        }
        if(i < j){
             a[i++] = a[j];
        }
        while(i < j && a[i] < key){
            i++;
        }
        if(i < j){
             a[j--]= a[i];
        }
     }
        a[i] = key;
        printf("i = %d,j = %d\n",i,j);
       // sleep(1);
        quick_sort(a,low,i);
        quick_sort(a,i+1,high);
}
