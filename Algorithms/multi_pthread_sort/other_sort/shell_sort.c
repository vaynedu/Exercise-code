#include <stdio.h>



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
    int a[10] = {14,6,78,25,36,23,32,47,65,12};

    print_sort(a,10);

    return 0;
}
