//寻找两个合并数组的中位数
class Solution
{
   public:
       int findk(int *a,int *b,int lena,int lenb,int k){
            int i = 0;
            int j = 0;
            for(;(i < lena)&&( j < lenb);){
                --k;
                if(a[i] < b[j]){
                    if( k == 0){
                        return a[i];
                    }
                    ++i;
                }else if(k == 0){
                    return b[j];
                }else{
                    ++j;
                }
            }

            return (i >= lena)?b[j+k-1]:a[i+k-1];

       }
       double findMedianSortedArrays(int A[],int m,int B[],int n){
           return ((m+n) & 1)?findk(A,B,m,n,(m + n + 1) >> 1):
           ((findk(A,B,m,n,(m + n) >> 1) + findk(A,B,m,n,((m+n) >>1)+1)) *0.5);
       }


};