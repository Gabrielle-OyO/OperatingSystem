#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>
#define SERVPORT 3333
#define MAXDATASIZE 100
int main(int argc,char *argv[])
{
  int sockfd,recvbytes;
  char buf[MAXDATASIZE];//接收数据的buf
  struct hostent *host;//调用gethostbyname函数
  struct sockaddr_in serv_addr;//服务器地址
  if(argc<2)
  {
    fprintf(stderr,"Please enter the server's hostname!\n");
    exit(1);
  }
  if((host=gethostbyname(argv[1]))==NULL)//IP地址则直接存放IP地址  IP地址名称 通过解析成IP地址进行存放
  {
    herror("gethostbyname error!\n");
    exit(1);
  }
  if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
  {
    perror("socket create error!\n");
    exit(1);
  }
  serv_addr.sin_family=AF_INET;//服务器类型
  serv_addr.sin_port=htons(SERVPORT);//服务器端口
  serv_addr.sin_addr=*((struct in_addr *)host->h_addr);//取地址
  bzero(&serv_addr.sin_zero,8);
  if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr))==-1)
  {
    perror("Error connect...\n");
    exit(1);
  }
  if((recvbytes=recv(sockfd,buf,MAXDATASIZE,0))==-1)
  {
    perror("Error connect...\n");
    exit(1);
  }
  buf[recvbytes]='\0';
  printf("Recieve: %s",buf);
  printf("sockfd:--- %d\n",sockfd);
  close(sockfd);
}

      
