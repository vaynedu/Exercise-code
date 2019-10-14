#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void bubble_sort(int *a,int length)
{
    int i = 0;
    int j = 0;
    int temp = 0;
    for(i = 0; i < length -1; i++)
        for(j = 0; j < length -i -1;j++)
            if(a[j] > a[j+1]){
                temp  = a[j];
                a[j]  = a[j+1];
                a[j+1]= temp;
            }
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
    bubble_sort(a,n);
    end  =  clock();
    //print_sort(a,n);

    usr_time = ((double)end - start)/CLOCKS_PER_SEC;
    printf("%lf \n",usr_time);
    return 0;
}
