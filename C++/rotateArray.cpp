/*************************************************************
旋转数组的最小数字
题目描述
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素。
例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。
NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。
**************************************************************/

class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        int i = 0;
        int min = 0;
        if(rotateArray.size() == 0){
            return 0;
        }
        min = rotateArray[0];
        for(i = 0; i < rotateArray.size(); ++i){
            if(rotateArray[i] < min){
                min = rotateArray[i];
                break;
            }
        }
        return min;
    }
};

//折半查找--每次折半，时间复杂度logn 
//本来写了个循环只需判断下降沿--Array[i]>Array[i+1]就行了，


class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        int left = 0;
        int right = rotateArray.size() - 1;
        int mid = (left + right)/2;
        
        if(rotateArray.empty()){
             return 0;
        }
        
        while(left < right){
            if(rotateArray[mid] == rotateArray[left]){
                return rotateArray[mid+1];
            }else if(rotateArray[mid] > rotateArray[left]){
                left = mid;
            }else{
                right = mid;
            }
            
            mid = (left + right)/2;
        }
        
        return 0;
        
    }
};
