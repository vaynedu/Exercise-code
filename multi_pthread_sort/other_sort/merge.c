#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void merge_sort(int *a,int n);
void Merge_sort(int *a,int left,int right,int *temp);
void merge_array(int *a,int left,int mid,int right,int *temp);
void print_sort(int *a,int n);



void merge_sort(int *a,int n)
{
    int *temp = NULL;
    if(a == NULL || n < 2){
          return ;
    }
    temp = (int *)malloc(sizeof(int) * n);

    Merge_sort(a,0,n-1,temp);
}

void Merge_sort(int *a,int left,int right,int *temp)
{
      int  mid = 0;
      if(left < right){
         mid = left + ((right - left)>>1);
         Merge_sort(a,left,mid,temp);
         Merge_sort(a,mid+1,right,temp);

         merge_array(a,left,mid,right,temp);
      }
}

void merge_array(int *a,int left,int mid,int right,int *temp)
{
    int i = left;
    int j = mid + 1;
    int m = mid;
    int n = right;
    int k = 0;

    while(i<=m && j<=n){
      if(a[i] < a[j]){
         temp[k++] = a[i++];
      }else{
         temp[k++] = a[j++];
      }
    }

    while(i <= m){
         temp[k++] = a[i++];
    }

    while(j <= n){
         temp[k++] = a[j++];
    }

    memcpy(a+left,temp,sizeof(int) * k);

}

void print_sort(int *a,int n)
{
    int i = 0;
    for(i = 0; i < n; i++){
       printf("%d ",a[i]);
    }

    printf("\n");
}

/*int main(int argc,char *argv[])
{
    int a[10] = {14,6,78,25,36,23,32,47,65,12};

    merge_sort(a,10);

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
                                                merge_sort(a,n);
                                                    end  =  clock();
                                                        //print_sort(a,n);

                                                        usr_time = ((double)end - start)/CLOCKS_PER_SEC;
                                                            printf("%lf \n",usr_time);
                                                                return 0;
}   
