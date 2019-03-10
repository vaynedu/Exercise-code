/*==========================================================
     > File Name: epoll_one_use.c
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Sun 03 Jul 2016 03:57:35 PM CST
===========================================================*/

#include "ds_socket.h"

#define  EPOLL_SIZE     (2048)
#define  BUFFER_SIZE    (1024)



int  epoll_fd;
int  listen_fd;


void my_epoll_add(int fd)
{
     struct epoll_event  ev;
     ev.events = EPOLLIN | EPOLLET; //使用边缘触发模式，监听读数据
     ev.data.fd =  fd;

     epoll_ctl(epoll_fd,EPOLL_CTL_ADD,fd,&ev);

}

void  on_accept()
{
    struct sockaddr_in  client_addr;
    int client_len = sizeof(client_addr);
    int client_fd = accept(listen_fd,(struct sockaddr*)(&client_addr),&client_len);
    if(client_fd > 0){
        //边缘触发需要socket非阻塞
        int flag = 1;
        ioctl(client_fd,FIONBIO,&flag);

        my_epoll_add(client_fd);
        printf("new client accept...............\n");
    }//end if
}

int on_read(int fd)
{
    char  buffer[BUFFER_SIZE];
    int n;

    while(1){
        n = read(fd,buffer,BUFFER_SIZE);
        if(n == -1){
            if(errno == EAGAIN){
                //表示本次数据读完
                break;
            }//end if
            return (-1);
        }else if(n == 0){
            return (-1);
        }else{
            printf("recv:%s\n",buffer);
        }//end if else
        memset(buffer,0x00,BUFFER_SIZE);
    }//end while
    return 0;
}

int main(int argc,char *argv[])
{

    int i = 0;
    int count = 0;
    int fd = 0;
    int ev = 0;
    int timeout = 1000;
    struct epoll_event events[EPOLL_SIZE];

    listen_fd  = ds_create_socket(); // 直接创建好监听socket

    epoll_fd = epoll_create(EPOLL_SIZE); // 创建

    my_epoll_add(listen_fd);           //将监听描述符加进去，控制，事件类型

    while(1){
        count = epoll_wait(epoll_fd,events,EPOLL_SIZE,timeout); //监听
        if(count > 0){
            for(i = 0; i < count; i++){
                fd = events[i].data.fd;
                if(fd == listen_fd){ //连接到来
                    on_accept();
                    continue;
                }//end if

                ev = events[i].events;
                if((ev & EPOLLHUP) || (ev & EPOLLERR)){//连接关闭
                     close(fd);
                     printf("client %d close\n",fd);
                     continue;
                }//end if

                if(ev & EPOLLIN){         //表示有数据可读
                     if(on_read(fd) == -1){
                        printf("client %d close\n",fd);
                        close(fd);
                     }else{
                        //把状态改为epollout，下一次循环就可以出发事件
                        events[i].events = EPOLLOUT | EPOLLET;
                        epoll_ctl(epoll_fd,EPOLL_CTL_MOD,fd,&events[i]);
                     }
                }else if(ev & EPOLLOUT){
                     // 处理写数据
                     //修改状态
                    events[i].events = EPOLLIN | EPOLLET;
                    epoll_ctl(epoll_fd,EPOLL_CTL_MOD,fd,&events[i]);
                }//end if else if
            }//end for
        }//end if
    }//end while

    close(epoll_fd);
    close(listen_fd);

    return 0;
}















