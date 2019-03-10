#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int a[3]={1,2,3};
    do{
        cout<<a[0]<<" "<<a[1]<<" "<<a[2]<<endl;
    }while(next_permutation(a,a+3));

    return 0;
}
//利用STL中的next_permutation全排列函数
//next_permutation函数会取得[first,last)所标示序列的下一个排列组合，
//如果没有下一个排列组合返回false，有则返回true
//简短的AC代码。调用了STL的next_permutation函数

vector<string> Permutation(string str) 
{
        vector<string> answer;
        if(str.empty())
            return answer;       
        sort(str.begin(),str.end());
        do{
            answer.push_back(str);
        }
        while(next_permutation(str.begin(),str.end()));
        return answer;
}

class Solution {
public:
    vector<string> Permutation(string str)
    {
        vector<string> result;
        if(str.empty()) return result;
         
        Permutation(str,result,0);
         
        // 此时得到的result中排列并不是字典顺序，可以单独再排下序
        sort(result.begin(),result.end());
         
        return result;
    }
     
    void Permutation(string str,vector<string> &result,int begin)
    {
        if(begin == str.size()-1) // 递归结束条件：索引已经指向str最后一个元素时
        {
            if(find(result.begin(),result.end(),str) == result.end())
            {
                // 如果result中不存在str，才添加；避免aa和aa重复添加的情况
                result.push_back(str);
            }
        }
        else
        {
            // 第一次循环i与begin相等，相当于第一个位置自身交换，关键在于之后的循环，
            // 之后i != begin，则会交换两个不同位置上的字符，直到begin==str.size()-1，进行输出；
            for(int i=begin;i<str.size();++i)
            {
                swap(str[i],str[begin]);
                Permutation(str,result,begin+1);
                swap(str[i],str[begin]); // 复位，用以恢复之前字符串顺序，达到第一位依次跟其他位交换的目的
            }
        }
    }
     
    void swap(char &fir,char &sec)
    {
        char temp = fir;
        fir = sec;
        sec = temp;
    }
};