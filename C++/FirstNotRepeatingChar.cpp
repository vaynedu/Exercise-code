//第一个只出现一次的字符
//在一个字符串(1<=字符串长度<=10000，全部由大小写字母组成)中找到第一个只出现一次的字符,并返回它的位置 
class Solution {
public:
   
       int FirstNotRepeatingChar(string str) 
       {
        int hashTime[256] = {0};
        if ( str.length() == 0){
            return -1;
        }
         
        for(int i =0;i<str.length();++i){
            hashTime[str[i]]++;
        }
         
        for(int i =0;i<str.length();++i){
            if(hashTime[str[i]] == 1){
                return i;
            }
        }
        return -1;
        }
};

