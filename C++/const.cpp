/*==========================================================
     > File Name: const.cpp
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Sun 17 Jul 2016 02:19:56 PM CST

===========================================================*/

#include <iostream>

using namespace std;


class TestClass
{
   private:
       char *pContent;
       size_t contentLength;
       bool lengthIsValid;
       size_t  precontentLength;

   public:
       size_t length() const;
       const  char*  getPcontent();
       void setLengthValid(bool islengthValid);
};
size_t TestClass::length()const
{
    if(!lengthIsValid){
    //  contentLength = strlen(pContent);
      //lengthIsValid = true;
    }

    return contentLength;
}

const char* TestClass::getPcontent()
{
    return pContent;
}

void TestClass::setLengthValid(bool islengthValid)
{
    lengthIsValid = islengthValid;
}


int main(int argc,char *argv[])
{
    TestClass *tc = new TestClass();
    tc->setLengthValid(false);
    tc->length();
    const char *content = tc->getPcontent();
    return 0;
}
