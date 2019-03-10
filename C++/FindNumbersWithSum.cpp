//和为S的两个数字
//输入一个递增排序的数组和一个数字S，在数组中查找两个数，
//使得他们的和正好是S，如果有多对数字的和等于S，输出两个数的乘积最小的。 

class Solution {
public:
    vector<int> FindNumbersWithSum(vector<int> a,int sum) {
        vector<int>res;
        int i = 0;
        int j = a.size() - 1;
        int n = a.size();
        while(i < j){
            if(a[i] + a[j] == sum){
                res.push_back(a[i]);
                res.push_back(a[j]);
                break;
            }
            while( i < j && a[i] + a[j] > sum){
                  --j;
            }
            while( i < j && a[i] + a[j] < sum){
                ++i;
            }
        }
        return res;
        
    }
};
