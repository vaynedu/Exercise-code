#include <stdio.h>
#include <uuid/uuid.h>


// gcc myuuid.c -luuid


/*typedef unsigned char uuid_t[16]*/

/* 具体实现可以看uuid.h, 意思都比较简单*/

// void uuid_generate(uuid_t out); 该函数封装了uuid_generate_random和uuid_generate_time
//
// void uuid_generate_random(uuid_t out);
// void uuid_generate_time(uuid_t out);
//
//
//uuid_generate_time 和 uuid_generate_time_safe区别是否有返回，因为某种情况下也有可能返回-1
// int uuid_generate_time_safe(uuid_t out);




int main()
{
   uuid_t uu;
   char str[36];

   uuid_generate(uu);
   uuid_unparse(uu, str);
 
   printf("uuid: %s\n", str);
   

   return 0;
}
