include <stdio.h>
#include "stack.h"

int main(int argc, char **argv)
{
    Stack *stack = init_stack();    //栈的初始化

    int array[] = {12, 23, 34, 45, 56, 67, 78, 89, 90, 100}; 
    int length = sizeof(array) / sizeof(array[0]);
    int i = 0;
    int *value = NULL; 

    //入栈数列  
    for(i = 0; i < length; ++i){
        push(stack, &array[i]);
    }

    //出栈
    for(i = 0; i < length; ++i){
        get_top(stack, (void **)&value);
        pop(stack);
        printf("%d ", *value);
    }
   
    printf("\n");

    destroy_stack(&stack);    //栈的销毁
    return 0;
}
