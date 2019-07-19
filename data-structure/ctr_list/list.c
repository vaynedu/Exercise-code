#include "list.h"


static List_node *create_node(void);

//创建头结点 ，只能在本文件使用
static List_node *create_node(void)
{
    List_node *node = (List_node*)Malloc(sizeof(List_node));
    bzero(node,sizeof(List_node));
    return node;
}

 //链表的初始化
List_node *init_list(void)
{
    List_node *head = create_node();
     
    return head;
 
}

//链表的销毁
void destroy_list(List_node **head)
{
     List_node *p_node = NULL;
     if(head == NULL || *head == NULL){
        return ;
     }

     p_node = (*head);

     while((*head) != NULL){
        (*head) = (*head)->next;
        free(p_node);
        p_node = (*head);
     }

     free(*head);
     *head = NULL;

}

//头部插入
Boolean push_front(List_node *head,int value)
{
    List_node *p_node = NULL;
    List_node *node = NULL;
    if(head == NULL){
        return FALSE;
    }

    p_node = head->next;

    node = create_node();
    node->data = value;

    if(p_node == NULL){
        head->next = node;
    }else{
        node->next = head->next;
        head->next = node;
    }
    return TRUE;

}

//尾部插入
Boolean push_back(List_node *head,int value)
{
    List_node *p_node = NULL;
    List_node *node = NULL;
    if(head == NULL){
        return FALSE;
    }

    p_node = head->next;s

    node = create_node();
    node->data = value;

    if(p_node == NULL){
        head->next = node;
    }else{

        while(p_node->next){
            p_node = p_node->next;
        }

        node->next = p_node->next;
        p_node->next = node;
    }
    return TRUE;

}

 //头部删除
Boolean pop_front(List_node *head)
{
    List_node *p_node = NULL;
    if(head == NULL){
        return FALSE;
    }
    p_node = head->next;

    if(p_node == NULL){
        return FALSE;
    }else if(p_node->next == NULL){
        head->next = NULL;
    }else{
        head->next = p_node->next;
    }
    
    free(p_node);
    p_node = NULL;
    
    return TRUE;

}

//尾部删除
Boolean pop_back(List_node *head)
{
    List_node *p_node = NULL;
    List_node *q_node = NULL;
    if(head == NULL){
        return FALSE;
    }
    p_node = head->next;
    q_node = head;

    if(p_node == NULL){
        return FALSE;
    }else if(p_node->next == NULL){
        head->next = NULL;
    }else{
        while(p_node->next != NULL){
            q_node = q_node->next
            p_node = p_node->next;
        }
        free(p_node);
        p_node = NULL;
        q_node->next = NULL;
        
    }
        
    return TRUE;
}

//删除某个指针的值
Boolean delete_list_node(List_node *head,
                         List_node *node)
{
    List_node *p_node = NULL;
    if(head == NULL || head->next == NULL || node == NULL){
        return FALSE;
    }

    p_node = head;
    while(p_node->next != node){
        p_node = p_node->next;
        if(p_node == NULL)
            break;
    }

    if(p_node == NULL){
        reurn FALSE;
    }


    p_node->next = node ->next;
    free(node);
    node = NULL;
   
    return TRUE;

}

//找到指定值的地址 
Boolean find_value_node(List_node *head,
                        int value,
                        List_node **node)
{
    List_node *p_node = NULL;
    if(head == NULL || node == NULL || *node == NULL){
        return FALSE;
    }

    p_node = head->next;
    while(p_node != NULL){
        if(p_node->data == value){
            *node = p_node;
             return TRUE;
        }
        p_node = p_node->next
    }

    return FALSE;

}

//显示链表
void show_list(List_node *head)
{
    List_node *p_node = NULL;
    if(head == NULL){
        return FALSE;
    }

    p_node = head->next;
    while(p_node){
        printf("%d ",p_node->data);
        p_node = p_node->next;
    }
    printf("\n");

}

//升序排序
void sort_list_ascend(List_node *head)
{
    List_node *p_node = NULL;
    List_node *q_node = NULL;
    if(head == NULL || head->next == NULL
       head->next->next == NULL){
        return ;
    }

    for(p_node = head->next; p_node; p_node = p_node->next)
       for(q_node = p_node->next; q_node; q_node = q_node->next)
           if(p_node->data > q_node->data)
           {
                swap(p_node,q_node,sizeof(List_node)-sizeof(List_node*));               

           }

}

//降序排序
void sort_list_descend(List_node *head)
{
    List_node *p_node = NULL;
    List_node *q_node = NULL;
    if(head == NULL || head->next == NULL
       head->next->next == NULL){
        return ;
    }

    for(p_node = head->next; p_node; p_node = p_node->next)
       for(q_node = p_node->next; q_node; q_node = q_node->next)
           if(p_node->data < q_node->data)
           {
                swap(p_node,q_node,sizeof(List_node)-sizeof(List_node*));               

           }

}

//链表的长度
int get_list_length(List_node *head)
{
    int count = 0;
    List_node *p_node = NULL;
    if(head == NULL){
        return ERROR;
    }

    p_node = head->next;
    while(p_node){
        count++;
        p_node = p_node->next;
    }

    return count;

}