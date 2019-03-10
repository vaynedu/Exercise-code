//数组中只出现一次的数字
//一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。 

class Solution {
public:
    void FindNumsAppearOnce(vector<int> data,int* num1,int *num2)
    {
        int myxor = 0;
        int flag = 1;
        int i = 0;
        
        for(i = 0; i < data.size(); ++i){
            myxor ^= data[i];
        }
        
        while((myxor & flag ) == 0){
            flag <<= 1;
        }
        
        *num1 = myxor;
        *num2 = myxor;
        
        for(i = 0; i < data.size(); ++i){
            if((flag & data[i]) == 0){
                *num2 ^= data[i];
            }else{
                *num1 ^= data[i];
            }
        }
             
    }
};