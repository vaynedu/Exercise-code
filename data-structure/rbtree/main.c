#include "tools.h"
#include "rbtree.h"
#include <math.h>
#include <time.h>

int main(int argc, char **argv)
{
    Rbtree root = NULL; 
    Rbtree_node *node = NULL;   

    int value = 0;
    int i = 0;
    int count = 10;
 
    srand(time(NULL));

    for(i = 1; i < count; ++i){
        value = i;
        if((root = rb_insert(value, root))){
            printf("insert value %d success!\n", value);
        }else{
            printf("insert value %d failed!\n", value);
        }
        printf("root value :%d\n", root->data);
        if((node = rb_search(value, root))){
            printf("found %d !\n", value);
        }else{
            printf("not found %d!\n", value);
        }
        preorder_print(root);
        printf("\n");
 #if 0 
        if(i % 3 == 0){
            if((root = rb_delete(value, root))){
                printf("delete %d success!\n", value);
            }else{
                printf("delete %d failed!\n", value);
            }
        }
#endif
    }
    return 0;
}
