#include <stdio.h>
#include <time.h>
#include <stdlib.h>


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
                    //                     printf("i = %d,j = %d\n",i,j);
                                                // sleep(1);
                                                 quick_sort(a,low,i);
                                                         quick_sort(a,i+1,high);
}



void print_sort(int *a,int n)
{
    int i = 0;
    for(i = 0; i < n; i++){
       printf("%d ",a[i]);
    }

    printf("\n");
}
/*
int main(int argc,char *argv[])
{
    int a[10] = {14,6,78,25,36,23,32,47,65,12};

    print_sort(a,10);

    return 0;
 }*/
int main(int argc,char *argv[])
{

clock_t start = 0;
    clock_t end   = 0;
    
        int i = 0;
            double usr_time = 0.0;
                int *a = NULL;
                    int n = atoi(argv[1]);
                    
                        a = (int *)malloc(sizeof(int ) * n);
                        
                            srand(time(NULL));
                                for(i = 0; i < n;i++){
                                         a[i] = rand()%100000000;
                                             }
                                             
                                                 start = clock();
                                                     quick_sort(a,0,n);
                                                         end  =  clock();                                                                                                                                                         
                                                             //print_sort(a,n);
                                                             
usr_time = ((double)end - start)/CLOCKS_PER_SEC;
    printf("%lf \n",usr_time);
        return 0;
        }
