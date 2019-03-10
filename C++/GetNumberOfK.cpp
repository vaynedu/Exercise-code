//数字在排序数组中出现的次数
class Solution {
public:
    int count(vector<int>&data,int mid,int k)
    {
        int i = mid;
        int j = mid;
        int num = 0;
        while(data[++i] == k){
            num++;
        }
        while(data[j--] == k){
            num++;
        }
        return num;
    }
    
    int GetNumberOfK(vector<int> data ,int k) {
        int i = 0;
        int j = data.size()-1;
        int mid = 0;
        
        if(data.size() == 0){
            return 0;
        }
        while(i <= j){
            mid = (i + j)/2;
            if(data[mid] == k){
                return count(data,mid,k);
                break;
            }else if(data[mid] > k){
                i = mid + 1;
            }else{
                j = mid - 1;
            }
        }
        
        return 0;
    }
};