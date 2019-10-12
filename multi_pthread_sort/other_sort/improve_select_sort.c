#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void improve_select_sort(int *a,int length)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int temp = 0;

    for(i = 0; i < length -1; i++){
         k = i;
         for(j = i + 1; j < length; j++){
             if(a[k] > a[j]){
                  k = j;
             }//end if
         }//end for

         if(i != k){
            temp = a[k];
            a[k] = a[i];
            a[i] = temp;
         }//end if
    }// end for
}// end improve_select_sort


void print_sort(int *a,int n)
{
    int i = 0;
    for(i = 0; i < n; i++){
       printf("%d ",a[i]);
    }//end for

    printf("\n");
}

/*int main(int argc,char *argv[])
{
    int a[10] = {14,6,78,25,36,23,32,47,65,12};

    improve_select_sort(a,10);

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
             a[i] = rand()%1000000;
        }   

    start = clock();
    improve_select_sort(a,n);
    end  =  clock();
    //print_sort(a,n);

    printf ("%d\n", end);
    printf("%d\n", start);
    usr_time = ((double)(end - start)/CLOCKS_PER_SEC);
    printf("%.5lf \n",usr_time);
    return 0;
}
