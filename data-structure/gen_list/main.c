#include <stdio.h>
#include <stdlib.h>
#include "gen_list.h"

int main(int argc, char **argv)
{
    Gen_list list = NULL;
    char str[] = "(15, 'c', (20, 'd', (30, 'f')), ('g', 'i'), 60)";

    list = init_genlist(str);
  
    show_genlist(list);    //显示广义表信息

    destroy_genlist(&list);   //广义表的销毁
    return 0;
}


//(15, 'c', (20, 'd', (30, 'f')), ('g', 'i'), 60)
