#include <stdio.h>
#include<stdlib.h>
#include <time.h>

void insert_sort(int *a,int length)
{
    int i = 0;
    int j = 0;
    int key = 0;

    for(i = 0; i < length; i++){
         key = a[i];
         for(j = i -1; j >= 0 && a[j] > key; j--){
              a[j+1] = a[j];
         }
         a[j+1] = key;
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

/*int main(int argc,char *argv[])
{
    int a[10] = {14,6,78,25,36,23,32,47,65,12};

    insert_sort(a,10);

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
                                                     a[i] = rand()%1000000000;
                                                         }

                                            start = clock();
                                                insert_sort(a,n);
                                                    end  =  clock();
                                                        //print_sort(a,n);

                                                        usr_time = ((double)end - start)/CLOCKS_PER_SEC;
                                                            printf("%lf \n",usr_time);
                                                                return 0;
}   
