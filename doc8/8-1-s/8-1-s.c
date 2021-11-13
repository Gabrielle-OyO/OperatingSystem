#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#define SERVPORT 3333//服务器监听端口号
#define BACKLOG 10//最大同时连接请求数
int main()
{
  int sockfd,client_fd;//监听 ，数据传输     监听-626740051  数据传输22023
  struct sockaddr_in my_addr;//本地机IP地址
  struct sockaddr_in remote_addr;//客户机IP地址
  int sin_size;//定义地址空间大小
  printf("sockfd:--- %d\n",sockfd);
  printf("client_fd:--- %d\n",client_fd);
  if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)//创建socket
  {
    perror("Failed to create socket !\n");
    exit(1);
  }
  my_addr.sin_family=AF_INET;//设置监听地址  类型为 AF_INET
  my_addr.sin_port=htons(SERVPORT);//htons把主机字节序转换成网络字节序  host to net
  my_addr.sin_addr.s_addr=INADDR_ANY;//本机中所有可以使用 作为监听的地址
  bzero(&(my_addr.sin_zero),8);//保持与struct sockaddr同样大小  后8个字节进行清零
  if(bind(sockfd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr))==-1)//绑定
  {AF_INET
    perror("Error bind!\n");
    exit(1);
  }
  if(listen(sockfd,BACKLOG)==-1)//监听    BACKLOG 缓冲池
  {
    perror("Error listen!\n");
    exit(1);
  }
  while(1)
  {
    sin_size=sizeof(struct sockaddr_in);
    //父进程
    if((client_fd=accept(sockfd,(struct sockaddr*)&remote_addr,&sin_size))==-1)//阻塞等待
    {
      perror("Error accept!\n");
      continue;
    }
    printf("client IP is :  %s\n",inet_ntoa(remote_addr.sin_addr));//把IP地址转换为字符串
    if(!fork())
    {
      //子进程
      if(send(client_fd,"conneting...\n",26,0)==-1)
        perror("Error send!\n");
      close(client_fd);
      exit(0);
    }
    close(client_fd);
  }
}
      
