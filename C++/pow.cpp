//数值的整数次方
//给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。 

class Solution {
public:
    double Power(double base, int exponent) {
    
        double r = 1.0;
        int n = abs(exponent);
        
        if(base == 0 && exponent == 0){
            return -1;
        }
        if(base == 0){
            return 0;
        }
        if(exponent == 0){
            return 1;
        }
        
        while(n != 0){
            if( n & 1){
                r *= base;
            }
            base *= base;
            n >>= 1;
        }
        
        return exponent < 0?1/r:r;
       
    }
};
