#ifndef __HEAD_APUE__
#define __HEAD_APUE__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <dirent.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <setjmp.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sched.h>
#include <sys/utsname.h>

#define SLPTM         5000
#define BUFFLEN       1024
#define MSGQUESIZE    512000
#define THGUARDSIZE   (1024*1024)
#define MSGSIZE       BUFFLEN
#define NSEMS         1      //the number of the semaphore

#define GUARDMIN      1024
#define GUARDMAX      (GUARDMIN*10)
#define STACKMIN      (1024*1024)
#define STACKMAX      (STACKMIN*100)

#define ON            1
#define OFF           0
#define OK            0
#define NG            -1

#define TCPPORT       8888
#define UDPPORT       6666

#define SEMLOCK      -1
#define SEMUNLOCK     1

#define Srsclock      0      //the first semaphore of the semaphore-set

#define MSGTYPE       2015

#define IMOK          "I'm OK."

#define SHMKEY00      0xffffa000
#define MSGKEY00      0xffffb000
#define SEMKEY00      0xffffc000

#define logo(...) {                       \
  printf("[%s:%04d] ",__FILE__,__LINE__); \
  printf(__VA_ARGS__);                    \
}
#define logerr(...) {                                          \
  printf("[%s:%04d] [%s] ",__FILE__,__LINE__,strerror(errno)); \
  printf(__VA_ARGS__);                                         \
  printf("\n");                                                \
}

 #define PLAY(TIM) {   \
 while(1)              \
     usleep(TIM);      \
 }


#define sem_lock(id,sem,wait) sem_op(id,sem,SEMLOCK,wait)
#define sem_unlock(id,sem)    sem_op(id,sem,SEMUNLOCK,0)

typedef struct {
    int    shmid         ;
    int    seque         ;
    char   cache[BUFFLEN];
}_shmctl;

typedef struct {
    long mtype;
    char msgtext[BUFFLEN];
}_msgctl;

typedef union {
    int              val  ;  /* Value for SETVAL */
    struct semid_ds *buf  ;  /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                (Linux-specific) */
}_semun;


typedef struct sembuf _sembuf;

#define SYSTEM 0

#if SYSTEM

typedef unsigned short int sa_family_t  ;
typedef unsigned int       uint32_t     ;
typedef unsigned short int uint16_t     ;
typedef uint32_t           in_addr_t    ;

struct in_addr
{
  in_addr_t s_addr;
};

struct sockaddr {
    sa_family_t sa_family;
    char        sa_data[14];
};

#define __SOCKADDR_COMMON(sa_prefix) \
  sa_family_t sa_prefix##family

struct sockaddr_in
{
  __SOCKADDR_COMMON (sin_);
  in_port_t sin_port;                 /* Port number.  */
  struct in_addr sin_addr;            /* Internet address.  */

  /* Pad to size of `struct sockaddr'.  */
  unsigned char sin_zero[sizeof (struct sockaddr) -
                         __SOCKADDR_COMMON_SIZE -
                         sizeof (in_port_t) -
                         sizeof (struct in_addr)];
};

#endif

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

#endif //__HEAD_APUE__
