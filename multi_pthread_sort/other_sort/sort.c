#include <stdio.h>
#include <time.h>
#include "tools.h"

// 1000 * 1000 * 1000 = 1000000000

#define SIZE     (100000000)
#define MOD_SIZE (100)

//不稳定：当出现跳跃交换而不是相邻交换现象（选择排序 快速排序 shell排序）

//1.冒泡排序   时间复杂度O(n^2)   稳定
//2.插入排序   时间复杂度O(n^2)   稳定
//3.选择排序   时间复杂度O(n^2)   不稳定
//4.shell排序
//5.归并排序   时间复杂度O(n * logn)  稳定
//6.快速排序   
//7.堆排序
//8.计数排序   时间复杂度O(n)     
//9.基数排序

//      9000 10000 8000 9100    O(n*logn)
//


void bubble_sort(int *array, int length);    //冒泡排序
void init_array(int *array, int length);
void show_array(int *array, int length);
void insert_sort1(int *array, int length);    //插入排序1
void insert_sort2(int *array, int length);    //插入排序2
void insert_sort3(int *array, int length);    //插入排序3
void select_sort(int *array, int length);    //选择排序
void merge_sort(int *array, int length);    //归并排序（分治思想）
static void Merge_sort(int *array, int left, int right, int *temp);
static void merge_array(int *array, int left, 
                int mid, int right, int *temp);
void count_sort(int *array, int length, int min, int max);    //计数排序

void count_sort(int *array, int length, int min, int max)
{
   //1.数据比较集中；
   //2.数据范围小；
   //
   //3.对内存的消耗比较大，用空间换取时间
   
   //   18 19 18 19 19 29 21 20 25 27 29 
   int *count = NULL;
   int c_size = max - min + 1;
   int i = 0;
   int j = 0;

   //申请统计个数的数组,并且进行清0操作
   count = (int *)malloc(sizeof(int) * c_size);
   bzero(count, sizeof(int) * c_size);
   
   //计算每个数字对应的个数
   for(i = 0; i < length; ++i){
       count[array[i] - min]++;
   }


     for(i = 0, j = 0; i < c_size; ++i){
         while(count[i]--){
             array[j++] = i + min;
         }
     }
   

   //从min到max，把个数非0的数字依次进行尾部插入
   //for(i = 0, j = 0; i < c_size;){
   //    if(count[i--] != 0){
   //        array[j++] = i + min;
   //    }else{
   //        i++;
   //    }
   //}
   free(count);
}


static void merge_array(int *array, int left, 
                int mid, int right, int *temp)
{
    int i = left;   //第一个数组的起始位置
    int j = mid + 1;    //第二个数组的起始位置
    int m = mid;    //第一个数组的终止位置
    int n = right;    //第二个数组的终止位置
    int k = 0;

    while(i <= m && j <= n){   //当两个数组都有元素时，对应位置进行比较
        if(array[i] < array[j]){
            temp[k++] = array[i++];
        }else{
            temp[k++] = array[j++];
        }
    } 

    while(i <= m){
        temp[k++] = array[i++];
    }

    while(j <= n){
        temp[k++] = array[j++];
    }

    //把temp的内容复制到array相对应的范围
    memcpy(array + left, temp, sizeof(int) * k);
}


//O(n * logn)  < O(n^2)
//
//   y = logn
//
//   y = n
//
//
//
//
//
static void Merge_sort(int *array, int left, int right, int *temp)
{
    int mid = 0;
    //1.先进行拆分，再进行合并
    if(right > left){    //元素个数不为1，可以继续拆分
     //  14 3  3  2  45  32  18  27     logn   log2 8 = 3
     //   0                       7
     // 
     //  3  14 2  3
     //
     //  2  3  3  14
     //
     //    9 + 13 = 11
     //    4 + 6 = 10
     //   mid = (right >> 1) +  (left >> 1);
        mid = left + ((right - left) >> 1);
        Merge_sort(array, left, mid, temp);    //归并左半部分
        Merge_sort(array, mid + 1, right, temp);   //归并右半部分
        //合并拆解的两部分(合并两个有序数组)
        merge_array(array, left, mid, right, temp);
    }
}


void merge_sort(int *array, int length)    //归并排序（分治思想）
{
     int *temp = NULL;

     if(array == NULL || length < 2){
         return ;
     }

     temp = (int *)Malloc(sizeof(int) * length);
     Merge_sort(array, 0, length - 1, temp);    
     free(temp);

     //  14 3  57  2  45  32  18  27     logn   log2 8 = 3
     //  拆分过程：
     //
     //  14 3  57  2         45  32  18  27
     //
     //
     //  14 3    57  2        45  32      18  27
     //
     //  14   3    57    2    45   32   18   27
     //
     //  无法拆分，开始合并
     //
     //  ------合并两个有序数组
     //
     //  3   14    2    57    32   45   18   27
     //
     //  2   3    14    57    18   27   32   45
     //
     //  2   3    14    18    27   32   45   57
     //
     //  O(n*logn)
}


void select_sort(int *array, int length)    //选择排序
{
     // 5 13 6 9 2
     //   i                
     //
     // min = i
     //
     // if(array[j]  < array[min]){
     //     min = j;
     // }
     //
     //  swap(array[min], array[i])
     //
     // min = i
     //
     // 5   13    6    9   2
     // i   j = i+1
     //
     // 0   0  13  13  2  9  
     //     i      
     //
     int min_index = 0;
     int i = 0;
     int j = 0;
     int temp = 0;

     for(i = 0; i < length - 1; ++i){
         min_index = i;   //设当前序列的第一个元素为最小值
         for(j = i + 1; j < length; ++j){ 
             if(array[j] < array[min_index]){
                 min_index = j;
             }
         }  
         if(min_index != i){       
            temp = array[i];
            array[i] = array[min_index];
            array[min_index] = temp;
         }
     }
}

 
void insert_sort3(int *array, int length)
{
    int i = 0;
    int j = 0;
    int temp = 0;

    // j     i
    //

    for(i = 1; i < length; ++i){
        for(j = i - 1; j >= 0 && array[j] > array[j + 1]; --j){
           //array[j] = array[j] + array[j + 1];
           //array[j + 1] = array[j] - array[j + 1];
           //array[j] = array[j] - array[j + 1];
            temp = array[j]; 
            array[j] = array[j + 1]; 
            array[j + 1] = temp;
           // //swap(&array[j], &array[j + 1], sizeof(array[0]));
        }
    }
}

void insert_sort2(int *array, int length)
{

    // key = 2
    // 2 3 6
    // j   i
    //
    int i = 0;
    int j = 0;  
    int key = 0;

    for(i = 1; i < length; ++i){
         key = array[i];
         for(j = i - 1; j >= 0 && array[j] > key; --j){
             array[j + 1] =  array[j];
         }
         array[j + 1] = key;
    }
}


void show_array(int *array, int length)
{
    int i = 0;   
    
    if(array != NULL && length > 0){
        for(i = 0; i < length; ++i){
            printf("%d ", array[i]);
        }
        printf("\n");
    }
   
}

void init_array(int *array, int length)
{
    int i = 0;   //
    
    srand(time(NULL));
    if(array != NULL && length > 0){
        for(i = 0; i < length; ++i){
            array[i] = rand() % MOD_SIZE;
        }
    }
}


//冒泡排序
void bubble_sort(int *array, int length)
{
    // 12 3  5   1  40  35 64 17
    //
    // 3  12 5   1  40  35 64 17
    // 
    // 3  5  12  1  40  35 64 17
    //
    // 3  5  1  12  40  35 64 17
    // 
    // 3  5  1  12  35  40 64 17
    //
    // 3  5  1  12  35  40 17 64 
    int i = 0;
    int j = 0;

    // 统计出待排序数量：length - i

    for(i = 0; i < length - 1; ++i){    
        for(j = 1; j < length - i; ++j){
            if(array[j - 1] > array[j]){
                swap(&array[j - 1], &array[j], sizeof(int)); 
            }
        } 
    } 
}



void insert_sort1(int *array, int length)
{
    int i = 0;
    int j = 0;

    // 12  3   5   1  40
    // i   j
    //
    // 3   12  5   1  40
    // i           j
    //
    // 1   12  5   3  40
    // i               j
    //
    // 1   12  5   3  2
    //     i   j
    //
    //
    for(i = 0; i < length - 1; ++i){
        for(j = i + 1; j < length; ++j){ 
            if(array[i] > array[j]){ 
                //swap(&array[i], &array[j], sizeof(int));
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}


int main(int argc, char **argv)
{
    clock_t start = 0; 
    clock_t end = 0;
    double use_time = 0.0;    
    int *array2 = NULL;

    int *array = (int *)Malloc(sizeof(int) * SIZE);
    array2 = (int *)Malloc(sizeof(int) * SIZE); 
   
    init_array(array, SIZE);   //待排序数组的初始化   
    memcpy(array2, array, sizeof(int) * SIZE);   


    printf("address:%p\n", array);
 
    //排序过程
    start = clock();
    //show_array(array, SIZE);    //显示数组元素
    //bubble_sort(array, SIZE);   //排序
    //insert_sort2(array, SIZE);    
    count_sort(array, SIZE, 0, MOD_SIZE - 1);
    //show_array(array, SIZE);    //显示数组元素
    //结束排序
    end = clock();
    use_time = (double)(end - start) / CLOCKS_PER_SEC;  
    printf("sort use time:%lf\n", use_time);

    start = clock();
    //show_array(array2, SIZE);    //显示数组元素
    //bubble_sort(array, SIZE);   //排序
    //insert_sort3(array2, SIZE);    
    //select_sort(array2, SIZE);
    merge_sort(array2, SIZE);
    //show_array(array2, SIZE);    //显示数组元素
    //结束排序
    end = clock();
    use_time = (double)(end - start) / CLOCKS_PER_SEC;  
    printf("sort use time:%lf\n", use_time);



    free(array);
    free(array2);
    return 0;
}
