//输入一个链表，反转链表后，输出链表的所有元素。 
class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
        ListNode *pPrev = NULL;
        ListNode *pNext = NULL;
        ListNode *pNode = pHead;
        ListNode *pReverseNode = NULL;
        
        if(pHead == NULL){
            return NULL;
        }
        
        while(pNode != NULL){
            pNext = pNode->next;
            if(pNext == NULL){
                pReverseNode = pNode;
            }
            pNode->next = pPrev;
            pPrev = pNode;
            pNode = pNext;
        }
        
        return pReverseNode;
    }
};