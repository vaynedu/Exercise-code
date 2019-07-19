#include <stdio.h>
#include <time.h>


#define SIZE      (10000000)
#define MOD_SIZE  (100)


// 不稳定：当出现跳跃交换而不是相邻交换（选择，快速，shell）
// 比较排序可以被抽象为决策树
// 最坏情况下，都需要做n*logn次比较
// 优化的比较类排序，堆排序和合并排序运行时间上界o(nlogn)


// 1.冒泡排序    o(n^2)       稳定
// 2.选择排序    o(n^2)       不稳定
// 3.插入排序    o(n^2)       稳定 
// 4.shell排序
// 5.归并排序    o(n*logn)    稳定
// 6.快速排序  
// 7 堆排序
// 8.计数排序    o(n)
// 9.基数排序    年龄  9000 10000 8000 9100 o(n*logn)



void init_array(int *array,int length); 
void swap(void *a,void *b,int length);
void show_array(int *array,int length);


void bubble_sort(int *array,int length);   // 1.冒泡排序
void select_sort(int *array,int length);   // 2.选择排序
void improve_select_sort(int *array,int length);// 2.优化选择排序
void insert_sort(int *array,int length);   // 3.插入排序
void shell_sort(int *array,int length);    // 4.希尔排序
void merge_sort(int *array,int length);    // 5.归并排序
void quick_sort(int *array,int length);    // 6.快速排序
void count_sort(int *array,int length);    // 8.计数排序
void base_sort(int *array,int length);     // 9.基数排序


static void Merge_sort(int *array,int left, int  right, int *temp); 
static void merge_array(int *array,int left,int mid,int right,int *temp);


void show_array(int *array,int length)
{   
    int i = 0;

    if(array != NULL && length > 0){
         for(i = 0; i < length; ++i){
            printf("%d  ",array[i]);
         }
    }


}
void swap(void *a,void *b,int length)
{
    void *temp = malloc(sizeof(length));

    memcpy(temp,a,length);
    memcpy(a,b,length);
    memcpy(b,temp,length);

    free(temp);
}


void init_array(int *array,int length)
{
    int i = 0;

    srand(time(NULL));
    if(array != NULL && length > 0){
         for(i = 0; i < length; ++i){
            array[i] = rand() % MOD_SIZE;
         }
    }
}


void bubble_sort(int *array,int length)
{
    int i = 0;
    int j = 0;  
     
    if(array == NULL || length <= 0){
        return ;
    }
  
    for(i = 0; i < length - 1; i++)
        for(j = 0; j < length - i - 1; j++)
        {
            if(array[j + 1] > array[j])
            {
                swap(&array[j + 1],&array[j],sizeof(array[0]));
            }
        }

}

void select_sort(int *array ,int length)
{
    int i = 0;
    int j = 0;

    if(array == NULL || length <= 0){
        return ;
    }

    for(i = 0; i < length - 1; i++)
        for(j = i + 1; j < length; j++)
        {
            if(array[i] > array[j])
            {
                swap(&array[i],&array[j],sizeof(array[0]));

            }
        }


}
void improve_select_sort(int *array,int length)
{
    int i = 0;
    int j = 0;
    int min = 0;

    for(i = 0; i < length - 1; i++)
    {
        for(j = i + 1; j < length; j++) 
        if(array[min] > array[i]){
              min = i;
        }

        swap(&array[min],&array[i],sizeof(array[0]));
    }


}

void insert_sort(int *array,int length)
{
    int i = 0;
    int j = 0;
    int value = 0;
    
    for(i = 1; i < length; i++)
    {
        value = array[i];
        for(j = i-1; j >=0 && array[j] > value;j--){
            array[j+1] = a[j];
        }
        array[j+1] = value;
    }
}

void shell_sort(void *array,int length)
{
     int i = 0;
     int j = 0;
     int gap = 0;
     int temp = 0;

     for(gap = length / 2; gap > 0; gap /= 2){
        for(i = gap; i < length; i++){
            for(j = i - gap; j >= 0 && array[j] > array[j+gap]; j -= gap){
                    temp = array[j];
                    array[j] = array[j+gap];
                    array[j+gap] =temp;
            }
        }

     }

}

void quick_sort(int *array,int length)
{
    int  low = 0;
    int  high = length -1;
    int  key = array[low];
    

   // 3 8 3 6 9 15 2 3 5 

  if(low < high){
      while(low < high)
     {
         while(low < high && key < array[high]){
             high--;
         }
         if(low < high){
             array[low++]= array[high];
         }
         while(low < high && key > array[low]){
             low++;
         }
         if(low < high){
            array[high--] = array[low];
         }

         array[low] = key;
       
         quick_sort(array,low - 1);
         quick_sort(array + low + 1 ,length - low - 1);   
    }

  }

}
void merge_sort(int *array,int length)
{
    int *temp = NULL; 
    if(array == NULL || length < 2){
        return ;
    }

    temp = (int *)malloc(sizeof(int) * length);
    Merge_sort(array,0,length - 1,temp);    

}
static void Merge_sort(int *array,int left, int  right, int *temp)
{
    int mid = 0;
    // 先进行拆分，在进行合并
    if(right > left){  //元素个数不为1，可以继续拆
          mid = left  + ((right - left)>>1);
          Merge_sort(array,left,mid,temp);      //归并左半部分
          Merge_sort(array,mid+1,right,temp);   //归并右半部分

          //合并拆分的两部分（合并两个有序数组）
          merge_array(array,left,mid,right,temp);
    }
}
static void merge_array(int *array,int left,int mid,int right,int *temp)
{
    int i = left;     // 第一个数组的起始位置
    int j = mid + 1;  // 第二个数组的起始位置
    int m = mid;      // 第一个数组的终止位置 
    int n = right     // 第二个数组的终止位置
    int k = 0;

    while(i <= m && j <= n){
       if(array[i] < array[j]){
          temp[k++]  = array[i++];
       }else{
          temp[k++]  = array[j++];
       }


    }

    while(i <= m){
        temp[k++] = array[i++];
    }
    
    while( j <= n){
        temp[k++] = array[j++];
    }

    // 把temp中的内容复制到array相对应的范围
    memcpy(array + left, temp, sizeof(int) * k);

}

void count_sort(int *array,int length)
{
     //1.数据比较集中
     //2.数据范围小
     //3.对内存消耗比较大，用空间换时间


    // 18 19 18 19 19 29 21 20 25 27 29
    int *count = NULL;
    int c_size = max - min + 1;
    int i = 0;
    int j = 0;
    //申请统计个数的数组，并且进行清0操作
    count = (int *)malloc(sizeof(int) * c_size);
    bzero(count,sizeof(int) *c_size);

    //计算每个数字对应的个数
    for(i = 0; i < length; ++i){
        count[array[i] - min]++;
    }

    //从min到max，把个数非0的数字依次进行尾部插入

    for(i = 0; i < c_size;i++){
        while(count[i]--){
            array[j++] = i + min;
        }
    }
   
    free(count);
}

// 9基数排序 ，消耗内存，比如扑克牌
void base_sort(int *array,int length)     
{
     // 120 321 456 326 443 2221 334 901 108 856 735 235
     // 按照个位排序
     // 按照十位排序
     // 按照百位排序

     int **bucket = NULL;
     int i = 0;
     int num = 1; 
     int key = array[0];
     int j = 1;
     int n = 0;
     int mod = 1;
     int x = 0;

     for(i = 0; i < length; i++){
        if(key < array[i]){
            key = array[i];
        }
     }

     while(key){
        key /= 10;
        num++;
     } 
    
     bucket = (int **)malloc(sizeof(int) * 10);

     for(i = 0; i < 10; i++){
          bucket[i] = (int *)malloc(sizeof(int) * (length+1));
          bzero(bucket[i],sizeof((int) * (length+1)));
     }

     
     for(x = 0; x < num ; x++ ){

        for(i = 0; i< length;i++){
             bucket[array[i]/mod%10][j++] = array[i];                            
             bucket[array[i]/mod%10][0]++;
        }
        j = 1;
        for(i = 0; i < 10;i++)
        {
            while(bucket[i][0]--){
               array[n++] = bucket[i][j++];
            }

            j = 1;
        }B
        n = 0;
        mod *= 10;

    }


}


int main(int argc,char *argv[])
{
    clock_t start = 0;
    clock_t end = 0;
    double usr_time = 0.0;

    init_array(array,SIZE);
    
    int *array = (int *)malloc(sizeof(int) * SIZE);

    start = clock();
    
    show_array(array,SIZE);
    bubble_sort(array,SIZE);
    show_array(array,SIZE);

    end = clock();

    usr_time = (double)(end - start)/CLOCKS_PER_SEC;
    


    return 0;
}

