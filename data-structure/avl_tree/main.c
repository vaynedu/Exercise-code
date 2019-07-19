#include "tools.h"
#include "avl_tree.h"

#define COUNT (1000)

int main(int argc, char **argv)
{
    Avl_tree root = NULL;
    Avl_node *find = NULL;
    int value = 0;
    int i = 0;

    for(i = 1; i <= COUNT; ++i){
        value = rand() % 10000000;
        root = avltree_insert(root, value);
        preorder_avltree(root);
        printf("\n");
    
        if(i % 3 == 0){ 
            find = find_node(root, value);
            printf("%d\n", find->data);
        }
#if 0 
        if(i % 3 == 0){
            avltree_delete(root, value);
        }
#endif
    }
    printf("height of tree:%d\n", get_tree_height(root));

    preorder_avltree(root);
    printf("\n");
   
    
 
    destroy_avltree(root);
    return 0;
}
