/*==========================================================
     > File Name: epoll_use_two_lt_et.c
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Sun 24 Jul 2016 05:56:23 PM CST
===========================================================*/

#include "ds_socket.h"
#include "ds_tools.h"



#define MAX_EVENT_NUMBER  (1024)
#define BUFFER_SIZE       (10)

//将文件描述符fd上的EPOLLIN注册到epollfd指示的epoll内核事件表中，
void add_fd(int epollfd,int fd,Boolean enableet)
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    if(enableet == TRUE){
       event.events |= EPOLLET;
    }
    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
    ds_setnonblocking(fd);
}


//lt
void epoll_lt(struct epoll_event *events,int number,int epollfd,int listenfd)
{
    int sockfd;
    int i = 0;
    char buf[BUFFER_SIZE];

    memset(buf,0x00,BUFFER_SIZE);
    for(i = 0; i < number; i++){
        sockfd = events[i].data.fd;
        if(sockfd == listenfd){
            struct sockaddr_in client_addr;
            socklen_t  client_addrlength = sizeof(client_addr);
            int connfd = ds_accept(listenfd,(struct sockaddr*)(&client_addr),&client_addrlength);
            add_fd(epollfd,connfd,FALSE);//关闭et
        }else if(events[i].events & EPOLLIN){

          /*只要socket上还有为读出的数据，这段代码就触发*/
            printf("event trigger once\n");
            memset(buf,0x00,BUFFER_SIZE);
            int ret = recv(sockfd,buf,BUFFER_SIZE -1,0);
            if(ret <= 0){
                close(sockfd);
                continue;
            }
            printf("get %d bytes of content:%s\n",ret,buf);
        }else{
            printf("something else happend \n");
        }
    }

}
//et
void epoll_et(struct epoll_event *events,int number,int epollfd,int listenfd)
{
    char buf[BUFFER_SIZE];
    int sockfd;
    int i = 0;


    memset(buf,0x00,BUFFER_SIZE);
    for(i = 0; i < number; i++){
       sockfd = events[i].data.fd;
       if(sockfd == listenfd){
           struct sockaddr_in client_addr;
           socklen_t client_addrlength = sizeof(client_addr);
           int connfd = ds_accept(listenfd,(struct sockaddr*)(&client_addr),&client_addrlength);
           add_fd(epollfd,connfd,TRUE);   //开启et
       }else if(events[i].events & EPOLLIN ){
          /*这段代码不会重复触发，所以处理数据要循环读*/
           printf("event trigger once\n");
           while(1){
               memset(buf,0x00,BUFFER_SIZE);
               int ret = recv(sockfd,buf,BUFFER_SIZE-1,0);
               if(ret < 0){
                /*这一步执行非阻塞IO表示数据已经全部读完，等待下一次，epoll触发EPOLLIN事件*/
                   if((errno == EAGAIN) || (errno == EWOULDBLOCK)){
                       printf("read later\n");
                       break;
                   }
                   close(sockfd);
                   break;
               }else if(ret == 0){
                   close(sockfd);
               }else{
                   printf("get %d bytes of content: %s\n",ret,buf);
               }
           }
       }else{
           printf("something else happend\n");
       }
    }

}

int main(int argc,char *argv[])
{
    int listenfd;
    int epollfd;
    struct epoll_event events[MAX_EVENT_NUMBER];

    listenfd = ds_create_socket();

    epollfd = epoll_create(5);
    return_if_fail(epollfd != -1);
    add_fd(epollfd,listenfd,TRUE);

    while(1){
        int count = epoll_wait(epollfd,events,MAX_EVENT_NUMBER,-1);
        return_if_fail(count >= 0);

//        epoll_lt(events,count,epollfd,listenfd);
        epoll_et(events,count,epollfd,listenfd);
    }


    close(listenfd);
    close(epollfd);
    return 0;
}
