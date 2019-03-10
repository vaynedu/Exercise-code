//调整数组顺序使奇数位于偶数前面
//输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇
//数位于数组的前半部分，所有的偶数位于位于数组的后半部分，并保证奇数和
//奇数，偶数和偶数之间的相对位置不变。


class Solution
{
   public:
        void reOrderArray(vector<int> &array){
            int i = 0;
            int j = 0;
            for(i = 0; i < array.size(); ++i){
                for(j = array.size() - 1; j > i; --j){
                    if(array[j] % 2 == 1 && array[j - 1] % 2 == 0){
                        swap( array[j], array[j-1]);
                    }
                }//end for 2
            }//end for 1
        }
};


class Solution {
public:
    void reOrderArray(vector<int> &array) {
        int i = 0;
        int count = 0;
        int n = array.size();
        vector<int> tempArray(n);
        for(i = 0; i < n; ++i){
            if(array[i] % 2 != 0){
                tempArray[count++] =  array[i];
            }
        }
         for(i = 0; i < n; ++i){
            if(array[i] %2 == 0){
                tempArray[count++] =  array[i];
            }
        }
        for(i = 0; i < n; ++i){
            array[i] = tempArray[i];
        }
               
    }
};