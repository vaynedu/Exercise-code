#include <stdio.h>

void select_sort(int *a,int length)
{
    int  i = 0;
    int  j = 0;
    int  temp =  0;
    for(i = 0; i < length -1;i++)
        for(j = i + 1; j < length; j++)
            if(a[i] > a[j]){
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
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
    int a[10] = {14,6,78,25,36,23,32,47,65,12};

    select_sort(a,10);

    print_sort(a,10);

    return 0;
}
