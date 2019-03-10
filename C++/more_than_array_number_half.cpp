//数组中出现次数超过一半的数字
/**********************************************************************
数组中有一个数字出现的次数超过数组长度的一半，
请找出这个数字。例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。
由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。如果不存在则输出0。 
***********************************************************************/
class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) 
    {
        if(numbers.size() == 0){
            return  0;
        }
        if(numbers.size() == 1){
            return  numbers[0];
        }
        int i = 0;
        int k =  numbers[0];
        int count = 1;
        
        for(i = 1; i < numbers.size(); ++i){
            if(numbers[i] == k){
                count++;
            }else{
                count--;
                if(count == 0){
                    count = 1;
                    k = numbers[i];
                }
            }
        }
        
        if(count > 1 || (count == 1 && k != numbers[i-1])){
            return k;
        }else{
            return 0;
        }
    }
};