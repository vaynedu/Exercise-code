#ifndef _MYSTRING_H_
#define _MYSTRING_H_

// 不仅要会使用，还要了解清楚其实现原理
// 这是成为高手的必经之路

#include <iostream>
#include <stdlib.h>
#include <string.h>


using std::ostream;


class myString{
    public:
        myString(const char *str = NULL);  // 普通构造函数
        myString(const myString &other);   // 拷贝构造函数
        ~ myString();  // 析构函数
        myString & operator =(const myString &other); // 赋值函数
        myString & operator +(const myString &other); // 字符串连接 + 
        friend ostream & operator<<(ostream &output, const myString &str); // 字符串输出
        bool operator ==(const myString &other); // 判断两个string 字符串是否相等
        int getLength();  // 返回长度

    private:
        char *m_data;  // 私有变量保存字符串
};


myString::myString(const char *str)
{
    if(!str){
        m_data = new char[1];
        *m_data = '\0';
    }else{

        m_data = new char[strlen(str) + 1];

        strcpy(m_data, str);
    }
}


myString::myString(const myString &other)
{
    //拷贝构造函数里面传入常引用，这样可以不用新增一个栈变量和参数内容不会被修改
    if(!other.m_data){
        m_data = NULL;
    }else{
        m_data = new char[strlen(other.m_data) + 1];
        strcpy(m_data, other.m_data);
    }
}

myString::~myString()
{
    if(m_data){
        delete[] m_data;
        m_data = NULL;
    }
}


myString & myString::operator =(const myString &other)
{
    if(this != &other){ // 检查是否是自赋值
        delete[] m_data;
        m_data = NULL;
        if(!other.m_data){
             int length = strlen(other.m_data);
             m_data = new char[length + 1];
             strcpy(m_data, other.m_data);                     
        }
    }
   
    return *this;
}

myString & myString::operator +(const myString &other)
{
    if(!other.m_data){
        return *this;
    }

    // 如果判断other为空，为空直接返回this指针
    // 如果other不为空
    //    1. 计算两个字符串的长度
    //    2. 申请空间
    //    3. 拷贝两个字符串
    //    4. 赋值给m_data
    //    5. return

    int length = strlen(other.m_data) + strlen(m_data);
    char *tmp_m_data = new char[length + 1];
    strcpy(tmp_m_data, m_data);
    strcat(tmp_m_data, other.m_data);

    delete[] m_data;
    m_data = NULL;

    m_data = tmp_m_data;
    tmp_m_data = NULL;

    return *this;
}



bool myString::operator ==(const myString &other)
{
   if(strlen(m_data) != strlen(other.m_data)){
     return false;
   }else{
     return strcmp(m_data, other.m_data) ? false:true;
   }
} 

ostream & operator<<(ostream &output, const myString &str)
{
   output << str.m_data << std::endl;
  
   return output;
}




#endif  /* _MYSTRING_H_ */
