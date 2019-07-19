#ifndef _STACK_H_
#define _STACK_H_

#include "dlist.h"

//栈的控制信息
typedef struct Stack
{
    Dlist *dlist;   //用双端链表的控制信息直接封装栈
}Stack;

//关于栈的接口
Stack *init_stack(void);    //栈的初始化
void destroy_stack(Stack **stack);    //栈的销毁
void push(Stack *stack, void *value);    //入栈
Boolean pop(Stack *stack);    //出栈
Boolean get_top(Stack *stack, void **value);   //得到栈顶元素
Boolean is_stack_empty(Stack *stack);    //判断栈是否为空
int get_stack_count(Stack *stack);    //得到栈的元素个数

#endif
