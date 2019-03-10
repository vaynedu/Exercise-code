/*==========================================================
     > File Name: select_use.c
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Fri 01 Jul 2016 03:41:37 PM CST
===========================================================*/

#include "ds_socket.h"
#include "ds_tools.h"


#define  MAXDATASIZE    (1024)


typedef struct Client
{
    int    fd;                   //客户端sockket描述符
    char   name[20];             //客户端名称
    struct  sockaddr_in  addr;   //客户端结构体
    char   data[MAXDATASIZE];    //客户端的私有数据

}Client;


void process_client(Client *client,char *recvbuf,int len)
{
    char sendbuf[MAXDATASIZE];
    int i;

    printf("Receive client(%s) message:%s\n",client->name,recvbuf);

    for(i = 0; i < len - 1;i++){
        sendbuf[i] = recvbuf[len - i -1];
    }//end for

    sendbuf[len - 1] = '\0';

    send(client->fd,sendbuf,strlen(sendbuf),0);
}



int main(int argc,char *argv[])
{

    int       i,maxi,maxfd;
    int       sockfd,newfd,tempfd;
    int       nready;              //select 返回描述符
    ssize_t   n;

    fd_set  rset,allset;           //select所需文件描述符集合

    Client  client[FD_SETSIZE];
    char    recvbuf[MAXDATASIZE];  //接受缓冲区
    int     sin_size;              //地址信息结构体大小

    sockfd = ds_create_socket();   // 这里如果返回，那么sokcfd就是监听的描述符了

    maxfd = sockfd;
    maxi = -1;
    for(i = 0; i < FD_SETSIZE; i++){
        client[i].fd = -1;
    }//end for
    FD_ZERO(&allset);               // 清空
    FD_SET(sockfd,&allset);         // 将监听描述符socket加入select检测的描述集合

    while(1){
        struct sockaddr_in   addr;
        rset = allset;;
        nready = select(maxfd + 1,&rset,NULL,NULL,NULL);     // 调用select
        printf("select() break and the return num is %d\n",nready);

        if(FD_ISSET(sockfd,&rset)){        // 检测是否有新客户端请求
            printf("accept a connection\n");
            sin_size = sizeof(struct sockaddr_in); //socklen_t
            newfd = ds_accept(sockfd,(struct sockaddr *)(&addr),&sin_size); //调用accept，返回服务器与客户端连接的socket描述符

            // 将新客户端的描述符加入数组
            for(i = 0; i < FD_SETSIZE; i++){
                if(client[i].fd < 0){
                   char buffer[20];
                   client[i].fd = newfd;
                   memset(buffer,0x00,sizeof(buffer));
                   sprintf(buffer,"Client[%.2d]",i);
                   memcpy(client[i].name,buffer,strlen(buffer));
                   client[i].addr = addr;
                   memset(buffer,0x00,sizeof(buffer));
                   sprintf(buffer,"Only for my love!");
                   memcpy(client[i].data,buffer,strlen(buffer));
                   printf("you got a connection from %s:%d\n",
                          inet_ntoa(client[i].addr.sin_addr),
                          ntohs(client[i].addr.sin_port));
                   printf("add a new connection:%s",client[i].name);
                   break; // oh shit
                }//end if
            }// end for

            if(i == FD_SETSIZE){
                  printf("too  many  clients\n");
            }//end if
            FD_SET(newfd,&allset);
            if(newfd > maxfd){   // 确认maxfd是最大描述符
                  maxfd = newfd;
            }//end if
            if(i > maxi){
                maxi = i;
            }//end if
            if(--nready <= 0){   // 如果没有客户端连接，继续循环
                continue;
            }//end if
        }//end if

        for( i = 0; i <= maxi; i++){
              if((tempfd=client[i].fd) < 0){   // 如果客户端描述小雨0，则没有客户端连接，检测下一个
                 continue;
              }//end if
              //有客户连接，检测是否有数据
              if(FD_ISSET(tempfd,&rset)){
                 printf("Receive from connect fd[%d]\n",i);
                 if((n=recv(tempfd,recvbuf,MAXDATASIZE,0)) == 0){
                         // 从客户端socket读数据，等于0表示网络中断
                         close(tempfd);
                         printf("%s closed,User's data:%s\n",client[i].name,client[i].data);
                         FD_CLR(tempfd,&allset);
                         client[i].fd = -1;
                 }else{
                      process_client(&client[i],recvbuf,n); // 接受客户端数据，开始处理
                 }//end else
                 if(--nready <= 0){
                     break;          //如果没有新客户端有数据，跳出for循环回到while循环
                 }//end if
              }//end if
        }// end for
    }// end while

    close(sockfd);
    return 0;
}



