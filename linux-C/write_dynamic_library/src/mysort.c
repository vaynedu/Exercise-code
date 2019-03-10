#include <stdio.h>

int main(int argc,char *argv[])
{
    int i = 0;
    int a[10] = {7,14,23,6,8,7,14,6,78,12};
    quick_sort(a,0,10);
    for(i = 0; i < 10; i++){
        printf("%d ",a[i]);
    }
    printf("\n");
    return 0;
}

