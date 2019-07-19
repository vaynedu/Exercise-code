#include <stdio.h>
#include <stdlib.h>
#include "b_tree.h"

#define MAX_SIZE (100)

int main(int argc, char **argv)
{
    int i = 0; 
    //int array[MAX_SIZE] = {12, 23, 34, 45, 56, 67, 78, 89, 90, 100};
    B_tree root1 = create_tree();

    for(i = 0; i < MAX_SIZE; ++i){
        b_tree_insert(&root1, rand() % 200000);
        print_b_tree(root1);
        printf("\n");
    }
  

    return 0;
}
