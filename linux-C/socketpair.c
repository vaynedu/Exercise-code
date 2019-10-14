/*******************************************************************
*    > F-Name :  socketpair.c
*    > Author :  vaynedu
*    > E-mail :  1219345363@qq.com
*    > C-time :  Mon 14 Oct 2019 11:08:16 AM CST
*******************************************************************/
#include <sys/types.h>
#include <sys/socket.h>

#include <stdlib.h>
#include <stdio.h>


// gcc -o channel channel.c 

int main ()
{
    int   fd[2];
    pid_t pid; 

    int r = socketpair( AF_UNIX, SOCK_STREAM, 0, fd );
    if ( r < 0 ) {
        perror( "socketpair()" );
        exit( 1 );
    }  

    pid = fork();

   
    /* print 
     *
     * parent Sending data: 10001
     * son Data received: 10001
     * son send received: 10002
     * parent Data received: 10002
     */
 
    if ( pid  > 0) {
        /* parent */
        int val = 10000;
        close(fd[1]);
        while (1) {
            sleep(1);
            ++val;
            printf("parent Sending data: %d\n", val);
            write(fd[0], &val, sizeof(val));
            read(fd[0], &val, sizeof(val));
            printf("parent Data received: %d\n", val);
        }
    }else if (pid == 0){
        /* child */
        int child_val = 0;
        close(fd[0]);
        while (1) {
            read(fd[1], &child_val, sizeof(child_val));
            printf("son Data received: %d\n", child_val);
            ++child_val;
            write(fd[1], &child_val, sizeof(child_val));
            printf("son send received: %d\n", child_val);
        }
    }else{
        perror("fork failed\n");
    }


}

