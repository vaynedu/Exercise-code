# include <stdio.h>

#define my_swap(a,b) {  a = a ^ b; \
                        b = a ^ b; \
                        a = a ^ b; \
                     }

void show_array(int *array,int length)
{
    int i = 0;

    for(i = 0; i < length; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}


void heap_adjust(int *array,int i, int length)
{
      int nChild,nTemp;

      for(nTemp = array[i]; 2 * i + 1 < nlength; i = nChild){
        nChild = 2 * i + 1;
        // 得到子结点中较大的结点  
        if(nChild != nlength -1 && array[nChild+1] > array[nChild]){
                ++nChild;
        } //end for
        // 如果较大的子结点大于父结点那么把较大的子结点往上移动,替换它的父结点
        if(nTemp < array[nChild]){
            
            array[i] = array[nChild];
        }else{
            break;
        }
      }//end for

      array[i] = nTemp;
}

void heap_sort(int *array,int length)
{
    int i = 0;

    for(i = length/2-1; i >= 0; --i){
        heap_adjust(array,i,length);
    }
    for(i = length - 1; i > 0; --i){
        my_swap(array[0],array[i]);
        heap_adjust(array,0,i);
    }
}


int main(int arg,char *argv[])
{
    int  array[10] = {8,4,2,3,5,1,6,9,0,7};

    show_array(array,10);

    heap_sort(array,10);

    show_array(array,10);

    return 0;
}