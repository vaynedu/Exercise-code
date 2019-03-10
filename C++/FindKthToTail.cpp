//输入一个链表，输出该链表中倒数第k个结点。 

class Solution {
public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k){
        ListNode *pNode = NULL;
        unsigned int len = 0;
        if(pListHead == NULL || k == 0){
                return NULL;
        }
        pNode = pListHead;
        while(pNode){
            len++;
            pNode = pNode->next;
        }
        if(len < k){
            return NULL;
        }
        len -= k;
        pNode = pListHead;
        while(pNode){
            if(!len--){
                return pNode;
            }
            pNode = pNode->next;
        }
        return NULL;
    }
};