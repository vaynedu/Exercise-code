class Solution
{
    private:
        stack<int> stack1;
        stack<int> stack2;
    public:
        void push(int node){
            stack1.push(node);
        }

        int pop(){
            int temp;
            if(stack2.empty()){
                while(!stack1.emtpy()){
                    temp = stack1.top();
                    stack2.push(temp);
                    stack1.pop();
                }
            }
            temp = stack2.top();
            stack2.pop();
            return temp;
        }

};

//使用栈先进后出来模拟队列先进先出的结构，实现函数：enqueue(入队)，dequeue(出队)，isEmpty(是否为空)的判断。
//使用栈来模拟队列，需要借助两个栈A、B来实现，A栈负责入队，B栈负责出队，空值判断时需要判断两个栈均为空。需要注意的是，
//从A栈向B栈移动元素时要注意只有当B栈为空时，把A栈内所有元素一次性移入B栈，若B栈有元素，那么不可移动，需要等待B栈为空时才可以移动。




stack<int> A;
stack<int> B;


void enqueue(int value[],int len)
{
    int i = 0;
    for(i = 0; i < len; i++){
        A.push(value[i]);
    }
    if(B.emtpy()){
        while(!A.empty()){
            B.push(A.top());
            A.pop();
        }
    }
}


void dequeue()
{
    while(!B.empty()){
        B.pop();
    }
    while(!A.empty()){
        B.push(A.top());
        A.pop();
    }
    while(!B.empty()){
        B.pop();
    }

}

bool isEmpty()
{
    if(A.empty() && B.empty()){
        return true;
    }
    return false;
}





