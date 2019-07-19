//广义表接口

//
//char *str = "";
//char *str1 = "()";
//
//char *str2 = "(((((())"    括号匹配问题
//
//   int flag = 0
//
//   (    flag++;
//   )    flag--;
//
//   if flag < 0:
//        bu pi pei
//
//   flag == 0 
//      pi pei
//
//(15,     'c', (20, 'd', (30, 'f', i)),('g', 'i'), 60)
//

#include "gen_list.h"
#include "tools.h"
#include <ctype.h>
#include <strings.h>
#include <stdio.h>

static Boolean is_input_empty(const char *string);
static Boolean is_braket_match1(const char *string);    //括号匹配
static Boolean is_braket_match(const char *string);    //括号匹配
static Gen_list create_genlist(char *string);

//创建广义表节点
static Gen_node *create_node(void);
static Gen_node *create_head_node(int head_flag);
static Gen_node *create_int_node(int int_value);
static Gen_node *create_char_node(char character);
static Gen_node *create_list_node(Gen_node *p_list);
//删除空格
static char *delete_blank(char *string);
//去掉最外层括号
static void delete_braket(const char *src_str, 
                          char *des_str, 
                          int src_len);
static void get_item(char *sub_str, char *item_str);
static void show_genlist_value(Gen_list gen_list);            //显示广义表信息

static void get_item(char *sub_str, char *item_str)
{
    //15,'c',(20,'d',(30,'f','i')),(12,32),60
    //
    // ((), 'a', 12)
    // (12, 'd', 34), 'a', 12
    // 
    // 12
    int i = 0;
    int flag = 0;
    int sub_len = strlen(sub_str);
 
    while(i < sub_len){
        if(sub_str[i] == '('){
            flag++;    
        }
        if(sub_str[i] == ')'){
            flag--;
        }
        //当前没有在子表里，逗号可以进行元素分割
        if(flag == 0 && sub_str[i] == ','){
            break ;
        }
        i++;     
    }   

    //获取广义表元素
    if(i == sub_len){    //只有一个元素
        strcpy(item_str, sub_str);
        sub_str[0] = '\0';
    }else{    //把当前的元素复制给item_str,并且在原列表删除复制的元素
        strncpy(item_str, sub_str, i);
        item_str[i] = '\0';
        strcpy(sub_str, sub_str + i + 1);
    }
}

static void delete_braket(const char *src_str,
                          char *des_str, 
                          int src_len)
{
   // (asdfasd)
   // asdfasd\0
    strncpy(des_str, src_str + 1, src_len - 2);
    des_str[src_len - 2] = '\0'; 
}
 
static char *delete_blank(char *string)
{
    // adsfad a     dsd\0 
    // adsfadadsd\0 
    int i = 0; 
    int j = 0;

    if(string == NULL){ 
        return string;
    }
    while(string[j] = string[i]){
        if(isblank(string[i])){
            i++;
            continue ;
        }
        i++;
        j++;      
    }
    return string;
}

static Gen_node *create_head_node(int head_flag)
{
    Gen_node *node = create_node();
    node->n_type = HEAD;
    node->value.head_flag = head_flag;
    
    return node;
}

static Gen_node *create_int_node(int int_value)
{
    Gen_node *node = create_node();
    node->n_type = INT;
    node->value.int_value = int_value;
    
    return node;
}
static Gen_node *create_char_node(char character)
{
    Gen_node *node = create_node();
    node->n_type = CHARACTER;
    node->value.char_value = character;
    
    return node;
}

static Gen_node *create_list_node(Gen_node *p_list)
{
    Gen_node *node = create_node();
    node->n_type = LIST;
    node->value.head = p_list;
    
    return node;
}


static Gen_node *create_node(void)
{
    Gen_node *result = (Gen_node *)Malloc(sizeof(Gen_node));
  bzero(result, sizeof(Gen_node));

    return result;
}

static Gen_list create_genlist(char *string)
{
    char *sub_str = NULL;
    char *item_str = NULL;
    int str_len = strlen(string);
    Gen_node *p_node = NULL;

    //判断子表是否为空
    if(is_input_empty(string) == TRUE){
        fprintf(stderr, "input illegal!\n");   
        return NULL;
    }
    //(15, 'c', (20, 'd', (30, 'f', 'i')),(12, 32), 60)
    //15, 'c', (20, 'd', (30, 'f', 'i')),(12, 32), 60
    // 
    //  ((12, 'c', 'd'))
    //
    Gen_list start = create_head_node(1);   //广义表的头结点
    p_node = start;
   
    sub_str = (char *)Malloc(sizeof(char) * str_len);
    item_str = (char *)Malloc(sizeof(char) * str_len);    

    //1.首先去掉最外层括号
    delete_braket(string, sub_str, str_len);
    // printf("%s\n", sub_str);
    while(strlen(sub_str)){
        //2.通过逗号分隔广义表元素
        get_item(sub_str, item_str);
        if(item_str[0] != '(' && item_str[0] != '\''){     //整型类型
            p_node->next = create_int_node(atoi(item_str));
        }else if(item_str[0] != '(' && item_str[0] == '\''){     //子符类型
            p_node->next = create_char_node(item_str[1]); 
        }else{    //子表类型
            p_node->next = create_list_node(create_genlist(item_str));
        }
        p_node = p_node->next;
    }
    //3.根据元素类型构造节点（如果遇到子表要递归调用）
    
    // strncpy

    free(sub_str);   
    free(item_str);

    return start;   
}


static Boolean is_input_empty(const char *string)
{
     //  "()"
     return strlen(string) == ZERO || strcmp(string, "()") == 0;
}
static Boolean is_braket_match(const char *string)    //括号匹配
{
    int flag = MATCH;
    int i = 1;

    if(string[0] != '('){
        return NOT_MATCH;
    }

    flag++;    //说明第一个是左括号成立
    while(string[i] != '\0'){
        if(string[i] == '('){
            flag++;
        }else if(string[i] == ')'){
            flag--;
        }
        if(flag == MATCH && string[i+1] != '\0'){
            return NOT_MATCH;
        }
        i++;
    }
    return flag == MATCH ? MATCH : NOT_MATCH;
   
}

static Boolean is_braket_match1(const char *string)
{
    int flag = MATCH;
    int length = strlen(string);
    int i = 1;
     
    if(string[0] != '(' || string[length - 1] != ')'){
        return NOT_MATCH;
    }

    while(i < length - 1){
        if(string[i] == '('){
            flag++;
        }else if(string[i] == ')'){
            flag--;
        }
        if(flag < MATCH){
            return NOT_MATCH;
        }
        i++;
    }
    return flag == MATCH ? MATCH : NOT_MATCH;
}

Gen_list init_genlist(char *input_str)          //广义表的创建   
{
    //判断输入字符串是否符合条件
    if(input_str == NULL || is_input_empty(input_str) == TRUE 
    || is_braket_match(input_str) == NOT_MATCH){
        return NULL;
    }
   
    delete_blank(input_str);
    //使用字符串构建广义表，遇到子表结构递归调用
    return create_genlist(input_str);  
}


void     destroy_genlist(Gen_list *gen_list)    //广义表的销毁
{
    Gen_node *p_node = NULL;

    if(gen_list == NULL || *gen_list == NULL){ 
        return ;
    }
 
    p_node = *gen_list;
    while(p_node != NULL){
        *gen_list = p_node->next;
        if(p_node->n_type == LIST){
            //如果是子表，则递归调用销毁函数
            destroy_genlist(&(p_node->value.head));
        }
        free(p_node);
        p_node = *gen_list;
    }  
}

int      get_genlist_count(Gen_list gen_list)    //得到广义表的元素个数
{

    return 1;
}

int      get_genlist_depth(Gen_list gen_list)    //得到广义表的深度
{
    int max = 0;
    Gen_node *p_node = NULL;

    if(gen_list == NULL || gen_list->next == NULL){
          return max;
    }

    p_node = gen_list->next;

    while(p_node != NULL){
        if(p_node->n_type == LIST){
            child_depth = get_genlist_depth(p_node->value.head);
            if(max < child_depth){
                max = child_depth;
            }
        }

        p_node = p_node->next;
    }


    return max+1;

}

Gen_list copy_genlist(Gen_list gen_list)         //广义表的拷贝
{
    Gen_list result = NULL;
    Gen_node *p_node = NULL;
    Gen_node *q_node = NULL;


    if(gen_list == NULL || gen_list->next == NULL){
           return NULL;
    }

    result = create_head_node(1);
    p_node = gen_list->next;
    q_node = result;

    while(p_node != NULL){
        if(p_node->n_type == INT){
            q_node->next = create_int_node(p_node->value.int_value);
        }else if(p_node->n_type == CHARACTER){
            q_node->next = create_char_node(p_node->value.char_value);
        }else{
            q_node->next = create_list_node(copy_genlist(p_node->value.head));
        }

        p_node = p_node->next;
        q_node = q_node->next;
    }
    
    return NULL;
}

static void show_genlist_value(Gen_list gen_list)            //显示广义表信息
{
    Gen_node *p_node = NULL;

    if(gen_list == NULL){
        return ;
    }
    printf("(");
    p_node = gen_list->next;
    while(p_node != NULL){
        if(p_node->n_type == INT){ 
            printf("%d", p_node->value.int_value);
        }else if(p_node->n_type == CHARACTER){ 
            printf("'%c'", p_node->value.char_value);
        }else{
            show_genlist_value(p_node->value.head);
        }
        if(p_node->next != NULL){ 
            printf(", ");
        }
        p_node = p_node->next;
    }
    printf(")");
}


void show_genlist(Gen_list gen_list)            //显示广义表信息
{
    show_genlist_value(gen_list);
    printf("\n");
}
