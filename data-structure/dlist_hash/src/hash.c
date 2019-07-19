
#include "hash.h"

//hash表的接口
Hash    *init_hash(int b_size, Hash_func h_func)      //hash表的初始化
{
    Hash *hash = (Hash *)ds_malloc(sizeof(Hash));
    hash->bucket_size = b_size;
    hash->element_count = 0;
    hash->hash_free = NULL;
    hash->hash_match = NULL;
    hash->hash_func = h_func;

    //申请桶的个数由b_size决定
    hash->table = (Dlist **)ds_malloc(sizeof(Dlist *) * b_size);
    bzero(hash->table, sizeof(Dlist *) * b_size);
    //关于双端链表的初始化在被使用的时候进行，这样做是为了节省效率

    return hash;
}

void    destroy_hash(Hash **hash)                     //hash表的销毁
{
    int i = 0;
    int bucket_size = 0;
    Hash *p_hash = NULL;

    return_if_fail(hash != NULL  && *hash != NULL);


    //销毁操作：
    //  1.销毁每一个双端链表
    p_hash = *hash;
    bucket_size = p_hash->bucket_size;
    for(i = 0; i < bucket_size; ++i){
        destroy_dlist(&(p_hash->table[i]));
    }
    //   2.销毁hash->table
    free(p_hash->table);
    //   3.销毁hash控制信息
    free(p_hash);
    *hash = NULL;
}

Boolean hash_insert(Hash *hash, const void *value)    //hash表的插入
{
    int b_index = 0;

    if(hash == NULL || value == NULL
    || hash_search(hash, value)){
        //不得对重复元素进行插入，如果该元素已经存在于hash表，则直接退出
        return FALSE;
    }

    //通过hash函数确定value插入的链表
    b_index = hash->hash_func(value) % hash->bucket_size;

    if(hash->table[b_index] == NULL){
        hash->table[b_index] = init_dlist();
    }

    //对value进行插入操作（尾插）
    push_back(hash->table[b_index], (void *)value);
    hash->element_count++;

    return TRUE;
}

Boolean hash_search(Hash *hash, const void *value)    //hash表的查找
{
    int        b_index = 0   ;
    Dlist_node *p_node = NULL;

    return_val_if_fail(hash!=NULL && value!=NULL,FALSE);

    b_index = hash->hash_func(value) % hash->bucket_size;

    //如果该链表不存在，则需要进行初始化
    if(hash->table[b_index] == NULL){
        return FALSE;
    }

    //在该链表中进行查找，从头到尾遍历
    if(hash->hash_match != NULL){
        for(p_node = hash->table[b_index]->head;
        p_node ;
        p_node = p_node->next){
            if(hash->hash_match(p_node->data, value)){
                return TRUE;
            }
        }
    }else{
        for(p_node = hash->table[b_index]->head;
        p_node ;
        p_node = p_node->next){
            if(p_node->data == value){
                return TRUE;
            }
        }
    }

    return FALSE;
}

Boolean hash_remove(Hash *hash, const void *value)    //hash表的删除
{
    int b_index = 0;
    Dlist_node *p_node = NULL;

    if(hash == NULL || value == NULL || hash->element_count == ZERO){
        return FALSE;
    }

    b_index = hash->hash_func(value) % hash->bucket_size;

    if(hash->hash_match != NULL){
        for(p_node = hash->table[b_index]->head;
        p_node ;
        p_node = p_node->next){
            if(hash->hash_match(p_node->data, value)){
                remove_dlist_node(hash->table[b_index], p_node, NULL);
                hash->element_count--;
                return TRUE;
            }
        }
    }else{
        for(p_node = hash->table[b_index]->head;
        p_node ;
        p_node = p_node->next){
            if(p_node->data == value){
                remove_dlist_node(hash->table[b_index], p_node, NULL);
                hash->element_count--;
                return TRUE;
            }
        }
    }

    return TRUE;
}

int     get_element_count(const Hash *hash)           //得到hash表的元素数量
{
    return_val_if_fail(hash != NULL,-1);

    return hash->element_count;
}

void    show_hash_table(const Hash *hash, Print_func print)             //显示hash表的元素信息
{
    int i = 0;
    int bucket_size = 0;

    if(hash == NULL || hash->element_count == ZERO){ 
        return ;
    }

    //从hash表的第一个链表打印到最后一个链表
    bucket_size = hash->bucket_size;
    for(i = 0; i < bucket_size; ++i){
         printf("bucket[%d]:", i);
         show_dlist(hash->table[i], print);
    }
}
