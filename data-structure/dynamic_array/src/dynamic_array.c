#include "dynamic_array.h"

#define MODE_SIZE 32

static  Boolean array_push_front(Array *array,void *value);
static  Boolean array_push_back(Array *array,void *value);
static  Boolean array_pop_front(Array *array);
static  Boolean array_pop_back(Array *array);


static void *array_iter_head(Iterator *iter,Array *array);
static void *array_iter_tail(Iterator *iter,Array *array);
static void *array_iter_next(Iterator *iter,Array *array);
static void *array_iter_prev(Iterator *iter,Array *array);


static void array_grow(Array *array,int size);
static int adjust_size(int size);




static Boolean array_push_back(Array *array,void *value)
{
    if(array == NULL || value == NULL){
        return FALSE;
    }
    if(array->count >= array->capacity){
        array_grow(array,array->count + MODE_SIZE);
    }

    array->data[array->count] =  value;
    array->count++;

    return TRUE;
}

static Boolean array_push_front(Array *array,void *value)
{
    return array_prev_insert(array,0,value);
}

static Boolean array_pop_front(Array *array)
{
    void *delete = NULL;
    int i = 0;

    if(array == NULL || array->count == ZERO){
        return FALSE;
    }

    array->count--;

    delete = array->data[0];
    if(array->free != NULL){
        array->free(delete);
    }

    for(i = 0; i < array->count; i++){
        array->data[i] = array->data[i+1];
    }
    array->data[i] = NULL;

    return TRUE;
}

static Boolean array_pop_back(Array *array)
{
    void *delete = NULL;
    if(array == NULL){
        return FALSE;
    }
    array->count--;
    delete = array->data[array->count];
    if(array->free != NULL){
        array->free(delete);
    }

    array->data[array->count] = NULL;

    return TRUE;
}


static void *array_iter_head(Iterator *iter,Array *array)
{
    if(iter == NULL || array == NULL){
        return NULL;
    }

    iter->index = 0;
    iter->size = array->count;
    if(array->data == NULL || array->count == ZERO){
        iter->ptr = NULL;
    }else{
        iter->ptr = array->data[0];
    }

    return iter->ptr;
}

static void *array_iter_tail(Iterator *iter,Array *array)
{
    if(iter == NULL || array == NULL){
        return NULL;
    }
    iter->index = array->count -1;
    iter->size = array->count;
    if(array->data == NULL || array->count == ZERO){
        iter->ptr = NULL;
    }else{
        iter->ptr = array->data[iter->index];
    }

    return iter->ptr;
}

static void *array_iter_next(Iterator *iter,Array *array)
{
    iter->index++;
    if(iter->index >= iter->size){
        iter->ptr = NULL;
    }else{
        iter->ptr = array->data[iter->index];
    }

    return iter->ptr;
}


static void *array_iter_prev(Iterator *iter,Array *array)
{
    iter->index--;
    if(iter->index < 0){
        iter->ptr = NULL;
    }else{
        iter->ptr = array->data[iter->index];
    }

    return iter->ptr;
}


static int adjust_size(int size)
{
    size += (MODE_SIZE - 1);
    size /= MODE_SIZE;
    size *= MODE_SIZE;

    return size;
}

static  void array_grow(Array *array,int size)
{
    int adjust = 0;
    if(array->capacity < size){
        adjust = adjust_size(size);
        array->capacity = size;
        if(array->data != NULL){
            array->data = Realloc(array->data,sizeof(void *)*adjust);
        }else{
            array->data = Malloc(sizeof(void *) * adjust);
        }
    }
}


Array *init_array(int init_size)
{
     Array *array = (Array *)Malloc(sizeof(Array));

     array->copy = NULL;
     array->match = NULL;
     array->free  = NULL;

     array->push_front = array_push_front;
     array->push_back  = array_push_back;
     array->pop_front  = array_pop_front;
     array->pop_back   = array_pop_back;


     array->iter_head = array_iter_head;
     array->iter_tail = array_iter_tail;
     array->iter_next = array_iter_next;
     array->iter_prev = array_iter_prev;


     array->count = 0;
     array->data = NULL;
     array->capacity = 0;
     if(init_size > 0){
        array_grow(array,init_size);
     }

     return array;
}

void destroy_array(Array **array)
{
    if(array == NULL || *array == NULL){
        return ;
    }

    array_clean(*array);

    free((*array)->data);

    free(*array);
    *array = NULL;
}


void array_clean(Array *array)
{
    delete_range_value(array,0,array->count-1);
}

Boolean array_prev_insert(Array *array,int index,void *value)
{
    int i = 0;

    if(array == NULL || index < 0 || value == NULL
       || array->data == NULL || index >= array->count){
               return FALSE;
    }

    if(array->count >= array->capacity){
        array_grow(array,array->capacity + MODE_SIZE);
    }

    for(i = array->count; i >= index; --i){
        array->data[i] = array->data[i-1];
    }

    array->data[i] = value;
    array->count++;

    return  TRUE;
}


Boolean array_next_insert(Array *array,int index,void *value)
{
    int i = 0;
    if(array == NULL || index < 0 || value == NULL
      || array->data == NULL || index >= array->count){
        return FALSE;
    } 

    if(array->count >= array ->capacity){
        array_grow(array,array->capacity + MODE_SIZE);
    }

    for(i = array->count; i > index; --i){
        array->data[i] = array->data[i-1];
    }

    array->data[i] = value;
    array->count++;

    return FALSE;
}

int get_array_count(Array *array)
{
    if(array == NULL){
        return ERROR;
    }
    return array->count;
}

Boolean delete_index_value(Array *array,int index)
{
    return delete_range_value(array,index,index);
}

Boolean delete_range_value(Array *array, int begin, int end)
{
    int i = 0;
    int j = 0;

    if(array == NULL || array->count == ZERO
      || begin < 0 || begin > end || end >= array->count){
          return  FALSE;
     }

     for(i = begin; i <= end; i++){
         if(array->free != NULL){
            array->free(array->data[i]);
         }

         array->data[i]= NULL;
     }

     for(i = begin,j=end + 1; j < array->count; i++,j++){
        array->data[i] = array->data[j];
     }

     array->count -= (end - begin + 1);

     return TRUE;
}

int find_value(Array *array,void *value)
{
    int i = 0;
    int count = array->count;

    if(array == NULL || array->count == ZERO
       || value == NULL){
        return ERROR;
    }

    if(array->match != NULL){
        for(i = 0; i < count; i++){
            if(array->match(array->data[i],value)){
                return i;
            }
        }
    }else{
        for(i = 0; i < count; i++){
            if(array->data[i] == value){
                return i;
            }
        }
    }

    return ERROR;
}



























