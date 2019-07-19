#ifndef _HASH_H_
#define _HASH_H_

#include "dlist.h"
#include "ds_tools.h"


typedef int (*Hash_func)(const void *key);

//hash表的控制信息
typedef struct Hash{
    int   bucket_size;    //1.需要桶（链表）的数量
    int element_count;    //2.hash表内元素的数量
    Dlist     **table;    //3.hash表的实际存储区域
    
    //free、match、hash_func(散列元素的具体操作)
    void (*hash_free)(const void *ptr);      
    Boolean (*hash_match)(const void *value1, 
                          const void *value2);
    int (*hash_func)(const void *key);
}Hash;

//暴雪hash算法
//生成随机数表进行hash

//hash表的接口
Hash    *init_hash(int b_size, Hash_func h_func)  ;    //hash表的初始化
void    destroy_hash(Hash **hash)                 ;    //hash表的销毁
Boolean hash_insert(Hash *hash, const void *value);    //hash表的插入
Boolean hash_search(Hash *hash, const void *value);    //hash表的查找
Boolean hash_remove(Hash *hash, const void *value);    //hash表的删除
int     get_element_count(const Hash *hash)       ;    //得到hash表的元素数量
void    show_hash_table(const Hash *hash,
                        Print_func print)         ;    //显示hash表的元素信息



#endif
