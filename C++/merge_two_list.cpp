//合并两个排序的链表
//输入两个单调递增的链表，输出两个链表合成后的链表，当然我们需要合成后的链表满足单调不减规则。 

ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
    ListNode *p_node = NULL;
    ListNode *q_node = NULL;
    ListNode *mergeHead = NULL;
    ListNode *mergeTail = NULL;
    
    if(pHead1 == NULL && pHead2 == NULL){
        return NULL;
    }else if(pHead1 == NULL){
        return pHead2;
    }else if(pHead2 == NULL ){
        return pHead1;
    }
    
    //看是否有头结点
    p_node = pHead1->next;
    q_node = pHead2->next;

    
    if(p_node->val < q_node->val){
        mergeHead = mergeTail = p_node;
          p_node = p_node -> next;    
    }else{
        mergeHead = mergeTail = q_node;
        q_node = q_node -> next;
    }  
    
    while(p_node && q_node){
        if(p_node->val < q_node->val){
            mergeTail->next = p_node;
            mergeTail = p_node;
            p_node = p_node -> next;               
        }else{
            mergeTail->next = q_node;
            mergeTail = q_node;
            q_node = q_node -> next;
        }

    }
    if(p_node){
        while(p_node){
             mergeTail->next = p_node;
             mergeTail = p_node;
             p_node  = p_node ->next;
        }
        
    }
    if(q_node){
        while(q_node){
            mergeTail->next = q_node;
            mergeTail = q_node; 
            q_node  = q_node ->next;
        }
    }
    mergeTail->next = NULL;
    return mergeHead;        
 }

 //创建节点合并
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