#include <iostream>
#include "mystring.h"


using namespace std;

int main(int argc, char *argv[])
{
     myString str;

     myString str1 = "I love you";

     cout << "str1 : " << str1 << endl;

     myString str2("you love me too");

     cout << "str2 : " << str2 << endl;

     cout << "str1 + str2 :" << str1 + "  " + str2 << endl;    
 
     myString str3(str2);
    
     cout << "str3 : " << str3 << endl; 

     
     cout << "str1 == str2 : "  << ((str1 == str2) ? "==" : "!=") << endl;

     cout << "str2 == str3 : "  << ((str2 == str3) ? "==" : "!=" )<< endl;


     return 0;
}


