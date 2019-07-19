#include "ctr_list.h"


static List_node *create_node(void);


static List_node *create_node(void)
{
    List_node *node = (List_node*)Malloc(sizeof(List_node));
    bzero(node,sizeof(List_node));

    return node;
}


//链表的初始化
List      *init_list(void)
{
    List *list = (List *)Malloc(sizeof(List));
    bzero(list,sizeof(List));

    return list;
}  


#if 0 
//链表的销毁  自己写的
void      destroy_list(List **list)             
{
    List_node *p_node = NULL;
    if(list == NULL || *list == NULL){
        return ;
    }
    p_node = (*list)->head;

    while(p_node != NULL){
        (*list)->head = (*list)->head->next;
        free(p_node);
        p_node = (*list)->head;
    }

    free(*list);
    *list = NULL;
}
#endif
//链表的销毁
void      destroy_list(List **list)                   
{

    //              list
    //             /
    //         list_head  
    //          /
    //      | head | tail | count |
    //          \      \       n + 1
    //             
    //            \           \
    //            node->node2->node3
    if(list == NULL || *list == NULL){
        return ;
    }
   
    //  链表删除步骤：
    //  1.删除链表节点信息;
    while((*list)->count){   //头部删除链表节点
        pop_front(*list);
    }
    //  2.删除链表控制信息.
    free(*list);
    *list = NULL;
}

//头部插入
Boolean   push_front(List *list, int value)      
{
    List_node *node = NULL;
    if(list == NULL){
        return FALSE;
    }

    node = create_node();
    node->data = value;

    if(list->count == ZERO){
        list->head = list->tail = node;
    }else{
        node->next = list->head;
        list->head = node;
    }

    list->count++;

    return TRUE;

}

//尾部插入
Boolean   push_back(List  *list, int value)       
{
    List_node *node = NULL;
    if(list == NULL){
        return FALSE;
    }

    node = create_node();
    node->data = value;

    if(list->count == ZERO){
        list->head = list->tail = node;
    }else{

        list->tail->next = node;
        list->tail = node;
    }

    list->count++;

    return TRUE;

}

//头部删除
Boolean   pop_front(List *list)                   
{
    List_node *p_node = NULL;
    if(list == NULL || list->count == 0){
        return FALSE;
    }

    p_node = list->head;

    if(list->count == ONLY){
        list->head = list->tail = NULL;
    }else{
        list->head = list->head->next;
    }

    free(p_node);
    p_node = NULL;
    list->count--;

    return TRUE;

}

#if 0
//尾部删除  自己写的
Boolean   pop_back(List *list)                    
{
    List_node *p_node = NULL;
   List_node *q_node = NULL; 
    if(list == NULL || list->count == 0){
        return FALSE;
    }

    p_node = list->head;
    q_node = list->head;
    if(list->count == ONLY){
        list->head = list->tail = NULL;
    }else{
        while(q_node->next->next != NULL){
            q_node = q_node->next;
        }
        p_node = q_node->next
        list->tail = q_node;
        list->tail->next = NULL;      
    }

    free(p_node);
    p_node = NULL;
     list->count--;

    return TRUE;


}
#endif 
//尾部删除
Boolean   pop_back(List *list)                        
{
    List_node *p_node = NULL;

    if(list == NULL || list->count == ZERO){ 
        return FALSE;
    }
   
    //   case1:
    //      | head | tail | count |
    //          \      /      1->0
    //           \    /
    //            node
    
    //   case2:
    //      | head |              tail | count |
    //          \                 /       n-> n - 1
    //           \               /
    //            node1->node2->node3
    p_node = list->head; 
    if(list->count == ONLY){    
        list->head = list->tail = NULL;
        free(p_node);
    }else{
        //判断倒数第二个？
        //   p_node->next == list->tail
        while(p_node->next != list->tail){
            p_node = p_node->next;
        }
        free(list->tail);
        list->tail = p_node;
        p_node->next = NULL;
    }
    list->count--;
    return TRUE;
}


//显示链表信息
void      show_list(List *list)                   
{
    List_node *p_node = NULL;
    if(list == NULL || list->count == ZERO){
        return ;
    }

    p_node = list->head;

    while(p_node){
        printf("%d ",p_node->data);
        p_node = p_node->next;
    }
    printf("\n");

}

//升序排列
void      sort_list_ascend(List *list)            
{
    List_node *p_node = NULL;
    List_node *q_node = NULL;
    if(list == NULL || list->count == ZERO
      || list->count == ONLY){
          return ;
    }

    for(p_node = list->head; p_node; p_node = p_node->next)
       for(q_node = p_node->next; q_node; q_node = q_node->next)
           if(p_node->data > q_node->data)
           {
                swap(p_node,q_node,sizeof(List_node)-sizeof(List_node*));               

           }

}

//降序排列
void      sort_list_descent(List *list)           
{
    List_node *p_node = NULL;
    List_node *q_node = NULL;
    if(list == NULL || list->count == ZERO
      || list->count == ONLY){
          return ;
    }

    for(p_node = list->head; p_node; p_node = p_node->next)
       for(q_node = p_node->next; q_node; q_node = q_node->next)
           if(p_node->data > q_node->data)
           {
                swap(p_node,q_node,sizeof(List_node)-sizeof(List_node*));               

           }


}

//得到链表节点数量
int       get_list_count(List *list)              
{
     if(list == NULL){
        return ERROR;
     }

     return list->count;
}


///

#if 0
//合并两个有序链表  感觉自己写的很复杂
List      *merge_two_lists(List *list1, List *list2)       
{
    List_node *p_node = NULL;
    List_node *q_node = NULL;
    List_node *w_node = NULL;
    List *list3 = init_list();

    if(list1 == NULL && list2 != NULL){
          return  list2;
    }else if(list1 != NULL && list2 == NULL){
          return  list1;
    }else if(list1 == NULL && list2 == NULL){
          return NULL;
    }
    
    p_node = list1->head;
    q_node = list2->head;
    w_node = list3->head;
    while(p_node && q_node){
         
        node = create_node();
        if(p_node->data < q_node->data){
            node->data = p_node->data;
            p_node = p_node->next;
        }else{
            node->data = q_node->data;
            q_node = q_node->next;
        }

        if(w_node == NULL){
            w_node = node;
        }else{
            w_node->next = node;
            w_node = node;
        }

        list3->count++;

    }

    while(p_node){
        node = create_node();
        node->data = p_node->data;
        p_node = p_node->next;
        w_node->next = node;
        w_node = node;
        list3->count++;
    }
    
    while(q_node){
        node = create_node();
        node->data = q_node->data;
        q_node = q_node->next;
        w_node->next = node;
        w_node = node;
        list3->count++;
    }
  
    list3->tail = w_node;
    
    return list3;

}
#endif
//合并两个有序链表  这个就写的很简单
List   *merge_two_lists(List *list1, List *list2)    
{
     List_node *p = list1->head;
     List_node *q = list2->head;
     List *result = init_list();

     while(p&& q){
         if(p->data <= q->data)
         {     
             push_back(result,p->data);
             p =  p->next;
         }else{
             push_back(result,q->data);
             q = q ->next;
         }

    }
    while(q){
        push_back(result,q->data);
        q = q->next;
    }
    while(p){
        push_back(result,p->data);
        p = p->next;
    }

   return result;
      
}

//合并两个有序链表（递归）
List      *merge_two_lists_recure(List *list1, List *list2)
{


}
 //找到链表的倒数第num个节点
List_node *find_revise_node(List *list, int num)          
{
    int i = 0;
    List_node *p_node = NULL;
    List_node *q_node = NULL;
    if(list == NULL || num <= ZERO || list->count < num){
        return NULL;
    }
    p_node = list->head;
    q_node = list->head;
    while(i < num){
       p_node = p_node->next;
    }
    while(p_node){
        p_node = p_node->next;
        q_node = q_node->next;
    }
     
    return q_node;

}
//找到链表的中间节点
List_node *find_mid_node(List *list)                       
{
    List_node *p_node = NULL;
    List_node *q_node = NULL;
    if(list == NULL || list->count == ZERO){
        return NULL;
    }
    p_node = list->head;
    q_node = list->head;

    while(p_node){
        p_node = p_node->next->next;
        q_node = q_node->next;
    }
     
    return q_node;

}
//逆置一个链表
List      *reverse_list(List *list)                        
{
    List_node *p_node = NULL;
    List_node *q_node = NULL;
    List_node *m_node = NULL;

    if(list == NULL || List->count ==ZERO
      || list->count == ONLY){
        return NULL;
    }

    p_node = list->head;
    q_node = list->head;
    m_node = list->tail;
    list->head = list->tail;

    while(p_node != list->head){

        p_node = q_node;
        p_node = p_node->next;
       
        m_node->next = q_node;
        m_node = q_node;
        m_node->next = NULL;

    }
    list->tail = m_node;

    return list;

}
//链表的拷贝
List     *list_dump(List *list)                         
{
    List *copy_list = NULL;
    List_node *p_node = NULL;
    List_node *q_node = NULL;
    List_node *node = NULL;

    if(list == NULL){
        return NULL;
    }
   
    copy_list = init_list();
    memcpy(copy_list,list,sizeof(List));
    p_node = list->head;
    q_node = copy_list->head;
    while(p_node != NULL){
         node = create_node();
         node->data = p_node->data
         if(q_node == NULL){
            copy_list->head = q_node;
         }else{
            q_node->next = node;
            q_node = node;
         }
         copy_list->count++;
         copy_list->tail = q_node;
         p_node = p_node->next;
    }
    
    return copy_list;

}

//逆序输出链表信息
void      reverse_show_list(List *list)                    
{
    List_node *p_node = NULL;
    if(list == NULL || list->count == ZERO){
        return ;
    }
    p_node = list->head;
    if(p_node != NULL){
        reverse_show_list(p_node->next);
    }
     printf("%d ", p_node->data);
   


}

//判断链表是否有交点
Boolean   is_list_intersect(List *list1, List *list2)      
{
    if(lis1 == NULL || list2 == NULL
      || list1->count == ZERO || list2->count == ZERO){
      return FALSE;
    }

    return list1->tail == list2->tail;
     
}

//得到第一个交点
List_node *get_first_common_node(List *list1, List *list2) 
{
    int num = 0;
    List_node *p_node = NULL;
    List_node *q_node = NULL;
    if(lis1 == NULL || list2 == NULL
      || list1->count == ZERO || list2->count == ZERO
      || is_list_intersect(list1,list2) == FALSE){
      return NULL;
    }
    if(list1->count > list2->count){
          p_node = list1->head;
          num = list1->count - list2->count;
          while(num--){
              p_node = p_node->next;
          }
    }else{
          q_node = list2->head;
          num = list2->count - list1->count;
          while(num--){
              q_node = q_node->next;
          }
    }
    
    while(p_node != q_node){
         p_node = p_node->next;
         q_node = q_node->next;
    }

    return q_node;
}

#if 0
//在O（1）的时间复杂度删除节点  自己还是写的复杂
void      delete_one_node(List *list, List_node *node)     
{
    List_node *p_node = NULL;
    List_node *q_node = NULL;
    if(list == NULL || node == NULL || list->count == ZERO){
        return ;
    }
 
    q_node = list->head;
    
    if(list->count == ONLY){
      list->head = list->tail = NULL;
      free(q_node);
      q_node = NULL;
    }else if(p_node != list->tail){
        p_node = node->next;
        node->data = p_node->data;
        node->next = p_node->next;
        free(p_node);
        p_node = NULL;
    }else{
        while(q_node->next->next){
            q_node = q_node->next;
        }
        list->tail = q_node;
        List->tail->next = NULL;
        free(q_node->next);
    }
    

}
#endif
//在O（1）的时间复杂度删除节点  自己还是写的复杂
void      delete_one_node(List *list, List_node *node) 
{
    List_node *p_node = NULL;
    if(list == NULL || node == NULL){
        return ;
    }

    if(node->next != NULL){
        p_node = node->next;
        node ->data = p_node->data;
        node->next = p_node->next;
        free(p_node);
    }else{
        pop_back(list);
    }
}

//判断一个链表是否有环  这里最后还是接受快慢指针相遇的值，因为下一个函数要用
Boolean has_circle(List *list,List_node **instersect)               
{
    List_node *slow = NULL;
    List_node *fast = NULL;

    if(list == NULL || list->count == ZERO 
       || list->count == ONLY){
        return FALSE;
    }

    slow = list->head;
    fast = list->head;

    while(fast != NULL && fast->next != NULL){
        fast = fast->next->next;
        slow = slow->next;

        if(slow == fast){
            *instersect = fast;
            return TRUE; 
        }
    }


}
//找到循环链表的第一个节点
List_node *find_circle_first_node(List *list)  
{
      List_node *instersect = NULL;
      List_node *list1_head = NULL;
      List_node *list2_head = NULL;
      List_node *p_node = NULL;
      List_node *q_node = NULL;
      int list1_len = 1;
      int list2_len = 1;
      int dis = 0;


      if(list == NULL || list->count == ZERO
        || list->count == ONLY || has_circle(list,&instersect)==FALSE){
        return NULL;
      }

      //将问题转化为求两个链表的相交的第一个交点
      p_node = list1_head = list->head;
      q_node = list2_head = instersect->next;

      //计算长度
      while(p_node != instersect){
        list1_len++;
        p_node = p_node->next;
      }
      //计算长度
      while(q_node != instersect){
        list2_len++;
        q_node = q_node->next;
      }

      p_node = list1_head;
      q_node = list2_head;

      
      //用从后向前的差值，开始一起跑链表，遇到相等则为所求
      if(list1_len > list2_len){
        dis = list1_len - list2_len;
        while(dis--){
            p_node = p_node->next;
        }
      }else{
        dis = list2_len - list1_len;
        while(dis--){
            q_node = q_node->next;
        }
      }
      
      while(p_node != q_node){
        p_node = p_node->next;
        q_node = q_node->next;
      }

      return p_node;

}











