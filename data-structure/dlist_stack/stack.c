#include "stack.h"


//关于栈的接口
Stack *init_stack(void)    //栈的初始化
{
    Stack *stack = (Stack *)Malloc(sizeof(Stack));
    stack->dlist = init_dlist();

    return stack;
}

void destroy_stack(Stack **stack)    //栈的销毁
{
    if(stack == NULL || *stack == NULL){
        return ;
    }
    
    //先释放栈控制信息中双端链表，在释放栈的控制信息
    destroy_dlist( &((*stack)->dlist) );
    free(*stack);
    *stack = NULL;
}

void push(Stack *stack, void *value)    //入栈
{
    if(stack == NULL || value == NULL){
        return ;
    }
    push_front(stack->dlist, value);
}

Boolean pop(Stack *stack)    //出栈
{
    if(stack == NULL || is_stack_empty(stack)){
        return FALSE;
    }
    return pop_front(stack->dlist);
}

Boolean get_top(Stack *stack, void **value)   //得到栈顶元素
{
    if(stack == NULL || is_stack_empty(stack)){
        return FALSE;
    }
    if(value != NULL){
        get_front(stack->dlist, value);
    }
    return TRUE;
}

Boolean is_stack_empty(Stack *stack)    //判断栈是否为空
{
    return get_stack_count(stack) == ZERO; 
}

int get_stack_count(Stack *stack)    //得到栈的元素个数
{
    if(stack == NULL){
        return -1;
    }
    return get_dlist_count(stack->dlist);
}
